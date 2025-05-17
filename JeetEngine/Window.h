#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Camera;

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    GLFWwindow* GetGLFWwindow() const;
    inline int GetScreenWidth() { return m_SCR_WIDTH; }
    inline int GetScreenHeight() { return m_SCR_HEIGHT; }

private:
    GLFWwindow* m_Window = nullptr;
    Camera* m_Camera = nullptr;
    int m_SCR_WIDTH;
    int m_SCR_HEIGHT;
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
