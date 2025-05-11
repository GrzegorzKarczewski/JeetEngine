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

    m_Mesh = new Mesh();
    m_Shaders = new Shader();
    glEnable(GL_DEPTH_TEST);
}

void Application::Run() {
    while (!m_Window->ShouldClose()) {
        m_Window->PollEvents();
        m_Window->ProcessInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_ImGuiLayer->Begin();
        m_Mesh->Draw();
        m_Shaders->ApplyShaderProgram();
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
