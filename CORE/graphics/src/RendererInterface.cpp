#include "RendererInterface.hpp"

#include "Modules/UIModule.hpp"

#include <imgui/imgui.h>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>
#include <GLFW/glfw3.h>


namespace Engine {
	RenderingInterface::RenderingInterface( unsigned int window_width,
											unsigned int window_height,
											const char* title,
											const std::string& abs_path) :
		m_window_height(window_height),
		m_window_width(window_width),
		m_absolute_path(abs_path)
	{
		// instantiate THE WINDOW
        ResourceManager::setExecutablePath(m_absolute_path);
        
        // Making the window itself
        mpWindow = std::make_shared<Window>(title, m_window_width, m_window_height);
        
        // Setting up a camera viewport
        m_camera.setViewportSize( static_cast<float>(m_window_width),
                                static_cast<float>(m_window_height));


        // Events ( add new event callback here and event itself in Event class)
        
        // Mouse movement callback
        mEventDispatcher.addEventListener<EventMouseMoved>(
            [](EventMouseMoved& event) {
                //LOG_INFO("[MouseMoved] Mouse moved to {0} x {1}", event.x, event.y);
            }
        );

        // Window resize callback
        mEventDispatcher.addEventListener<EventWindowResize>(
            [&](EventWindowResize& event) {
                LOG_INFO("[WindowResized] Changed size to {0} x {1}",
                    event.width, 
                    event.height
                );
                m_camera.setViewportSize(event.width, event.height);
                //draw();
            }
        );

        // Window close callback
        mEventDispatcher.addEventListener<EventWindowClose>(
            [&](EventWindowClose& event) {
                LOG_INFO("[WindowClose]");
                close();
            }
        );

        // Keyboard Key pressed callback
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

        // Keyboard Key released callback
        mEventDispatcher.addEventListener<EventKeyReleased>(
            [&](EventKeyReleased& event) {

                if (event.keycode <= KeyCode::KEY_Z) {
                    LOG_INFO("[KEY RELEASED] {0}", static_cast<char>(event.keycode));
                }
                Input::releaseKey(event.keycode);
            }
        );

        // Mouse button pressed callback
        mEventDispatcher.addEventListener<EventMouseButtonPressed>(
            [&](EventMouseButtonPressed& event) {
                LOG_INFO("[MOUSE BUTTON PRESSED: {0} AT {1}x{2}]", static_cast<int>(event.mouseButton), event.xPos, event.yPos);
                Input::pressMouseButton(event.mouseButton);
                onMouseButtonEvent(event.mouseButton, event.xPos, event.yPos, true);
            }
        );

        // Mouse button released callback
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

        // Initialization of primitives, shaders, materials
        InitializePrimitives();

        LOG_INFO("Renderer initialization is complete");
	}

	RenderingInterface::~RenderingInterface() {

	}

	void RenderingInterface::ConfigureObjects(const json& configuration_data) {
		// ADD JSON VALIDATION IN DA CASE OF A CORRUPTED configuration_data
        // for now we assume that json has correct format and has all the field required (bad assumption)

        // objects initialization here
        InitializeCamera(configuration_data["SCENE"]["CAMERA"].get<json>());

        
        for (const auto& obj : configuration_data["OBJECTS"].get<json>()) {
            std::string ID = obj["ID"].get<std::string>(); // ID
            auto drawing_obj = AssembleDrawingObject(obj);
            if (drawing_obj != nullptr) {
                m_drawing_objects.emplace(ID, std::move(drawing_obj));
            }
            else {
                LOG_ERROR("Cannot configure an object with ID : ", ID);
                continue;
            }
        }
       
	}

	void RenderingInterface::Draw(const json& rendering_objects) {
        RendererOpenGL::setClearColor(0.33, 0.33, 0.33, 1);
        RendererOpenGL::clear();
        // object dwaring here
		// rendering objects has a structure of {ID : position}
        for (const auto& obj : rendering_objects) {
            glm::vec3 position = STDVecToGLMVec(obj["coordinates"].get<std::vector<float>>());
            std::string curr_ID = obj["ID"].get<std::string>();
            m_drawing_objects.find(curr_ID)->second->SetPosition(position);
            m_drawing_objects.find(curr_ID)->second->Draw();
        }
        mpWindow->onUpdate();
	}

	void RenderingInterface::FreeResources() {
        ResourceManager::unloadAllResources();
        mpWindow = nullptr;
	}

    void RenderingInterface::InitializePrimitives() {
        p_texture_quads = ResourceManager::loadTexture("Face", "res/textures/obamna.png");
        p_texture_moon = ResourceManager::loadTexture("Moon", "res/textures/obama_sphere.png");
        
        basic_material = std::make_shared<Material>(ambient_factor, diffuse_factor, specular_factor, shininess, p_texture_quads);
        plane_material = std::make_shared<Material>(ambient_factor, diffuse_factor, 2 * specular_factor, 2 * shininess, p_texture_moon);

        p_cube = std::make_shared<Cube>(glm::vec3(0, 0, 0), 1, 1, 1);
        p_ls_sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1);
        p_basic_sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1);
        p_plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), 1.f, 1.f);

        // Shaders compilation section

        pSP_line = std::make_shared<ShaderProgram>(Shaders::line_vertex, Shaders::line_fragment);
        if (!pSP_line->isCompiled())
        {
            LOG_CRITICAL("Line shader compilation error");
            return; // maybe throw an exception later
        }

        // basic shader program with simple lighning
        pSP_basic = ResourceManager::loadShaders("Default", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pSP_basic->isCompiled()) {
            LOG_CRITICAL("Basic shader compilation error");
            return; // maybe throw an exception later
        }

        // Light source shader program
        pSP_light_source = std::make_shared<ShaderProgram>(Shaders::vertex_shader_light_source, Shaders::fragment_shader_light_source);
        if (!pSP_light_source->isCompiled()) {
            LOG_CRITICAL("Light source shader compilation error");
            return; // maybe throw an exception later
        }

        RendererOpenGL::enableDepthBuffer();
    }

    void RenderingInterface::InitializeCamera(const json& camera_config) {
        auto position = camera_config["position"].get<std::vector<float>>();
        auto rotation = camera_config["rotation"].get<std::vector<float>>();
        float fov = camera_config["fov"].get<float>();
        float near_plane = camera_config["near_plane"].get<float>();
        float far_plane = camera_config["far_plane"].get<float>();
        m_camera.setFieldOfView(fov);
        m_camera.setFarClipPlane(far_plane);
        m_camera.setNearClipPlane(near_plane);
        m_camera.setPositionRotation(STDVecToGLMVec(position), STDVecToGLMVec(rotation));
    }

    void RenderingInterface::GenerateQuadsTexture(  unsigned char* data,
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

    std::unique_ptr<DrawingObject> RenderingInterface::AssembleDrawingObject(const json& object_config)
    {
        std::string ID = object_config["ID"].get<std::string>(); // ID
        std::string type = object_config["ATTRIBUTES"]["type"].get<std::string>(); // shader type
        float radius = object_config["ATTRIBUTES"]["radius"].get<float>(); // radius (scale)
        auto position = object_config["ATTRIBUTES"]["coordinates"].get<std::vector<float>>(); // position
        //auto rotation = object_config["ATTRIBUTES"]["rotation"].get<std::vector<float>>(); // unnecessary

        std::string model = object_config["ATTRIBUTES"]["GRAPHICS"]["model"].get<std::string>(); // primitive
        std::string texture_path = object_config["ATTRIBUTES"]["GRAPHICS"]["texture"].get<std::string>(); // texture path
        std::string material = object_config["ATTRIBUTES"]["GRAPHICS"]["material"].get<std::string>(); // material

        auto texture = ResourceManager::loadTexture(ID, texture_path);

        std::shared_ptr<ShaderProgram> shader_program;
        if (material == "light_source") {
            shader_program = pSP_light_source;
        }
        else if (material == "default") {
            shader_program = pSP_basic;
        }
        else {
            LOG_ERROR("Unknown material type - ", material);
            return nullptr;
        }

        // switch to enum class later on
        // for now we stick with hardcore if-else

        std::shared_ptr<PrimitiveObject> primitive;

        if (model == "sphere") {
            if (material == "light_source") {
                primitive = p_ls_sphere;
            }
            else{
                primitive = p_basic_sphere;
            }
        }
        else if (model == "cube") {
            primitive = p_cube;
        }
        else if (model == "plane") {
            primitive = p_plane;
        }
        else {
            // custom mesh
            // only primitives are allowed for now
            LOG_ERROR("Unknown primitive model type - ", model);
            return nullptr;
        }
        glm::vec3 glm_pos = glm::vec3{ position[0], position[1], position[2] };
        return std::make_unique<DrawingObject>(ID, primitive, basic_material, shader_program, glm_pos, glm::vec3{ 0.f, 0.f, 0.f });
    }

    glm::vec2 RenderingInterface::getCurrentCursorPosition() const {
        return mpWindow->getCurrentCursorPosition();
    }



	// ===================== DRAWING OBJECT ===================== //
    DrawingObject::DrawingObject(const std::string& ID,
                                 std::shared_ptr<PrimitiveObject>& primitive,
                                 std::shared_ptr<Material>& material,
                                 std::shared_ptr<ShaderProgram>& shader_program,
                                 const glm::vec3& position,
                                 const glm::vec3& rotation) :
        m_ID(ID),
        m_primitive(primitive),
        m_material(material),
        m_shader_program(shader_program),
        m_position(position),
        m_rotation(rotation)
    {
        m_primitive->setShaderProgram(shader_program);
        m_primitive->setPosition(m_position);
    }

    DrawingObject::~DrawingObject() {
        m_material = nullptr;
        m_primitive = nullptr;
        m_tracking_line = nullptr;
        m_shader_program = nullptr;
    }

    void DrawingObject::Draw() {
        m_shader_program->bind();
        m_primitive->setMaterial(m_material);
        if (m_material->m_texture != nullptr) {
            m_material->m_texture->bind(0);
        }
        m_primitive->draw();
    }

    void DrawingObject::SetPosition(const glm::vec3& new_position) {
        m_position = new_position;
        m_primitive->setPosition(new_position);
    }
    
    glm::vec3 STDVecToGLMVec(const std::vector<float> vec)
    {
        if (vec.size() != 3) {
            LOG_ERROR("STDVecToGLMVec: Vector must have exactly 3 elements!");
            return glm::vec3(0.f, 0.f, 0.f);
        }
        return glm::vec3{vec[0], vec[1], vec[2]};
    }
}