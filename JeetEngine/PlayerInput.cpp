#include "PlayerInput.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Window.h"
#include "Camera.h"
#include <iostream> // for debug only


PlayerInput::PlayerInput(GLFWwindow* window, Camera* camera)
    : m_Window(window), m_Camera(camera)
{
}

PlayerInput::~PlayerInput()
{
}

void PlayerInput::processInput(float deltaTime)
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    static bool fullscreenTogglePressed = false;
    if (glfwGetKey(m_Window, GLFW_KEY_F11) == GLFW_PRESS && !fullscreenTogglePressed) {
        fullscreenTogglePressed = true;
        static bool fullscreen = false;
        fullscreen = !fullscreen;

        GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_F11) == GLFW_RELEASE)
        fullscreenTogglePressed = false;

    // Camera/Player Movement
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_Camera->ProcessKeyboard(FORWARD, deltaTime);
        std::cout << "Pressed W" << std::endl;

    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(RIGHT, deltaTime);
}
