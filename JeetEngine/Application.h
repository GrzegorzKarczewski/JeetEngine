#pragma once
#include <vector>
#include <iostream>
class Window;
class ImGuiLayer;
class Mesh;
class Shader;
class Camera;
class PlayerInput;
class Model;

class Application {
public:
    Application();
    ~Application();
    void Run();
    void Shutdown();

private:
    void Init();

    std::unique_ptr<Window>        m_Window;
    std::unique_ptr<ImGuiLayer>    m_ImGuiLayer;
    std::unique_ptr<Camera>        m_Camera;
    std::unique_ptr<Model>        m_Model;
    std::unique_ptr<Mesh>          m_Mesh;
    std::unique_ptr<Shader>        m_Shaders;
    std::unique_ptr<PlayerInput>   m_PlayerInput;
};
