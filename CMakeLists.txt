cmake_minimum_required(VERSION 3.14)
project(chip8_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --machine-windows")

add_executable(chip8_2 main.cpp chip8.cpp chip8.h )

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(chip8_2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
