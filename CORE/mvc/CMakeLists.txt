cmake_minimum_required(VERSION 3.10)
project(MVC)

set(SOURCES sim_object.cpp)
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})