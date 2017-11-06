project(DateTimeLibrary)
add_compile_options(-std=c++14)
cmake_minimum_required(VERSION 2.8)

enable_testing()

include(build/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

INCLUDE_DIRECTORIES(src)
ADD_EXECUTABLE(dateTime_test gtest/DateTimeTest.cpp)
TARGET_LINK_LIBRARIES(dateTime_test ${CONAN_LIBS})
