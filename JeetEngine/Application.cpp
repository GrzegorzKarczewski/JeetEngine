#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "Mesh.h" // Adjust path if needed
#include "Shaders.h"
#include "Texture.h"
#include <vector>
#include <iostream>
#include <filesystem>

Application::Application() {
	Init();
}

Application::~Application() {
	Shutdown();
}

void Application::Init() {
	std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

	m_Window = new Window(800, 600, "JeetEngine");
	m_ImGuiLayer = new ImGuiLayer(m_Window->GetGLFWwindow());
	m_ImGuiLayer->Init();
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = { 0, 1, 3, // first triangle
							   1, 2, 3 // second triangle
	};

	m_Mesh = new Mesh(vertices, sizeof(vertices), indices ,sizeof(indices) /sizeof(unsigned int));
	m_Shaders = new Shader("Shaders/4.5.texture.vs", "Shaders/4.5.texture.fs");
	m_Textures.push_back(std::make_unique<Texture>("Resources/Textures/awesomeface.png"));
	m_Textures.push_back(std::make_unique<Texture>("Resources/Textures/container.jpg"));


	glEnable(GL_DEPTH_TEST);
}

void Application::Run() {
	while (!m_Window->ShouldClose()) {
		m_Window->PollEvents();
		m_Window->ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ImGuiLayer->Begin();
		m_Shaders->use();
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
	delete m_Mesh;
	delete m_Shaders;
	m_ImGuiLayer->Shutdown();
	delete m_ImGuiLayer;
	delete m_Window;
}
