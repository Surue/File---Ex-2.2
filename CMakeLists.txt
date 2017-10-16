cmake_minimum_required(VERSION 3.9)
project(Exe2.2)

file(GLOB_RECURSE Exe2.2_SRC src/*.cpp include/*.h)

include_directories(include/)
add_executable(Exe2.2 ${Exe2.2_SRC})
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)



#SFML
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
set(SFML_BUILD_EXAMPLES FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include)

LIST(APPEND Exe2.2_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network)
	
target_link_libraries(Exe2.2 ${Exe2.2_LIBRARIES})
	