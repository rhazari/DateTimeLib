cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(GoogleTestSampleProject)

set(CMAKE_CXX_STANDARD 14)

option(debug "Use debugging flag" ON)

# Set the C++ standard you wish to use (will apply to all files).
# If you do not use any features that limits the standard required,
# you could omitt this line.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Things to always include as flags. Change as needed.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  

# Set debug/coverage flags, or optimize, depending on options.
if (debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    # Coverage can only be set if -g is used.
else ()
    # Optimize flag for production code. Change as needed.
    set(CMAKE_CXX_FLAGS "-O2")
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)