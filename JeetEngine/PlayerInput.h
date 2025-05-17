#pragma once

struct GLFWwindow;
class Camera;
class PlayerInput {

public:
	PlayerInput(GLFWwindow* window, Camera* camera);
	~PlayerInput();
	void processInput(float deltaTime);
private:
	GLFWwindow* m_Window;
	Camera* m_Camera;
    // mouse
    bool  m_FirstMouse = true;
    bool  m_CursorFree = false;

    float m_LastX = 0.f;
    float m_LastY = 0.f;
    float m_Sensitivity = 0.1f;

    // wheel
    static void ScrollCallback(GLFWwindow* win, double /*x*/, double y);
    void        onScroll(float yoffset);
};