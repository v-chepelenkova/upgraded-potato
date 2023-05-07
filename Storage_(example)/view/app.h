#pragma once

#include <memory>
#include <Application.h>
#include <Input.hpp>
#include <imgui/imgui.h>
#include <imgui_internal.h>

//#include <implot/implot_demo.cpp>

class App : public Engine::Application {
  double mInitialMousePosX = 0;
  double mInitialMousePosY = 0;
  float camera_speed = 10.0f / FPS;
  float rotation_speed = 90.0f / FPS;

  float speed_multiplier = 1.0;

  virtual void onUpdate() override {
    glm::vec3 movementDelta{ 0, 0, 0 };
    glm::vec3 rotationDelta{ 0, 0, 0 };



    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_W)) {
      movementDelta.x += camera_speed * speed_multiplier;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_S)) {
      movementDelta.x -= camera_speed * speed_multiplier;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_A)) {
      movementDelta.y -= camera_speed * speed_multiplier;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_D)) {
      movementDelta.y += camera_speed * speed_multiplier;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_R)) {
      movementDelta.z += camera_speed * speed_multiplier;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_F)) {
      movementDelta.z -= camera_speed * speed_multiplier;
    }

    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_COMMA)) {
      if (speed_multiplier > 1e-3) {
        speed_multiplier *= 0.95f;
      }
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_PERIOD)) {
      if (speed_multiplier < 1e3) {
        speed_multiplier *= 1.05f;
      }
    }

    // rotation
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_UP)) {
      rotationDelta.y -= rotation_speed;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_DOWN)) {
      rotationDelta.y += rotation_speed;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_RIGHT)) {
      rotationDelta.z -= rotation_speed;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_LEFT)) {
      rotationDelta.z += rotation_speed;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_Q))
    {
      rotationDelta.x -= rotation_speed;
    }
    if (Engine::Input::isKeyPressed(Engine::KeyCode::KEY_E))
    {
      rotationDelta.x += rotation_speed;
    }

    // rotate camera with a mouse using RMB
    if (Engine::Input::isMouseButtonPressed(Engine::MouseButton::MOUSE_BUTTON_RIGHT)) {
      // pan camera with two buttons pressed
      glm::vec2 currentCursorPosition = getCurrentCursorPosition();

      if (Engine::Input::isMouseButtonPressed(Engine::MouseButton::MOUSE_BUTTON_LEFT)) {
        camera.moveRight(static_cast<float>(-mInitialMousePosX + currentCursorPosition.x) / 100.0f);
        camera.moveUp(static_cast<float>(mInitialMousePosY - currentCursorPosition.y) / 100.0f);
      }
      else {
        rotationDelta.z += static_cast<float>(mInitialMousePosX - currentCursorPosition.x) / 5.0f; // yaw
        rotationDelta.y -= static_cast<float>(mInitialMousePosY - currentCursorPosition.y) / 5.0f; // pitch
      }

      mInitialMousePosX = currentCursorPosition.x;
      mInitialMousePosY = currentCursorPosition.y;
    }

    camera.addMovementAndRotation(movementDelta, rotationDelta);
  }

  void setupDockspaceMenu()
  {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton;
    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiIO& io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("New Scene...", NULL))
        {

        }
        if (ImGui::MenuItem("Open Scene...", NULL))
        {

        }
        if (ImGui::MenuItem("Save Scene...", NULL))
        {

        }
        ImGui::Separator();
        if (ImGui::MenuItem("Exit", NULL))
        {
          close();
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::End();
  }

  virtual void onMouseButtonEvent(const Engine::MouseButton button, const double xPos, const double yPos, const bool pressed) override {
    mInitialMousePosX = xPos;
    mInitialMousePosY = yPos;
  }

  virtual void onUiDraw() override
  {
    setupDockspaceMenu();
    cameraPosition[0] = camera.getCameraPosition().x;
    cameraPosition[1] = camera.getCameraPosition().y;
    cameraPosition[2] = camera.getCameraPosition().z;
    cameraRotation[0] = camera.getCameraRotation().x;
    cameraRotation[1] = camera.getCameraRotation().y;
    cameraRotation[2] = camera.getCameraRotation().z;

    camera_fov = camera.getFieldOfView();
    camera_near_plane = camera.getNearClipPlane();
    camera_far_plane = camera.getFarClipPlane();

    ImGui::Begin("Editor");
    if (ImGui::SliderFloat3("camera position", cameraPosition, -10.f, 10.f)){
      camera.setPosition(glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]));
    }
    if (ImGui::SliderFloat("camera rotation", cameraRotation, 0, 360.f)){
      camera.setRotation(glm::vec3(cameraRotation[0], cameraRotation[1], cameraRotation[2]));
    }
    if (ImGui::SliderFloat("camera FOV", &camera_fov, 1.f, 120.f)){
      camera.setFieldOfView(camera_fov);
    }
    if (ImGui::SliderFloat("camera near clip plane", &camera_near_plane, 0.1f, 10.f)){
      camera.setNearClipPlane(camera_near_plane);
    }
    if (ImGui::SliderFloat("camera far clip plane", &camera_far_plane, 1.f, 100.f)){
      camera.setFarClipPlane(camera_far_plane);
    }
    if (ImGui::Checkbox("Perspective camera", &perspectiveCamera)){
      camera.setProjectionMode(perspectiveCamera ? Engine::Camera::ProjectionMode::Perspective : Engine::Camera::ProjectionMode::Orthographic);
    }
    ImGui::End();

    ImGui::Begin("Light");
    if (ImGui::Checkbox("Disco mode", &is_disco)) {
    }
    if (ImGui::SliderFloat3("light source position", light_source_pos, -10.f, 10.f)) {
    }
    if(!is_disco)
      if (ImGui::ColorEdit3("light color", light_source_color)) {
      }
    if (ImGui::SliderFloat("brightness", &ls_brightness, 1.f, 50.f)) {
    }
    if (ImGui::SliderFloat("ambient_factor", &ambient_factor, 0.f, 3.f)) {
    }
    if (ImGui::SliderFloat("diffuse_factor", &diffuse_factor, 0.f, 3.f)) {
    }
    if (ImGui::SliderFloat("specular_factor", &specular_factor, 0.f, 3.f)) {
    }
    if (ImGui::SliderFloat("shininess", &shininess, 0.8f, 10.f)) {
    }
    ImGui::End();
//    bool open = true;
//    ImPlot::ShowDemoWindow(&open);
  }
};