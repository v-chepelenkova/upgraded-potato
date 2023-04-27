cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 17)

# Put executable in Simulators folder 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Simulators)

# Collect .cpp files inside this simulator directory
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# Set variable that tells where to find headers
set(CURRENT_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES}
                                ${PROJECT_SOURCE_DIR}/model
                                ${PROJECT_SOURCE_DIR}/view
                                ${PROJECT_SOURCE_DIR}/controller
        )

# Create target
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CURRENT_INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME} MVC utils EngineCore ImGui glm)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)