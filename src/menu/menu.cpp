#include <menu/menu.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <engine/engine.hpp>

menu_t::menu_t() : width(400), height(300), title("Debug Menu") {}

void menu_t::initialize(engine_t* engine) {
    state = engine;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));

    ImGui_ImplGlfw_InitForOpenGL(engine->get_window()->get_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void menu_t::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
    
    ImGui::Begin(title.c_str(), &showing);

    ImGui::SliderFloat("Camera FOV", &state->get_camera()->field_of_view, 45.0f, 90.0f);

    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void menu_t::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}