#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "Mesh.h" 
#include "Shaders.h"
#include "Camera.h"
#include "PlayerInput.h"
#include "Model.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


float lastFrame = 0.0f;
float deltaTime = 0.0f;

Application::Application() {
	Init();
}

Application::~Application() {
	Shutdown();
}

void Application::Init() {


	m_Window = std::make_unique<Window>(800, 600, "JeetEngine");
	m_ImGuiLayer = std::make_unique<ImGuiLayer>(m_Window->GetGLFWwindow());
	m_ImGuiLayer->Init();

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
	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);

	m_Models.push_back(std::make_unique<Model>("Resources/Models/backpack/backpack.obj"));
	m_Models.push_back(std::make_unique<Model>("Resources/Models/girl/girl.obj"));



}

void Application::Run() {
	while (!m_Window->ShouldClose()) {
		// --- time step ---
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Window->PollEvents();
		m_PlayerInput->processInput(deltaTime);
		m_ImGuiLayer->Begin();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Shaders->use();

		// Recompute view and projection each frame in case of camera movement
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom),
			(float)m_Window->GetScreenWidth() / (float)m_Window->GetScreenHeight(), 0.1f, 100.0f);
		m_Shaders->setMat4("view", view);
		m_Shaders->setMat4("projection", projection);
		m_Shaders->setVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
		m_Shaders->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shaders->setVec3("viewPos", m_Camera->Position);


		
		// render the model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		m_Shaders->setMat4("model", model);
		/*for (int i = 0; i < m_Models.size(); i++) {
			m_Models[i]->Draw(*m_Shaders);
		}
		*/
		m_Models[1]->Draw(*m_Shaders);
		
		m_ImGuiLayer->Render();
		m_ImGuiLayer->End();

		m_Window->SwapBuffers();
	}
}

void Application::Shutdown() {
	m_ImGuiLayer->Shutdown();
}
