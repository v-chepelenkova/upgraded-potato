cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME EngineCore)

set(ENGINE_PUBLIC_INCLUDES
	includes/Application.h
	includes/Event.hpp
	includes/Camera.hpp
	includes/Keys.hpp
	includes/Input.hpp
	includes/Log.hpp
	includes/ResourceManager.hpp
	includes/stb_image.h
)

set(ENGINE_PRIVATE_INCLUDES
	includes/Window.h
	includes/Modules/UIModule.hpp
	includes/Rendering/ShaderProgram.hpp
	includes/Rendering/VertexBuffer.hpp
	includes/Rendering/VertexArray.hpp
	includes/Rendering/IndexBuffer.h
	includes/Rendering/RendererOpenGL.hpp
	includes/Rendering/Texture2D.hpp
	includes/Rendering/ShaderContainer.hpp
	includes/Rendering/Material.hpp
	
	includes/Rendering/Primitives/PrimitiveObject.hpp
	includes/Rendering/Primitives/Plane.hpp
	includes/Rendering/Primitives/Sphere.hpp
	includes/Rendering/Primitives/Cube.hpp
	includes/Rendering/Primitives/Line.hpp
)

set(ENGINE_PRIVATE_SOURCES
	src/ResourceManager.cpp
	src/Application.cpp
	src/Window.cpp
	src/Input.cpp
	src/Modules/UIModule.cpp
	src/Camera.cpp
	src/Rendering/ShaderProgram.cpp
	src/Rendering/VertexBuffer.cpp
	src/Rendering/VertexArray.cpp
	src/Rendering/IndexBuffer.cpp
	src/Rendering/RendererOpenGL.cpp
	src/Rendering/Texture2D.cpp
	src/Rendering/ShaderContainer.cpp
	src/Rendering/Material.cpp
	
	src/Rendering/Primitives/PrimitiveObject.cpp
	src/Rendering/Primitives/Plane.cpp
	src/Rendering/Primitives/Sphere.cpp
	src/Rendering/Primitives/Cube.cpp
	src/Rendering/Primitives/Line.cpp
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)


add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
	${ENGINE_ALL_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)


set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h
	
	../external/implot/implot.h
	../external/implot/implot_internal.h
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/imgui_demo.cpp
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_tables.cpp
	
	../external/implot/implot.cpp
	../external/implot/implot_demo.cpp
	../external/implot/implot_items.cpp
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
#target_include_directories(ImGui PUBLIC ../external/implot)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)