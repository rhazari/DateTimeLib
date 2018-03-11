add_subdirectory(DateTimeLibrary)

add_executable (main main.cpp)

target_link_libraries (main DATE_TIME_LIB)