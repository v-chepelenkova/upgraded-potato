cmake_minimum_required(VERSION 3.10)
project(json_test)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES timer.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})