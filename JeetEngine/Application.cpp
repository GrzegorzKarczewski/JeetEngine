#include "Application.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "Mesh.h" // Adjust path if needed
#include "Shaders.h"

Application::Application() {
	Init();
}

Application::~Application() {
	Shutdown();
}

void Application::Init() {
	m_Window = new Window(800, 600, "JeetEngine");
	m_ImGuiLayer = new ImGuiLayer(m_Window->GetGLFWwindow());
	m_ImGuiLayer->Init();
	float vertices[] = {
   0.5f,  0.5f, 0.0f,  // top right
 0.5f, -0.5f, 0.0f,  // bottom right
-0.5f, -0.5f, 0.0f,  // bottom left
-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = { 0, 1, 3, // first triangle
							   1, 2, 3 // second triangle
	};

	m_Mesh = new Mesh(vertices, sizeof(vertices), indices ,sizeof(indices) /sizeof(unsigned int));
	m_Shaders = new Shader("4.5.shader.vs", "4.5.shader.fs");

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
