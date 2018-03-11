set(DATE_TIME_LIB_SRCS
    DateTime.h
    DateTime.cpp
)

# Declare the library
add_library(DATE_TIME_LIB STATIC
    ${DATE_TIME_LIB_SRCS}
)

target_link_libraries(DATE_TIME_LIB)

# Specify here the include directories exported
# by this library
target_include_directories(DATE_TIME_LIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)