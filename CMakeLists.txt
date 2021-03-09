cmake_minimum_required(VERSION 3.0)
project(mpl VERSION 1.0.0 LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS "-O3 -std=c++17")

########################
#######DIRECTORY########
########################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#copy python scripts to binary directory
configure_file(scripts/GenerateCSpace.py ${CMAKE_BINARY_DIR}/bin/GenerateCSpace.py COPYONLY)

#define variable for binary directory 
add_definitions(-DCMAKE_RUNTIME_OUTPUT_DIRECTORY="${CMAKE_BINARY_DIR}/bin/")

########################
######Dependencies######
########################
find_package(PythonLibs 2.7 REQUIRED)
find_package(Matplot++ REQUIRED)

INCLUDE_DIRECTORIES(
	include
	src
	scripts
	${PROJECT_SOURCE_DIR}
	${PYTHON_INCLUDE_DIRS}
	/usr/include/python2.7/
	graph/include
)

###########################
#######SUBDIRECTORY########
###########################
add_subdirectory(graph)

#######################
########Library########
#######################
add_library(mpl
	include/Roadmap.cpp
	include/CSpace.cpp
	include/Plotting.cpp)

target_link_libraries(mpl 
	graph
	Matplot++::matplot
 )

add_library(utils include/utils.cpp)

########################
########Examples########
########################
add_executable(test_roadmap tests/test_roadmap.cpp)
target_link_libraries(test_roadmap 
	mpl
	utils
	Matplot++::matplot
 )

add_executable(scratch src/scratch.cpp)
target_link_libraries(scratch 
	mpl
	utils
	Matplot++::matplot
 )

add_executable(test_matplotplusplus tests/test_matplotplusplus.cpp)
target_link_libraries(test_matplotplusplus 
	Matplot++::matplot
 )

#########################
##########Tests##########
#########################
#TODO
