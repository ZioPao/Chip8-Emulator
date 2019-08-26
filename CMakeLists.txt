cmake_minimum_required(VERSION 3.14)
project(chip8_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(chip8_2 main.cpp chip8.cpp chip8.h)