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
    void ProcessInput();
    GLFWwindow* GetGLFWwindow() const;
    inline int GetScreenWidth() { return m_SCR_WIDTH; }
    inline int GetScreenHeight() { return m_SCR_HEIGHT; }

private:
    GLFWwindow* m_Window;
    Camera* m_Camera;
    int m_SCR_WIDTH;
    int m_SCR_HEIGHT;
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
