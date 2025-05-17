#pragma once
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum ECamera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensivity;
	float Zoom;

	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(ECamera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
private:
	void updateCameraVectors();
};