add_compile_options(-std=c++14)
cmake_minimum_required(VERSION 3.3)

project(myProject)

enable_testing()

add_subdirectory(test)
add_subdirectory(lib)