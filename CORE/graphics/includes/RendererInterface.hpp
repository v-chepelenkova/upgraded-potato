#pragma once
#include <memory>
#include <iostream>
#include <chrono>
#include "../../utils/json/json.hpp"

#include "Rendering/Material.hpp"
#include "Rendering/RendererOpenGL.hpp"
#include "Rendering/ShaderContainer.hpp"
#include "Rendering/Primitives/Plane.hpp"
#include "Rendering/Primitives/Sphere.hpp"
#include "Rendering/Primitives/Line.hpp"
#include "Rendering/Primitives/Cube.hpp"

#include "Event.hpp"
#include "Camera.hpp"

#include <string>

#include "Window.h"
#include "Event.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "ResourceManager.hpp"

using json = nlohmann::json;

namespace Engine {
	struct DrawingObject {
		DrawingObject(	const std::string& ID,
						const std::shared_ptr<PrimitiveObject>& primitive,
						const std::shared_ptr<Material>& material,
						const std::shared_ptr<ShaderProgram>& shader_program,
						const glm::vec3& position,
						const glm::vec3& rotation,
						const std::string& type,
						const float& scale);
		
		~DrawingObject();
		
		void Draw();
		
		void SetPosition(const glm::vec3& new_position);
		void SetScale(const float& new_scale);

		void SetDrawTrackingLine(const bool flag);

		std::string m_ID;
		std::shared_ptr<PrimitiveObject> m_primitive; // expand later for non primitive meshes
		std::shared_ptr<Material> m_material;
		std::shared_ptr<ShaderProgram> m_shader_program;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		std::unique_ptr<Line> m_tracking_line = nullptr;
		bool m_draw_tracking_line = false;
		std::string m_ls_type;
		float m_scale = 1;
	};

	static glm::vec3 vecToGLMVec(const std::vector<float> vec);
	static glm::vec3 vecToGLMVec(const float* vec);

	class RenderingInterface {
	public:
		RenderingInterface( unsigned int window_width,
							unsigned int window_height,
							const char* title,
							const std::string& abs_path);

		virtual ~RenderingInterface();

		RenderingInterface(const RenderingInterface&) = delete;
		RenderingInterface(RenderingInterface&&) = delete;
		RenderingInterface& operator=(const RenderingInterface&) = delete;
		RenderingInterface& operator=(RenderingInterface&&) = delete;

		virtual void ConfigureObjects(const json& configuration_data);

		virtual void Draw(const json& rendering_objects);

		virtual void FreeResources();

		bool getWindowState() const { return mbCloseWindow; };

	private:
		void InitializePrimitives();
		
		void InitializeCamera(const json& camera_config);

		void GenerateQuadsTexture(	unsigned char* data,
									const unsigned int width,
									const unsigned int height);
		
		std::unique_ptr<DrawingObject> AssembleDrawingObject(const json& object_config);

		int m_window_width;
		int m_window_height;
		const std::string m_absolute_path;
		
		void close() { mbCloseWindow = true; };

		virtual void onMouseButtonEvent(const MouseButton button, const double xPos, const double yPos, const bool pressed) {};

		glm::vec2 getCurrentCursorPosition() const;

		// lightning parameters
		glm::vec3 light_source_pos = { 0.f, 0.f, 0.f };
		glm::vec3 light_source_color = { 1.f, 1.f, 0.f};
		float ls_brightness = 15;
		bool m_light_source_found = false;

		float ambient_factor = 0.2f;
		float diffuse_factor = 1.f;
		float specular_factor = 1.f;
		float shininess = 5.f;

		bool perspectiveCamera = true;
		Camera m_camera;

		std::shared_ptr<class Window> mpWindow;
		EventDispatcher mEventDispatcher;
		bool mbCloseWindow = false;

		std::map<std::string, std::unique_ptr<DrawingObject>> m_drawing_objects; // {ID : DrawingObj}

		// primitives
		// shaders
		std::shared_ptr<ShaderProgram> pSP_light_source; // light source shader
		std::shared_ptr<ShaderProgram> pSP_basic; // basic shader with simple lightning

		std::shared_ptr<ShaderProgram> pSP_line;

		// materials
		std::shared_ptr<Material> basic_material;
		std::shared_ptr<Material> plane_material;

		// textures example
		std::shared_ptr<Texture2D> p_texture_moon;
		std::shared_ptr<Texture2D> p_texture_quads;

		// line primitive
		//std::vector<std::shared_ptr<Line>> lines(N_spheres);

		// cube primitive
		std::shared_ptr<Cube> p_cube;

		// plane primitive
		std::shared_ptr<Plane> p_plane;

		// spheres
		std::shared_ptr<Sphere> p_basic_sphere; // NOT a light source sphere
		std::shared_ptr<Sphere> p_ls_sphere; // light source sphere
	};
}