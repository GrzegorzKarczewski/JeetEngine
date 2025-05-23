#pragma once

#include "ImGuiLayer.h"
#include <imgui.h>
#include <ImGuizmo.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

ImGuiLayer::ImGuiLayer(GLFWwindow* window) : m_Window(window) {}

void ImGuiLayer::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void ImGuiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::Render() {
    ImGui::Begin("Stats");
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Test Menu")) {
            // Menu items here
            ImGui::MenuItem("Change the model scale:", nullptr, false, true);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", 1.0f / io.DeltaTime);
    ImGui::End();
    
}

void ImGuiLayer::End() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
