#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "Mesh.h" 
#include "Shaders.h"
#include "Camera.h"
#include "PlayerInput.h"
#include "Texture.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


float lastFrame = 0.0f;
float deltaTime = 0.0f;

Application::Application() {
	Init();
}

Application::~Application() {
	Shutdown();
}

void Application::Init() {
	std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

	m_Window = std::make_unique<Window>(800, 600, "JeetEngine");
	m_ImGuiLayer = std::make_unique<ImGuiLayer>(m_Window->GetGLFWwindow());
	m_ImGuiLayer->Init();
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.3f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.3f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = { 0, 1, 3, // first triangle
							   1, 2, 3 // second triangle
	};

	m_Mesh = std::make_unique<Mesh>(vertices, sizeof(vertices), indices ,sizeof(indices) /sizeof(unsigned int));

	m_Camera = std::make_unique<Camera>(
		glm::vec3(0.0f, 0.0f, 3.0f),   // position
		glm::vec3(0.0f, 1.0f, 0.0f),   // world-up
		-90.0f,                        // yaw   (look toward −Z)
		0.0f);                         // pitch (level)

	if (m_Camera != nullptr) {
		m_PlayerInput = std::make_unique<PlayerInput>(m_Window->GetGLFWwindow(), m_Camera.get());
	}
	else
		std::cout << "Camera is nullptr" << std::endl;

	m_Shaders = std::make_unique <Shader>("Shaders/4.5.texture.vs", "Shaders/4.5.texture.fs");
	m_Textures.push_back(std::make_unique<Texture>("Resources/Textures/awesomeface.png"));
	m_Textures.push_back(std::make_unique<Texture>("Resources/Textures/container.jpg"));


	glEnable(GL_DEPTH_TEST);
}

void Application::Run() {
	while (!m_Window->ShouldClose()) {
		// --- time step ---
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Window->PollEvents();
		m_PlayerInput->processInput(deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Recompute view and projection each frame in case of camera movement
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom),
			(float)m_Window->GetScreenWidth() / (float)m_Window->GetScreenHeight(), 0.1f, 100.0f);

		m_ImGuiLayer->Begin();
		m_Shaders->use();
		m_Shaders->setMat4("model", model);
		m_Shaders->setMat4("view", view);
		m_Shaders->setMat4("projection", projection);

		if (m_Textures.size() >= 2) {
			m_Textures[0]->Bind(0); // texture unit 0
			m_Textures[1]->Bind(1); // texture unit 1

			m_Shaders->setInt("texture1", 0); 
			m_Shaders->setInt("texture2", 1);
		}
		
		m_Mesh->Draw();
		m_ImGuiLayer->Render();
		m_ImGuiLayer->End();

		m_Window->SwapBuffers();
	}
}

void Application::Shutdown() {
	m_ImGuiLayer->Shutdown();
}
