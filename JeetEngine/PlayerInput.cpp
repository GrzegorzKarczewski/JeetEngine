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
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	double x, y;
	glfwGetCursorPos(m_Window, &x, &y);
	m_LastX = static_cast<float>(x);
	m_LastY = static_cast<float>(y);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetScrollCallback(m_Window, ScrollCallback);
}

PlayerInput::~PlayerInput()
{
}

void PlayerInput::processInput(float dt)
{
    /* ---------- ESC -> release cursor ---------- */
    static bool escHeld = false;
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escHeld) {
        escHeld = true;
        glfwSetInputMode(m_Window, GLFW_CURSOR,
            m_CursorFree ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        m_CursorFree = !m_CursorFree;
        m_FirstMouse = true;                 // avoid jump on re-capture
    }
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) escHeld = false;

    /* ---------- click -> re-capture when free ---------- */
    if (m_CursorFree &&
        glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_CursorFree = false;
        m_FirstMouse = true;
    }

    /* ---------- keyboard movement only when captured ---------- */
    if (!m_CursorFree) {
        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) m_Camera->ProcessKeyboard(FORWARD, dt);
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) m_Camera->ProcessKeyboard(BACKWARD, dt);
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) m_Camera->ProcessKeyboard(LEFT, dt);
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) m_Camera->ProcessKeyboard(RIGHT, dt);

        /* mouse look */
        double xposD, yposD;
        glfwGetCursorPos(m_Window, &xposD, &yposD);
        float xpos = (float)xposD, ypos = (float)yposD;
        if (m_FirstMouse) { m_LastX = xpos; m_LastY = ypos; m_FirstMouse = false; }
        float xoff = (xpos - m_LastX) * m_Sensitivity;
        float yoff = (m_LastY - ypos) * m_Sensitivity;
        m_LastX = xpos; m_LastY = ypos;
        m_Camera->ProcessMouseMovement(xoff, yoff);
    }
}

/* ---------- wheel ---------- */
void PlayerInput::ScrollCallback(GLFWwindow* win, double /*x*/, double y)
{
	static_cast<PlayerInput*>(glfwGetWindowUserPointer(win))->onScroll(static_cast<float>(y));
}

void PlayerInput::onScroll(float yoffset)
{
	m_Camera->ProcessMouseScroll(yoffset);
}

