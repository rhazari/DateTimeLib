file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(DateTimeLibraryTest ${SRCS})

TARGET_LINK_LIBRARIES(
    DateTimeLibraryTest
    DATE_TIME_LIB
    libgtest
    libgmock
)

add_test(NAME DateTimeLibraryTest
         COMMAND DateTimeLibraryTest)