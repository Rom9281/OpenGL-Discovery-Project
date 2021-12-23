/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
 \*****************************************************************************/


#include "declaration.h"

//identifiant des shaders
GLuint shader_program_id;
GLuint gui_program_id;

camera cam;

const int nb_obj = 3;
objet3d obj[nb_obj];

const int nb_text = 2;
text text_to_draw[nb_text];

// Variables supplémentaire
// **************************************************************************

// I. Physique du personnage
// __________________________________________________

// 1. Deplacements
float vect_vitesse[3] = { 0.0,0.0,0.0 }; // vecteur de vitesse
enum coordonnés {X,Y,Z};

// 2. Caractéristiques
float masse = 200.0;

//3. Force de frottement
float F = 0.0;

// detection de vol
bool airborn_flag = false;


// Gestion du saut
// __________________________________________________

bool jump_flag = false;
bool jump_enable = true;

float jump_time_0 = 0.000000000; // first moment of the jump
float jump_time = 0.00000000000; //
 
float g = 9.810000/8; // Constante gravitationelle
float jump_speed = 1.0000; // Vitesse du saut quand initié

// Gestion des deplacements
//____________________________________________________
enum directions {UP,DOWN,LEFT,RIGHT};
bool move[] = {false,false,false,false}; // Permet d'établir si il faut bouger qqchs
bool move_enable = true;

// Gestion du temps
// ___________________________________________________
float timer = 0; // Commencement du temps à 0
float time_step = 0.025; // Base: 0.025

// Gestion des collisions & Frotements
// ___________________________________________________

// 1. Rayon de collision
float rayon_collision = 1.0; // valeur recomandé par le professeur

// 2. Detecteurs de collisions
bool collision_flag = false;
bool collision_enable = true;

// 3. Temps de la collision
float collision_time_0 = 0.000000000; // first moment of the jump
float collision_time = 0.00000000000; //

// 4. Force de la collisions
float vitesse_collision = 0.5; // Vitesse à l'instant 0 de la collision

// 5. Variable de calcul temporaire
float vect_vit_temp[3] = {0.0,0.0,0.0};

// 6. Coeficient de frottements
float mu_c = 0.8;


// AJOUTS DE FONCTIONS
// **************************************************************************

// Calcul de norme d'un vecteur en 3D
float norm(float table[3]) {
    return sqrt(table[X] * table[X] + table[Y] * table[Y] + table[Z] * table[Z]);
}

// Calcul de la norme d'un vecteur entre deux objets
float norm2point(objet3d objet1, objet3d objet2) {
    return sqrt((objet2.tr.translation.x - objet1.tr.translation.x )*(objet2.tr.translation.x - objet1.tr.translation.x)+(objet2.tr.translation.y - objet1.tr.translation.y)*(objet2.tr.translation.y - objet1.tr.translation.y) + (objet2.tr.translation.z - objet1.tr.translation.z)*(objet2.tr.translation.z - objet1.tr.translation.z));
}


// Fonction de calcul de vecteur normé entre deux objets
float getNorm(char choix, objet3d objet1, objet3d objet2) {
    float valren = 0.0;
    switch (choix) {
    case 'X':
        valren = (objet2.tr.translation.x - objet1.tr.translation.x) / norm2point(objet1, objet2);
        break;
    case 'Y':
        valren = (objet2.tr.translation.y - objet1.tr.translation.y) / norm2point(objet1, objet2);
        break;
    case 'Z':
        valren = (objet2.tr.translation.z - objet1.tr.translation.z) / norm2point(objet1, objet2);
        break;
    }
    return valren;
}

// Fonction décrivant l'évolution de la vitesse apres une collision
float collisionSpeed(float t, float vitesse[3],float mu_c) {
    return vitesse_collision * exp((-t)*(norm(vitesse))/(mu_c));
}

void copyVector(float table1[3], float table2[2]) {
    table2[X] = table1[X];
    table2[Y] = table1[Y];
    table2[Z] = table1[Z];
}

void resetVector(float table[3]) {
    table[X] = 0.0;
    table[Y] = 0.0;
    table[Z] = 0.0;

}

// **************************************************************************


/*****************************************************************************\
* initialisation                                                              *
\*****************************************************************************/
static void init()
{
  shader_program_id = glhelper::create_program_from_file("shaders/shader.vert", "shaders/shader.frag"); CHECK_GL_ERROR();

  cam.projection = matrice_projection(60.0f*M_PI/180.0f,1.0f,0.01f,100.0f);
  cam.tr.translation = vec3(0.0f, 1.0f, 0.0f);
  
  // cam.tr.translation = vec3(0.0f, 20.0f, 0.0f);
  // cam.tr.rotation_center = vec3(0.0f, 20.0f, 0.0f);
  // cam.tr.rotation_euler = vec3(M_PI/2., 0.0f, 0.0f);

  init_model_1();
  init_model_2();   
  init_model_3();

  gui_program_id = glhelper::create_program_from_file("shaders/gui.vert", "shaders/gui.frag"); CHECK_GL_ERROR();
  
  /*
  text_to_draw[0].value = "CPE";
  text_to_draw[0].bottomLeft = vec2(-0.2, 0.5);
  text_to_draw[0].topRight = vec2(0.2, 1);
  init_text(text_to_draw);

  text_to_draw[1]=text_to_draw[0];
  text_to_draw[1].value = "Lyon";
  text_to_draw[1].bottomLeft.y = 0.0f;
  text_to_draw[1].topRight.y = 0.5f;

  */
}

/*****************************************************************************\
* display_callback                                                           *
\*****************************************************************************/
 static void display_callback()
{
  glClearColor(0.5f, 0.6f, 0.9f, 1.0f); CHECK_GL_ERROR();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();

  for(int i = 0; i < nb_obj; ++i)
    draw_obj3d(obj + i, cam);

  for(int i = 0; i < nb_text; ++i)
    draw_text(text_to_draw + i);

  glutSwapBuffers();
}

/*****************************************************************************\
* keyboard_callback                                                           *
\*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{
  switch (key)
  {
    case 'p':
      glhelper::print_screen();
      break;
    case 'Q':
    case 27:
      exit(0);
      break;

    case 'x':
        if (jump_enable) {
            jump_enable = false;
            jump_flag = true;
        }
        break;
  }
}

/*****************************************************************************\
* special_callback                                                            *
\*****************************************************************************/
static void special_callback(int key, int, int)
{
    switch (key){

    case GLUT_KEY_UP:
        if (move_enable) {
            move[UP] = true;
        }
        break;
    case GLUT_KEY_DOWN:
        if (move_enable) {
            move[DOWN] = true;
        }
        break;
    case GLUT_KEY_LEFT:
        if (move_enable) {
            move[LEFT] = true;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (move_enable) {
            move[RIGHT] = true;
        }
        break;
    }
}

static void special_callback_up(int key, int, int)
{
    switch (key){
    case GLUT_KEY_UP:
        move[UP] = false;
        break;
    case GLUT_KEY_DOWN:
        move[DOWN] = false;
        break;
    case GLUT_KEY_LEFT:
        move[LEFT] = false;
        break;
    case GLUT_KEY_RIGHT:
        move[RIGHT] = false;
        break;
    }
}

/*****************************************************************************\
* timer_callback                                                              *
\*****************************************************************************/

static void timer_callback(int){
    
    // Detection de vol
    //---------------------------------------------------------------------------------------
    if(!airborn_flag && obj[2].tr.translation.y > 0) {
        airborn_flag = true;
        jump_time_0 = timer;
    }
    else if (airborn_flag && obj[2].tr.translation.y <= 0) {
        airborn_flag = false;
    }

    // definitions des temps
    // -------------------------------------------------------------------------------------
    timer += time_step;
    jump_time = timer - jump_time_0;
    collision_time = timer - collision_time_0;
    
    
    // Detection des collisions
    // ------------------------------------------------------------------------------------

    if (norm2point(obj[2], obj[0]) < rayon_collision * rayon_collision) {

        collision_time_0 = timer;

        /*  
        * Tout ce qui est lié a la collision et fait une seule fois rentre ici:
        * Par exemple, on applique une seul fois la vitesse de vol
        */

        vect_vitesse[Z] += -getNorm('Z', obj[2], obj[0]) * collisionSpeed(collision_time, vect_vitesse, mu_c);

        collision_flag = true;
        move_enable = false;

        printf("[$]Collision! (time:%f)\n",timer);
    }

    // Force de pesenteur
    // ____________________________________________________________________________________

    if (airborn_flag) { // Si l'objet est en l'air

        vect_vitesse[Z] += -g*jump_time; // Application de la formule P=mg

    }

    // Application de la collision avec prise en compte des frotements secs
    // ------------------------------------------------------------------------------------

    

    if(collision_flag){

        if (airborn_flag) {
            mu_c = 0.017;
        }
        else {
            mu_c = 0.8/20;
        }

        vect_vitesse[X] = -getNorm('X',obj[2], obj[0]) * collisionSpeed(collision_time,vect_vitesse,mu_c);
        vect_vitesse[Y] = -getNorm('Y',obj[2], obj[0]) * collisionSpeed(collision_time,vect_vitesse,mu_c);

        printf("[$]Force applied! Value = %f (collision time: %f)\n", collisionSpeed(collision_time, vect_vitesse, mu_c), collision_time); // Permet de s'informer

        if (collisionSpeed(collision_time, vect_vitesse, mu_c) < 0.15) {
            printf("[$] Collision ended.\n");
            resetVector(vect_vitesse);

            collision_flag = false;  // ACtivation du flag
            move_enable = true;     // Empeche le joueur d'utiliser les commandes
        }
    }


    // Saut du personnage
    // -----------------------------------------------------------------------------------

    if (jump_flag) {

            vect_vitesse[Z] += jump_speed; // Ajout de la vitesse du saut.

            jump_flag = false;
            jump_enable = true;
    }

    // Deplacement du personnage
    // ---------------------------------------------------------------------------------------

    // Up
    if (move[UP]){
        obj[2].tr.translation.z += 0.1f; // Deplacement
    }

    // Down
    if (move[DOWN]) {
        obj[2].tr.translation.z += -0.1f;
    }
    // Left
    if (move[LEFT]) {
        obj[2].tr.translation.x += 0.1f;
    }

    //Right
    if (move[RIGHT]) {
        obj[2].tr.translation.x += -0.1f;
    }


    if (obj[2].tr.translation.y < 0) { // sil'objet est sous le sol
        obj[2].tr.translation.y = 0; // Le ramener a la surface
    }

    // Application du vecteur vitesse a la position
    // ------------------------------------------------------------------------
    obj[2].tr.translation.x += vect_vitesse[X];
    obj[2].tr.translation.y += vect_vitesse[Z];
    obj[2].tr.translation.z += vect_vitesse[Y];


    printf("[$] Coord (%f,%f,%f) | Speed (%f,%f,%f)\n",obj[2].tr.translation.x, obj[2].tr.translation.y, obj[2].tr.translation.z, vect_vitesse[X], vect_vitesse[Y], vect_vitesse[Z]);

    // Si plus bas que sol
    //--------------------------------------------------------------------------
    if (obj[2].tr.translation.y < 0) { // Si jamais sous le sol
        obj[2].tr.translation.y = 0; 
        if (vect_vitesse[Z] < 0) { // si le vecteur vitesse est negatif au sol
            vect_vitesse[Z] = 0;
        }
    }


    glutTimerFunc(25, timer_callback, 0);
    glutPostRedisplay();
}

/*****************************************************************************\
* main                                                                         *
\*****************************************************************************/
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | MACOSX_COMPATIBILITY);
  glutInitWindowSize(600, 600);
  glutCreateWindow("OpenGL");

  glutDisplayFunc(display_callback);
  glutKeyboardFunc(keyboard_callback);
  glutSpecialFunc(special_callback);
  glutSpecialUpFunc(special_callback_up);
  glutTimerFunc(25, timer_callback, 0);

  glewExperimental = true;
  glewInit();

  std::cout << "OpenGL: " << (GLchar *)(glGetString(GL_VERSION)) << std::endl;

  init();
  glutMainLoop();

  return 0;
}

/*****************************************************************************\
* draw_text                                                                   *
\*****************************************************************************/
void draw_text(const text * const t)
{
  if(!t->visible) return;
  
  glDisable(GL_DEPTH_TEST);
  glUseProgram(t->prog);

  vec2 size = (t->topRight - t->bottomLeft) / float(t->value.size());
  
  GLint loc_size = glGetUniformLocation(gui_program_id, "size"); CHECK_GL_ERROR();
  if (loc_size == -1) std::cerr << "Pas de variable uniforme : size" << std::endl;
  glUniform2f(loc_size,size.x, size.y);     CHECK_GL_ERROR();

  glBindVertexArray(t->vao);                CHECK_GL_ERROR();
  
  for(unsigned i = 0; i < t->value.size(); ++i)
  {
    GLint loc_start = glGetUniformLocation(gui_program_id, "start"); CHECK_GL_ERROR();
    if (loc_start == -1) std::cerr << "Pas de variable uniforme : start" << std::endl;
    glUniform2f(loc_start,t->bottomLeft.x+i*size.x, t->bottomLeft.y);    CHECK_GL_ERROR();

    GLint loc_char = glGetUniformLocation(gui_program_id, "c"); CHECK_GL_ERROR();
    if (loc_char == -1) std::cerr << "Pas de variable uniforme : c" << std::endl;
    glUniform1i(loc_char, (int)t->value[i]);    CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, t->texture_id);                            CHECK_GL_ERROR();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);                    CHECK_GL_ERROR();
  }
}

/*****************************************************************************\
* draw_obj3d                                                                  *
\*****************************************************************************/
void draw_obj3d(const objet3d* const obj, camera cam)
{
  if(!obj->visible) return;

  glEnable(GL_DEPTH_TEST);
  glUseProgram(obj->prog);
  
  {
    GLint loc_projection = glGetUniformLocation(shader_program_id, "projection"); CHECK_GL_ERROR();
    if (loc_projection == -1) std::cerr << "Pas de variable uniforme : projection" << std::endl;
    glUniformMatrix4fv(loc_projection,1,false,pointeur(cam.projection));    CHECK_GL_ERROR();

    GLint loc_rotation_view = glGetUniformLocation(shader_program_id, "rotation_view"); CHECK_GL_ERROR();
    if (loc_rotation_view == -1) std::cerr << "Pas de variable uniforme : rotation_view" << std::endl;
    mat4 rotation_x = matrice_rotation(cam.tr.rotation_euler.x, 1.0f, 0.0f, 0.0f);
    mat4 rotation_y = matrice_rotation(cam.tr.rotation_euler.y, 0.0f, 1.0f, 0.0f);
    mat4 rotation_z = matrice_rotation(cam.tr.rotation_euler.z, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(loc_rotation_view,1,false,pointeur(rotation_x*rotation_y*rotation_z));    CHECK_GL_ERROR();

    vec3 cv = cam.tr.rotation_center;
    GLint loc_rotation_center_view = glGetUniformLocation(shader_program_id, "rotation_center_view"); CHECK_GL_ERROR();
    if (loc_rotation_center_view == -1) std::cerr << "Pas de variable uniforme : rotation_center_view" << std::endl;
    glUniform4f(loc_rotation_center_view , cv.x,cv.y,cv.z , 0.0f); CHECK_GL_ERROR();

    vec3 tv = cam.tr.translation;
    GLint loc_translation_view = glGetUniformLocation(shader_program_id, "translation_view"); CHECK_GL_ERROR();
    if (loc_translation_view == -1) std::cerr << "Pas de variable uniforme : translation_view" << std::endl;
    glUniform4f(loc_translation_view , tv.x,tv.y,tv.z , 0.0f); CHECK_GL_ERROR();
  }
  {
    GLint loc_rotation_model = glGetUniformLocation(obj->prog, "rotation_model"); CHECK_GL_ERROR();
    if (loc_rotation_model == -1) std::cerr << "Pas de variable uniforme : rotation_model" << std::endl;
    mat4 rotation_x = matrice_rotation(obj->tr.rotation_euler.x, 1.0f, 0.0f, 0.0f);
    mat4 rotation_y = matrice_rotation(obj->tr.rotation_euler.y, 0.0f, 1.0f, 0.0f);
    mat4 rotation_z = matrice_rotation(obj->tr.rotation_euler.z, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(loc_rotation_model,1,false,pointeur(rotation_x*rotation_y*rotation_z));    CHECK_GL_ERROR();

    vec3 c = obj->tr.rotation_center;
    GLint loc_rotation_center_model = glGetUniformLocation(obj->prog, "rotation_center_model");   CHECK_GL_ERROR();
    if (loc_rotation_center_model == -1) std::cerr << "Pas de variable uniforme : rotation_center_model" << std::endl;
    glUniform4f(loc_rotation_center_model , c.x,c.y,c.z , 0.0f);                                  CHECK_GL_ERROR();

    vec3 t = obj->tr.translation;
    GLint loc_translation_model = glGetUniformLocation(obj->prog, "translation_model"); CHECK_GL_ERROR();
    if (loc_translation_model == -1) std::cerr << "Pas de variable uniforme : translation_model" << std::endl;
    glUniform4f(loc_translation_model , t.x,t.y,t.z , 0.0f);                                     CHECK_GL_ERROR();
  }
  glBindVertexArray(obj->vao);                                              CHECK_GL_ERROR();

  glBindTexture(GL_TEXTURE_2D, obj->texture_id);                            CHECK_GL_ERROR();
  glDrawElements(GL_TRIANGLES, 3*obj->nb_triangle, GL_UNSIGNED_INT, 0);     CHECK_GL_ERROR();
}

void init_text(text *t){
  vec3 p0=vec3( 0.0f, 0.0f, 0.0f);
  vec3 p1=vec3( 0.0f, 1.0f, 0.0f);
  vec3 p2=vec3( 1.0f, 1.0f, 0.0f);
  vec3 p3=vec3( 1.0f, 0.0f, 0.0f);

  vec3 geometrie[4] = {p0, p1, p2, p3}; 
  triangle_index index[2] = { triangle_index(0, 1, 2), triangle_index(0, 2, 3)};

  glGenVertexArrays(1, &(t->vao));                                              CHECK_GL_ERROR();
  glBindVertexArray(t->vao);                                                  CHECK_GL_ERROR();

  GLuint vbo;
  glGenBuffers(1, &vbo);                                                       CHECK_GL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER,vbo);                                          CHECK_GL_ERROR();
  glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);   CHECK_GL_ERROR();

  glEnableVertexAttribArray(0); CHECK_GL_ERROR();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();

  GLuint vboi;
  glGenBuffers(1,&vboi);                                                      CHECK_GL_ERROR();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);                                 CHECK_GL_ERROR();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);   CHECK_GL_ERROR();

  t->texture_id = glhelper::load_texture("data/fontB.tga");

  t->visible = true;
  t->prog = gui_program_id;
}

GLuint upload_mesh_to_gpu(const mesh& m)
{
  GLuint vao, vbo, vboi;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1,&vbo);                                 CHECK_GL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER,vbo); CHECK_GL_ERROR();
  glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); CHECK_GL_ERROR();

  glEnableVertexAttribArray(0); CHECK_GL_ERROR();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), 0); CHECK_GL_ERROR();

  glEnableVertexAttribArray(1); CHECK_GL_ERROR();
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(vertex_opengl), (void*)sizeof(vec3)); CHECK_GL_ERROR();

  glEnableVertexAttribArray(2); CHECK_GL_ERROR();
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(2*sizeof(vec3))); CHECK_GL_ERROR();

  glEnableVertexAttribArray(3); CHECK_GL_ERROR();
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_opengl), (void*)(3*sizeof(vec3))); CHECK_GL_ERROR();

  glGenBuffers(1,&vboi); CHECK_GL_ERROR();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi); CHECK_GL_ERROR();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); CHECK_GL_ERROR();

  return vao;
}

void init_model_1()
{
  // Chargement d'un maillage a partir d'un fichier
  mesh m = load_obj_file("data/stegosaurus.obj");

  // Affecte une transformation sur les sommets du maillage
  float s = 0.2f;
  mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
      0.0f,    s, 0.0f, 0.0f,
      0.0f, 0.0f,   s , 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f);

  apply_deformation(&m,transform);

  // Centre la rotation du modele 1 autour de son centre de gravite approximatif
  obj[0].tr.rotation_center = vec3(0.0f,0.0f,0.0f);

  update_normals(&m);
  fill_color(&m,vec3(1.0f,1.0f,1.0f));

  obj[0].vao = upload_mesh_to_gpu(m);

  obj[0].nb_triangle = m.connectivity.size();
  obj[0].texture_id = glhelper::load_texture("data/stegosaurus.tga");
  obj[0].visible = true;
  obj[0].prog = shader_program_id;

  obj[0].tr.translation = vec3(-2.0, 0.0, -10.0);
}

void init_model_2()
{

  mesh m;

  //coordonnees geometriques des sommets
  vec3 p0=vec3(-25.0f,0.0f,-25.0f);
  vec3 p1=vec3( 25.0f,0.0f,-25.0f);
  vec3 p2=vec3( 25.0f,0.0f, 25.0f);
  vec3 p3=vec3(-25.0f,0.0f, 25.0f);

  //normales pour chaque sommet
  vec3 n0=vec3(0.0f,1.0f,0.0f);
  vec3 n1=n0;
  vec3 n2=n0;
  vec3 n3=n0;

  //couleur pour chaque sommet
  vec3 c0=vec3(1.0f,1.0f,1.0f);
  vec3 c1=c0;
  vec3 c2=c0;
  vec3 c3=c0;

  //texture du sommet
  vec2 t0=vec2(0.0f,0.0f);
  vec2 t1=vec2(1.0f,0.0f);
  vec2 t2=vec2(1.0f,1.0f);
  vec2 t3=vec2(0.0f,1.0f);

  vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
  vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
  vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
  vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);

  m.vertex = {v0, v1, v2, v3};

  //indice des triangles
  triangle_index tri0=triangle_index(0,1,2);
  triangle_index tri1=triangle_index(0,2,3);  
  m.connectivity = {tri0, tri1};

  obj[1].nb_triangle = 2;
  obj[1].vao = upload_mesh_to_gpu(m);

  obj[1].texture_id = glhelper::load_texture("data/grass.tga");

  obj[1].visible = true;
  obj[1].prog = shader_program_id;
}


void init_model_3()
{
  // Chargement d'un maillage a partir d'un fichier
  mesh m = load_off_file("data/armadillo_light.off");

  // Affecte une transformation sur les sommets du maillage
  float s = 0.01f;

  mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
      0.0f,    s, 0.0f, 0.70f, // modification 0.5->0.7
      0.0f, 0.0f,   s , 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f);

  apply_deformation(&m,matrice_rotation(M_PI/2.0f,1.0f,0.0f,0.0f));
  apply_deformation(&m,matrice_rotation(M_PI,0.0f,1.0f,0.0f));
  apply_deformation(&m,transform);

  update_normals(&m);
  fill_color(&m,vec3(1.0f,1.0f,1.0f));

  obj[2].vao = upload_mesh_to_gpu(m);

  obj[2].nb_triangle = m.connectivity.size();
  obj[2].texture_id = glhelper::load_texture("data/white.tga");

  obj[2].visible = true;
  obj[2].prog = shader_program_id;

  obj[2].tr.translation = vec3(2.0, 0.0, -10.0);
}

