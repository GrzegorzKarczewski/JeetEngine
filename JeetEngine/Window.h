#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    void ProcessInput();
    GLFWwindow* GetGLFWwindow() const;

private:
    GLFWwindow* m_Window;
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
