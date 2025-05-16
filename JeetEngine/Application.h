#pragma once
#include <vector>
#include <iostream>
class Window;
class ImGuiLayer;
class Mesh;
class Shader;
class Texture;

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
    std::vector<std::unique_ptr<Texture>> m_Textures;
};
