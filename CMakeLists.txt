#-----------------------------------------------------------------------------
#
# Backward compatible to 2.4
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

IF(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 OLD)
ENDIF(COMMAND cmake_policy)

PROJECT(GraphicsProjectFrameWork)

set(CMAKE_CXX_FLAGS "-trigraphs -g")

FIND_PACKAGE(OpenGL)
IF(OPENGL_FOUND)
  SET( GRAPHICS_INCLUDE_DIRS ${GRAPHICS_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
  SET( GRAPHICS_LIBS  ${GRAPHICS_LIBS} ${OPENGL_LIBRARIES}  )
ENDIF(OPENGL_FOUND)

IF (WIN32)
  SET(GRAPHICS_INCLUDE_DIRS ${GRAPHICS_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/externals/include/windows")

  FIND_PATH(GLUT_INCLUDE_DIR GL/glut.h
    "C:/Program Files/NVIDIA Corporation/Cg/include/"
    "C:/Program Files/NVIDIA Corporation/SDK 9.5/inc/"
    "C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/Include/"
    DOC "What is the path where the file glut.h can be found"
    )
  IF(GLUT_INCLUDE_DIR)
    SET(GRAPHICS_INCLUDE_DIRS ${GRAPHICS_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
    MARK_AS_ADVANCED(GLUT_INCLUDE_DIR)
  ENDIF(GLUT_INCLUDE_DIR)
  FIND_LIBRARY(GLUT32_LIB glut32
    "${PROJECT_SOURCE_DIR}/externals/lib/windows"
    "C:/Program Files/NVIDIA Corporation/Cg/lib"
    "C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/lib"
    DOC "What is the path where the file glut32.lib can be found"
    )
  IF(GLUT32_LIB)
    SET( GRAPHICS_LIBS  ${GRAPHICS_LIBS} "optimized" ${GLUT32_LIB} )
    MARK_AS_ADVANCED(GLUT32_LIB)
  ENDIF(GLUT32_LIB)
  FIND_LIBRARY(GLUT32D_LIB glut32D
    "${PROJECT_SOURCE_DIR}/externals/lib/windows"
    "C:/Program Files/NVIDIA Corporation/Cg/lib"
    "C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/lib"
    DOC "What is the path where the file glut32.lib can be found"
    )
  IF(GLUT32D_LIB)
    SET( GRAPHICS_LIBS  ${GRAPHICS_LIBS} "debug" ${GLUT32D_LIB} )
    MARK_AS_ADVANCED(GLUT32D_LIB)
  ENDIF(GLUT32D_LIB)
ELSE(WIN32)
  FIND_PACKAGE(GLUT)
  IF(GLUT_FOUND)
    SET(GRAPHICS_INCLUDE_DIRS ${GRAPHICS_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
    SET(GRAPHICS_LIBS  ${GRAPHICS_LIBS} ${GLUT_LIBRARIES}  )
  ENDIF(GLUT_FOUND)
ENDIF(WIN32)

INCLUDE_DIRECTORIES( 
                    ${PROJECT_SOURCE_DIR}/src 
		    ${GRAPHICS_INCLUDE_DIRS}
                   )

ADD_EXECUTABLE(framework src/main.cpp)
ADD_EXECUTABLE(teapot src/teapot.cpp)
ADD_EXECUTABLE(pain src/pain.cpp)
ADD_EXECUTABLE(rocket src/rocket.cpp)
ADD_EXECUTABLE(patches src/patches.cpp)

TARGET_LINK_LIBRARIES(framework ${GRAPHICS_LIBS})
TARGET_LINK_LIBRARIES(teapot ${GRAPHICS_LIBS})
TARGET_LINK_LIBRARIES(pain ${GRAPHICS_LIBS})
TARGET_LINK_LIBRARIES(rocket ${GRAPHICS_LIBS})
TARGET_LINK_LIBRARIES(patches ${GRAPHICS_LIBS})

