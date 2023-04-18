cmake_minimum_required(VERSION 3.12)

set(APP_PROJECT_NAME Application)

add_executable(${APP_PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${APP_PROJECT_NAME} EngineCore ImGui glm)
target_compile_features(${APP_PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${APP_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${APP_PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${APP_PROJECT_NAME}>/res) 