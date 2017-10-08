set(lib_SRCS
    DateTime.h
    DateTime.cpp
)

# Declare the library
add_library(lib STATIC
    ${lib_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)