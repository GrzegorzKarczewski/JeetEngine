
#pragma once
#include <GLFW/glfw3.h>

class ImGuiLayer {
public:
    ImGuiLayer(GLFWwindow* window);
    void Init();
    void Begin();
    void Render();
    void End();
    void Shutdown();

private:
    GLFWwindow* m_Window;
};
