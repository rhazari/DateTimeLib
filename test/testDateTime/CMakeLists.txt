file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(DateTime ${SRCS})

TARGET_LINK_LIBRARIES(DateTime
    lib
    libgtest
    libgmock
)

add_test(NAME DateTime
         COMMAND DateTime)