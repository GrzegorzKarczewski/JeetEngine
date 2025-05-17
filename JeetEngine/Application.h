#pragma once
#include <vector>
#include <iostream>
class Window;
class ImGuiLayer;
class Mesh;
class Shader;
class Texture;
class Camera;
class PlayerInput;

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    void Init();
    void Shutdown();

    Window* m_Window;
    ImGuiLayer* m_ImGuiLayer;
    Camera* m_Camera;
    Mesh* m_Mesh;
    Shader* m_Shaders;
    PlayerInput* m_PlayerInput;
    std::vector<std::unique_ptr<Texture>> m_Textures;
};
