cmake_minimum_required(VERSION 3.11)

project(String CXX)
set(CMAKE_CXX_STANDARD 11)
 
add_executable(String 
               src/main.cpp 
               src/String.h 
               src/String.cpp)