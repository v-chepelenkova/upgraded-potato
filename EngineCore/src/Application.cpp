#include <iostream>
#include <chrono>

#include "Application.h"

#include "Window.h"
#include "Event.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "ResourceManager.hpp"

#include "Rendering/ShaderContainer.hpp"
#include "Rendering/Primitives/Plane.hpp"
#include "Rendering/Primitives/Sphere.hpp"
#include "Rendering/Primitives/Cube.hpp"

#include "Modules/UIModule.hpp"

#include <imgui/imgui.h>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>
#include <GLFW/glfw3.h>

namespace Engine {
	const float textScaleS = 10;

	//------------------------- TEST FUNCTIONS FOR SIMPLE TEXTURE GENERATION --------------//
	void generate_quads_texture(unsigned char* data,
		const unsigned int width,
		const unsigned int height)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				if ((x < width / 2 && y < height / 2) || x >= width / 2 && y >= height / 2)
				{
					data[3 * (x + width * y) + 0] = 0;
					data[3 * (x + width * y) + 1] = 0;
					data[3 * (x + width * y) + 2] = 0;
				}
				else
				{
					data[3 * (x + width * y) + 0] = 255;
					data[3 * (x + width * y) + 1] = 0;
					data[3 * (x + width * y) + 2] = 220;
				}
			}
		}
	}
	//---------------------------------------//

	// shaders example
	std::shared_ptr<ShaderProgram> pSP_light_source; // light source shader
	std::shared_ptr<ShaderProgram> pSP_basic; // basic shader with simple lightning
	
	// materials example
	std::shared_ptr<Material> basic_material;
	std::shared_ptr<Material> plane_material;
	
	// textures example
	std::shared_ptr<Texture2D> p_texture_smile;
	std::shared_ptr<Texture2D> p_texture_quads;

	// cube example
	std::shared_ptr<Cube> example_cube;

	// plane example
	std::shared_ptr<Plane> example_plane;
	
	// sphere example
	std::shared_ptr<Sphere> example_sphere;
	std::shared_ptr<Sphere> ls_sphere;

	float mBackgroundColor[4] = { 0.33f, 0.33f, 0.33f, 0.f };

	Application::Application() {
		LOG_INFO("Starting application");
	}

	Application::~Application() {
		LOG_INFO("Closing application");
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char* title, const char* abs_path)
	{	
		ResourceManager::setExecutablePath(abs_path);
		const double updateTime = 1e6 / FPS;
		// making a window
		mpWindow = std::make_shared<Window>(title, window_width, window_height);
		// setting up a camera viewport
		camera.setViewportSize(static_cast<float>(window_width), static_cast<float>(window_height));
		
		// Events ( add new event callback here and event itself in Event class)
		mEventDispatcher.addEventListener<EventMouseMoved>(
			[](EventMouseMoved& event) {
				//LOG_INFO("[MouseMoved] Mouse moved to {0} x {1}", event.x, event.y);
			}
		);

		mEventDispatcher.addEventListener<EventWindowResize>(
			[&](EventWindowResize& event) {
				LOG_INFO("[WindowResized] Changed size to {0} x {1}", event.width, event.height);
				camera.setViewportSize(event.width, event.height);
				//draw();
			}
		);

		mEventDispatcher.addEventListener<EventWindowClose>(
			[&](EventWindowClose& event) {
				LOG_INFO("[WindowClose]");
				close();
			}
		);

		mEventDispatcher.addEventListener<EventKeyPressed>(
			[&](EventKeyPressed& event) {
				
				if (event.keycode <= KeyCode::KEY_Z) {
					if (event.repeated) {
						LOG_INFO("[KEY PRESSED] {0}, repeated", (char)event.keycode);
					}
					else {
						LOG_INFO("[KEY PRESSED] {0}", static_cast<char>(event.keycode));
					}
				}
				Input::pressKey(event.keycode);
			}
		);

		mEventDispatcher.addEventListener<EventKeyReleased>(
			[&](EventKeyReleased& event) {
				
				if (event.keycode <= KeyCode::KEY_Z) {
					LOG_INFO("[KEY RELEASED] {0}", static_cast<char>(event.keycode));
				}
				Input::releaseKey(event.keycode);
			}
		);
		// Mouse event
		mEventDispatcher.addEventListener<EventMouseButtonPressed>(
			[&](EventMouseButtonPressed& event) {
				LOG_INFO("[MOUSE BUTTON PRESSED: {0} AT {1}x{2}]", static_cast<int>(event.mouseButton), event.xPos, event.yPos);
				Input::pressMouseButton(event.mouseButton);
				onMouseButtonEvent(event.mouseButton, event.xPos, event.yPos, true);
			}
		);

		mEventDispatcher.addEventListener<EventMouseButtonReleased>(
			[&](EventMouseButtonReleased& event) {
				LOG_INFO("[MOUSE BUTTON RELEASED: {0} AT {1}x{2}]", static_cast<int>(event.mouseButton), event.xPos, event.yPos);
				Input::releaseMouseButton(event.mouseButton);
				onMouseButtonEvent(event.mouseButton, event.xPos, event.yPos, false);
			}
		);

		mpWindow->set_event_callback(
			[&](BaseEvent& event) {
				mEventDispatcher.dispatch(event);
			}
		);

		// various stuff initialization

		const unsigned int width = 1000;
		const unsigned int height = 1000;
		const unsigned int channels = 3;
		
		// textures generation
		auto* data = new unsigned char[width * height * channels];
		
		generate_quads_texture(data, width, height);
		//p_texture_quads = std::make_shared<Texture2D>(data, width, height);
		p_texture_quads = ResourceManager::loadTexture("Earth", "res\\textures\\earth2048.bmp");
		p_texture_quads->bind(0);

		delete[] data; // cleaning up texture data
		
		// Compiling shader programs
		
		// basic shader program with simple lighning
		pSP_basic = ResourceManager::loadShaders("Default", "res\\shaders\\vertex.txt", "res\\shaders\\fragment.txt");
		if (!pSP_basic->isCompiled())
		{
			return false;
		}

		// Light source shader program
		pSP_light_source = std::make_shared<ShaderProgram>(Shaders::vertex_shader_light_source, Shaders::fragment_shader_light_source);
		if (!pSP_light_source->isCompiled())
		{
			return false;
		}

		// material init
		basic_material = std::make_shared<Material>(ambient_factor, diffuse_factor, specular_factor, shininess);
		plane_material = std::make_shared<Material>(ambient_factor, diffuse_factor, 2* specular_factor, 2* shininess);
		
		// Initializing cube
		example_cube = std::make_shared<Cube>(glm::vec3(0, 0, 0), 1, 1, 1);
		example_cube->setMaterial(plane_material);
		example_cube->setShaderProgram(pSP_basic);

		ls_sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1);
		ls_sphere->setShaderProgram(pSP_light_source);

		// Initializing plane
		example_plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), 100.f, 100.f);
		example_plane->setMaterial(plane_material);
		example_plane->setShaderProgram(pSP_basic);
		example_plane->setPosition(glm::vec3(0.f, 0.f, -5.f));

		// Initializing sphere
		example_sphere = std::make_shared<Sphere>(glm::vec3(10, 0, 2), 1.f);
		example_sphere->setMaterial(plane_material);
		example_sphere->setShaderProgram(pSP_basic);

		RendererOpenGL::enableDepthBuffer();
		

		auto begin = std::chrono::steady_clock::now();
		auto program_start_time = begin;
		auto end = std::chrono::steady_clock::now();

		auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

		// main cycle
		while (!mbCloseWindow) {
			elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			auto program_uptime = std::chrono::duration_cast<std::chrono::milliseconds>(end - program_start_time).count();
			if (elapsed_ms > updateTime) {
				begin = end;
				draw(program_uptime);
			}
			end = std::chrono::steady_clock::now();
		}
		ResourceManager::unloadAllResources();
		mpWindow = nullptr;

		return 0;
	}

	glm::vec2 Application::getCurrentCursorPosition() const {
		return mpWindow->getCurrentCursorPosition();
	}
	
	void Application::draw(double currrent_time) {
		RendererOpenGL::setClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], mBackgroundColor[3]);
		RendererOpenGL::clear();
		
		// view_projection matrix
		glm::mat4 view_projection_matrix = camera.getProjectionMatrix() * camera.getViewMatrix();

		// activating basic shader
		pSP_basic->bind();
		// set view projection matrix for basic shader
		pSP_basic->setMatrix4("view_projection_matrix", view_projection_matrix);
		// set camera position for basic shader
		pSP_basic->setVec3("camera_position", camera.getPosition());
		// set light source params for basic shader
		pSP_basic->setVec3("light_position", glm::vec3(light_source_pos[0], light_source_pos[1], light_source_pos[2]));
		pSP_basic->setVec3("light_color", glm::vec3(ls_brightness * light_source_color[0], ls_brightness * light_source_color[1], ls_brightness * light_source_color[2]));
		
		float rotate_in_radians = glm::radians(10.f);
		glm::mat4 rotateMatrix;
		glm::mat4 translateMatrix;
		
		// rendering cubes

		//example_cube->setModelMatrix(modelMatrix);
		unsigned int scale = 1;
		unsigned int n_cubes = 10;
		for (int i = 0; i < n_cubes; i++)
		{
			glm::mat4 translate_matrix( scale, 0, 0, 0,
										0, scale, 0, 0,
										0, 0, scale, 0,
										0, 0, 5 + 1.5*scale, 1);
			
			rotate_in_radians = glm::radians(currrent_time / (scale + 5));
			rotateMatrix = glm::mat4(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
									-sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
									 0, 0, 1, 0,
									 0, 0, 0, 1);

			// set new position for a cube
			example_cube->setModelMatrix(translate_matrix * rotateMatrix);
			example_cube->draw();
			scale *= 2;
		}

		// rendering plane
		example_plane->draw();
		
		
		// rendering spheres
		
		float R = 10.f;
		float period = 5.f;
		float vel = 2 * glm::radians(180.0) * R / period;
		
		float pulse = 1.01;// +glm::cos((2 * 3.14159265 * 1.f) * currrent_time * 1e-3);
		
		for (size_t i = 1; i < 20; i++)
		{
			R = 5 + 2*i;
			translateMatrix = glm::mat4(pulse, 0, 0, 0,
										0, pulse, 0, 0,
										0, 0, pulse, 0,
										R * glm::cos(vel / R * currrent_time * 1e-3 + 2.1415f * i), R * glm::sin(vel / R * currrent_time * 1e-3 + 2.1415f*i), 0, 1);

			example_sphere->setModelMatrix(translateMatrix);
			example_sphere->draw();
		}
		

		// rendering light source
		{
			pSP_light_source->bind();
			pSP_light_source->setMatrix4("view_projection_matrix", camera.getProjectionMatrix() * camera.getViewMatrix());
			if (is_disco) {
				float T = currrent_time * 1e-3;
				float caramel_dancen[3] = {1.f / 2.f * (1 + glm::cos(T / 0.1f)), 1.f / 2.f * (1 - glm::cos(T / 0.1f)), 1.f / 2.f * (1 + glm::sin(T / 0.1f))};
			
				light_source_color[0] = caramel_dancen[0];
				light_source_color[1] = caramel_dancen[1];
				light_source_color[2] = caramel_dancen[2];
			}
			pSP_light_source->setVec3("light_color", glm::vec3(light_source_color[0], light_source_color[1], light_source_color[2]));

			scale = 4;
			glm::mat4 translate_matrix(	scale, 0, 0, 0,
										0, scale, 0, 0,
										0, 0, scale, 0,
										light_source_pos[0], light_source_pos[1], light_source_pos[2], 1);
			ls_sphere->setModelMatrix(translate_matrix);
			ls_sphere->draw();
		}

		UIModule::onUiDrawBegin();
		onUiDraw();
		UIModule::onUiDrawEnd();

		mpWindow->onUpdate();
		onUpdate();
	}
}