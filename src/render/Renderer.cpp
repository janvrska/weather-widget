#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include "implot.h"
#include "../plot/TemperaturePlot.h"
#include "../data/api/WundergroundDataProvider.h"

Renderer::Renderer() {
    Renderer::Init();
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::Render() {
    WundergroundDataProvider wundergroundDataProvider = WundergroundDataProvider();
    std::thread refreshThread = wundergroundDataProvider.CreateRefreshThread();
    refreshThread.detach();

    std::string temperaturePlotTitle{"temperature"};
    std::string temperaturePlotUnit{" °C"};

    TemperaturePlot temperaturePlot = TemperaturePlot(temperaturePlotTitle,temperaturePlotUnit,wundergroundDataProvider);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{0, 0, 0, 0.0f});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("widget", &open, flags);
        ImGui::SetWindowSize(ImVec2{600, 400});
        ImGui::SetWindowPos(ImVec2{0, 0});

        temperaturePlot.CreatePlot();

        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(2);

        ImGui::End();
        ImGui::Render();

        int displayW, displayH;

        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(
                clearColor.x * clearColor.w,
                clearColor.y * clearColor.w,
                clearColor.z * clearColor.w,
                clearColor.w
        );
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(60);
    }
}

void Renderer::Init() {
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(800, 600, "Weather widget", nullptr, nullptr);
    //glfwSetWindowPos(window, 500, 500);

    if (window == nullptr)
        return;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();

    fonts.insert({"regular", io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Regular.ttf", 15)});
    fonts.insert({"light", io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Light.ttf", 50)});
}