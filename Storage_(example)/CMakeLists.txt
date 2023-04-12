cmake_minimum_required(VERSION 3.10)
project(StorageExample)

set(CMAKE_CXX_STANDARD 17)

# Put executable in Simulators folder 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Simulators)

# Collect .cpp files inside this simulator directory
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# Set variable that tells where to find headers
set(CURRENT_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES}
                                ${PROJECT_SOURCE_DIR}/events
                                ${PROJECT_SOURCE_DIR}/objects/include
                                ${PROJECT_SOURCE_DIR}/model
                                ${PROJECT_SOURCE_DIR}/view
                                ${PROJECT_SOURCE_DIR}/controller
                                ${PROJECT_SOURCE_DIR}/lib
        )

#message("\nShowing Cmake variables:")
#message("CURRENT_INCLUDE_DIRECTORIES = " ${CURRENT_INCLUDE_DIRECTORIES})
#message("PROJECT_NAME = " ${PROJECT_NAME})
#message("PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
#message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})
#message("SOURCES: " ${SOURCES})
#message("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})
#message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} "\n")

# Create target
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CURRENT_INCLUDE_DIRECTORIES})
