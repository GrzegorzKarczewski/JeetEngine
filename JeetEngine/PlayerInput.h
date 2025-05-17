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
};