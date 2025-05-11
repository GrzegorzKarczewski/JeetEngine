#pragma once
class Window;
class ImGuiLayer;
class Mesh;
class Shader;

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
    Mesh* m_Mesh;
    Shader* m_Shaders;
};
