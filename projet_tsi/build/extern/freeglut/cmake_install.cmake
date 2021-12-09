# Install script for directory: C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/extern/freeglut

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/openGL_CPE")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/lib/Debug/freeglut_staticd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/lib/Release/freeglut_static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/lib/MinSizeRel/freeglut_static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/lib/RelWithDebInfo/freeglut_static.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GL" TYPE FILE FILES
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/extern/freeglut/include/GL/freeglut.h"
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/extern/freeglut/include/GL/freeglut_ucall.h"
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/extern/freeglut/include/GL/freeglut_ext.h"
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/extern/freeglut/include/GL/freeglut_std.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE RENAME "freeglut.pc" FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/freeglut.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake"
         "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/CMakeFiles/Export/lib/cmake/FreeGLUT/FreeGLUTTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/FreeGLUT/FreeGLUTConfig.cmake"
    "C:/Users/romai/OneDrive/Documents/School/4A/TSI/TP/TSI_projet/projet_tsi/build/extern/freeglut/FreeGLUT/FreeGLUTConfigVersion.cmake"
    )
endif()

