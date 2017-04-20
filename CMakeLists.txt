CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variables
SET(PROJ_NAME					"Data Preprocessing"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)
SET(PROJ_INCLUDES			"inc")
SET(PROJ_SOURCES      "src")

# Ejecutables
SET(EJECUTABLE1       "yalefaces")
SET(EJECUTABLE2       "KDEF")
#SET(EJECUTABLE2       "trainingSetup")

# Archivos para cada ejecutable
FILE( GLOB_RECURSE EXECUTABLE1_SOURCES ${PROJ_SOURCES}/yalefaces.cpp ${PROJ_SOURCES}/yalefaces_db.cpp ${PROJ_SOURCES}/infoBaseDatos.cpp ${PROJ_SOURCES}/utilidades.cpp ${PROJ_SOURCES}/subject.cpp )
FILE( GLOB_RECURSE EXECUTABLE2_SOURCES ${PROJ_SOURCES}/kdef.cpp ${PROJ_SOURCES}/kdef_db.cpp ${PROJ_SOURCES}/infoBaseDatos.cpp ${PROJ_SOURCES}/utilidades.cpp )

# Inicio compilación.
PROJECT( ${PROJ_NAME} )

# Includes y 3rd parties.
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )
FIND_PACKAGE( OpenCV REQUIRED )

# Compilación Ejecutable 1.
ADD_EXECUTABLE( ${EJECUTABLE1} ${EXECUTABLE1_SOURCES} )
TARGET_LINK_LIBRARIES( ${EJECUTABLE1} ${OpenCV_LIBS} )

# Compilación Ejecutable 2.
ADD_EXECUTABLE( ${EJECUTABLE2} ${EXECUTABLE2_SOURCES} )
TARGET_LINK_LIBRARIES( ${EJECUTABLE2} ${OpenCV_LIBS} )
