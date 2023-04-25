#pragma once

#include <memory>
#include "Event.hpp"
#include "Camera.hpp"
#include "Rendering/Material.hpp"


namespace Engine {
	class Application {
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

        virtual int initialize(unsigned int window_width, unsigned int
        window_height, const char* title, const std::string& abs_path);

		virtual int start();
		
		void close() { mbCloseWindow = true; };

		virtual void onUpdate() {};

		virtual void onUiDraw() {};

		virtual void onMouseButtonEvent(const MouseButton button, const double xPos, const double yPos, const bool pressed) {};

		glm::vec2 getCurrentCursorPosition() const;

		float cameraPosition[3] = { 0.f, 0.f, 0.f };
		float cameraRotation[3] = { 0.f, 0.f, 0.f };

		// lightning parameters
		float light_source_pos[3] = { 0.f, 0.f, 0.f };
		float light_source_color[3] = {1.f, 1.f, 1.f};
		float ls_brightness = 15;

		float ambient_factor = 0.2f;
		float diffuse_factor = 1.f;
		float specular_factor = 1.f;
		float shininess = 5.f;

		bool is_disco = false;

		float camera_fov = 60.f;
		float camera_near_plane = 0.1f;
		float camera_far_plane = 100.f;

		bool perspectiveCamera = true;
		Camera camera{ glm::vec3(-20.f, 0.f, 10.f) }; // starting position of camera

		const double FPS = 90;

	private:
		void draw(double currrent_time);
		std::shared_ptr<class Window> mpWindow;
		EventDispatcher mEventDispatcher;
		bool mbCloseWindow = false;

	};
}