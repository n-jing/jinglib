CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(JinglibDoc)

SET(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

FIND_PACKAGE(Doxygen)
if (NOT DOXYGEN_FOUND)
  message(FATAL_ERROR 
    "Doxygen is needed to build the documentation. Please install it correctly")
endif()

SET(doc_inc_file ${PROJECT_SOURCE_DIR}/inc)
SET(doc_src_file ${PROJECT_SOURCE_DIR}/src)
SET(readme ${PROJECT_SOURCE_DIR}/README.md)
CONFIGURE_FILE(Doxyfile
  ${PROJECT_BINARY_DIR}/Doxyfile  @ONLY IMMEDIATE)

ADD_CUSTOM_TARGET(half_edge_doc ALL 
	COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
	SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
