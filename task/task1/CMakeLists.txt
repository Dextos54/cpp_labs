cmake_minimum_required(VERSION 3.20)  #версия cmake

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # стандарт плючов
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_app main.cpp) 