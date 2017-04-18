CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variables
SET(PROJ_NAME					"Data Preprocessing"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)
SET(PROJ_INCLUDES			"inc")

# Ejecutables
SET(EJECUTABLE1       "yalefaces")
#SET(EJECUTABLE2       "KDEF")
#SET(EJECUTABLE2       "trainingSetup")

# Archivos para cada ejecutable
FILE( GLOB_RECURSE EXECUTABLE1_SOURCES src/yalefaces.cpp src/subject.cpp utilidades.cpp yalefaces_db.cpp infoBaseDatos.cpp )
#FILE( GLOB_RECURSE EXECUTABLE2_SOURCES src/trainingSetup.cpp )

# Inicio compilación.
PROJECT( ${PROJ_NAME} )

# Compilación Ejecutable 1.
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${EJECUTABLE1} ${EXECUTABLE1_SOURCES} )
TARGET_LINK_LIBRARIES( ${EJECUTABLE1} ${OpenCV_LIBS} )

# Compilación Ejecutable 2.
#ADD_EXECUTABLE( ${EJECUTABLE2} ${EXECUTABLE2_SOURCES} )
