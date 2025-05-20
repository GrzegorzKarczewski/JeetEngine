#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "imgui.h"
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
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/type_ptr.hpp" 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Log.h"
#include <ImGuizmo.h>

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float lastFrame = 0.0f;
float deltaTime = 0.0f;
Application::Application() {
	Init();
}

Application::~Application() {
	Shutdown();
}

void Application::Init() {

	JeetLogger::Get().Initialize("JeetEngine.log");

	m_Window = std::make_unique<Window>(SCR_WIDTH,SCR_HEIGHT, "JeetEngine");
	JeetLogger::Get().Info("Screen width and height:%dx%d",SCR_WIDTH, SCR_HEIGHT);

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
		JeetLogger::Get().Error("Couldnt initialize Camera");

	m_Shaders = std::make_unique <Shader>("Shaders/4.5.texture.vs", "Shaders/4.5.texture.fs");
	if (m_Shaders) {
		JeetLogger::Get().Info("Shaders succesfully loaded!");
	}
	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);

	try {
		m_Models.push_back(std::make_unique<Model>("Resources/Models/backpack/backpack.obj",false, true));
		JeetLogger::Get().Info("Loaded model: backpack.obj");
	}
	catch (const std::exception& e) {
		JeetLogger::Get().Error("Failed to load backpack.obj: %s", e.what());
	}

	try {
		m_Models.push_back(std::make_unique<Model>("Resources/Models/girl/girl.obj"));
		JeetLogger::Get().Info("Loaded model: girl.obj");
	}
	catch (const std::exception& e) {
		JeetLogger::Get().Error("Failed to load girl.obj: %s", e.what());
	}
}

void Application::Run() {
	if (!m_Window || !m_ImGuiLayer || !m_Camera || !m_Shaders || m_Models.empty()) {
		JeetLogger::Get().Error("One or more core components are not initialized. Aborting run loop.");
		return;
	}
	while (!m_Window->ShouldClose()) {
		// --- time step ---
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Window->PollEvents();
		m_PlayerInput->processInput(deltaTime);
		m_ImGuiLayer->Begin();
		// ----------------------------------IMGUIZMO -----------------------------------//
		ImGuizmo::BeginFrame();
		// Optional: Define the area of the screen for the gizmo (usually the full window)
		ImGuizmo::SetRect(0, 0, (float)SCR_WIDTH, (float)SCR_HEIGHT);
		// Set view and projection
		ImGuizmo::SetOrthographic(false); // Use perspective
		ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList()); 
		// Operation mode: TRANSLATE / ROTATE / SCALE
		static ImGuizmo::OPERATION gizmoOperation = ImGuizmo::TRANSLATE;
		static ImGuizmo::MODE gizmoMode = ImGuizmo::WORLD;

	
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
	
		// Draw first model at -3 units on X axis
		glm::mat4 model1 = glm::mat4(1.0f);
		model1 = glm::translate(model1, glm::vec3(-3.0f, 0.0f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(1.0f));
		m_Shaders->setMat4("model", model1);
		m_Models[0]->Draw(*m_Shaders);

		// Draw second model at origin (can be manipulated with ImGuizmo)
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(1.0f));
		m_Shaders->setMat4("model", model2);
		m_Models[1]->Draw(*m_Shaders);

		// Manipulate second model interactively
		ImGuizmo::Manipulate(glm::value_ptr(view),
			glm::value_ptr(projection),
			gizmoOperation,
			gizmoMode,
			glm::value_ptr(model2));


		/*for (int i = 0; i < m_Models.size(); i++) {
			m_Models[i]->Draw(*m_Shaders);
		}*/
				
		m_ImGuiLayer->Render();
		m_ImGuiLayer->End();

		m_Window->SwapBuffers();
	}
}

void Application::Shutdown() {
	m_ImGuiLayer->Shutdown();
	JeetLogger::Get().Shutdown();

}
