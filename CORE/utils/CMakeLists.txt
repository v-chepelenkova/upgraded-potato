cmake_minimum_required(VERSION 3.10)

project(utils)

set(UTILS_INCLUDES
    json
    timer
)

set(UTILS_SOURCES
    timer/timer.cpp
)

set(UTILS_ALL_SOURCES
	${UTILS_INCLUDES}
	${UTILS_SOURCES}
)

add_library(${PROJECT_NAME} STATIC ${UTILS_ALL_SOURCES})

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
# 	${UTILS_ALL_SOURCES}
# )

target_include_directories(${PROJECT_NAME} PUBLIC ${UTILS_INCLUDES})