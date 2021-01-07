cmake_minimum_required(VERSION 3.10)
project(DSProtocol)

# Library Setup
add_subdirectory(vendor/github.com/google/googletest)


# Unit Test Setup
include_directories(.)

set(TEST_BINARY ${CMAKE_PROJECT_NAME}_tst)
set(TEST_SOURCES 
    test/main.cpp
    test/test.cpp
)

add_executable(${TEST_BINARY} ${TEST_SOURCES})

enable_testing()
add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
target_link_libraries(${TEST_BINARY} PUBLIC gtest)
