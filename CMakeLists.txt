cmake_minimum_required(VERSION 3.17)

project(maze)

set(CXX_STANDARD 20)

set(SRC_DIR src)
set(TEST_DIR tests)

set(SRC
    ${SRC_DIR}/maze.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} -lpng)

find_package(Catch2 REQUIRED)
set(TEST
    ${TEST_DIR}/tests.cpp
    ${TEST_DIR}/maze.cpp
)
add_executable(tests ${TEST})
target_link_libraries(tests Catch2::Catch2 ${PROJECT_NAME})
