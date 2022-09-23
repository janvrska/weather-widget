#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include "implot.h"

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

        std::vector<float> plotData{23, 24, 15, 10, 15, 10, 30, 35, 12.5, 12, 40, 85, 24, 23, 26};
        ImPlotFlags plotFlags =
                ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoInputs | ImPlotFlags_AntiAliased;

        if (ImPlot::BeginPlot("temperature",ImVec2{600, 400},plotFlags)) {
            double min = *min_element(plotData.begin(), plotData.end());
            double max = *max_element(plotData.begin(), plotData.end());

            ImPlot::SetupAxesLimits(0, std::size(plotData), min, max);
            ImPlot::SetupAxes(
                    nullptr,
                    nullptr,
                    ImPlotAxisFlags_NoDecorations | ImPlotAxisFlags_AutoFit,
                    ImPlotAxisFlags_NoDecorations
            );

            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.7f);
            ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2{0, 0});
            ImPlot::PushStyleColor(ImPlotCol_PlotBg, ImVec4{0, 0, 0, 0.7f});

            ImPlot::PlotShaded("temperature", plotData.data(), plotData.size());

            ImPlot::PopStyleVar(2);
            ImPlot::PopStyleColor(1);

            ImPlot::PlotLine("temperature", plotData.data(), plotData.size());

            ImGui::PushFont(fonts["light"]);
            ImPlot::PlotText("25 °C", (plotData.size() / 2.0) - 0.5, ((max - min) / 2) + min);
            ImGui::PopFont();

            ImPlot::EndPlot();
        }

        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(2);

        ImGui::End();
        ImGui::Render();

        int displayW, displayH;

        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w,
                     clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        //glfwWaitEventsTimeout(60);
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

    ImGuiIO &io = ImGui::GetIO();

    fonts.insert({"regular", io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Regular.ttf", 15)});
    fonts.insert({"light", io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Light.ttf", 50)});
}