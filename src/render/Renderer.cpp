#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include <GLFW/glfw3.h>
#include "implot.h"
#include "../plot/TemperaturePlot.h"
#include "../data/api/WundergroundDataProvider.h"
#include "../plot/HumidityPlot.h"
#include "../config/Config.h"
#include "../config/ConfigFileManager.h"

Renderer::Renderer() {
    Renderer::Init();
}

void Renderer::Init() {
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "Weather widget", nullptr, nullptr);

    RECT screen;
    auto desktop = GetDesktopWindow();
    GetWindowRect(desktop, &screen);

    glfwSetWindowPos(window, screen.right - windowWidth, ((screen.bottom - windowHeight) / 2));

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

    fonts.insert({"regular", io.Fonts->AddFontFromFileTTF(FONTS"Roboto-Regular.ttf", 15)});
    fonts.insert({"light", io.Fonts->AddFontFromFileTTF(FONTS"Roboto-Light.ttf", 50)});
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
    Config config = ConfigFileManager::LoadConfigData();
    std::string apiKey{config.apiKey};
    std::string pwsId{config.pwsId};

    WundergroundDataProvider wundergroundDataProvider = WundergroundDataProvider(apiKey, pwsId);
    wundergroundDataProvider.CreateRefreshThread();

    std::string temperaturePlotTitle{"temperature"};
    std::string temperaturePlotUnit{" °C"};

    std::string humidityPlotTitle{"humidity"};
    std::string humidityPlotUnit{" %"};

    TemperaturePlot temperaturePlot = TemperaturePlot(temperaturePlotTitle, temperaturePlotUnit,
                                                      wundergroundDataProvider);
    HumidityPlot humidityPlot = HumidityPlot(humidityPlotTitle, humidityPlotUnit, wundergroundDataProvider);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{0, 0, 0, 0.0f});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("widget", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

        ImGui::SetWindowSize(ImVec2{static_cast<float>(windowWidth), static_cast<float>(plotHeight * 2)});
        ImGui::SetWindowPos(ImVec2{0, 0});

        temperaturePlot.CreatePlot();
        humidityPlot.CreatePlot();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{0, 0, 0, 1.f});
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{10.f, 10.f});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{5, 5});

        ImGui::Begin("Settings", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing);
        ImGui::SetWindowSize(ImVec2{static_cast<float>(windowWidth), 130});
        ImGui::SetWindowPos(ImVec2{0, static_cast<float>(plotHeight * 2)});

        ImGui::PushItemWidth(static_cast<float>(windowWidth) - buttonPadding);
        ImGui::InputTextWithHint("##", "Wunderground API key", &apiKey, ImGuiInputTextFlags_CallbackCharFilter);
        ImGui::InputTextWithHint("###", "PWS ID", &pwsId, ImGuiInputTextFlags_CallbackCharFilter);

        if (ImGui::Button("Save", ImVec2{static_cast<float>(windowWidth - buttonPadding), 30})) {
            config.apiKey = apiKey;
            config.pwsId = pwsId;
            ConfigFileManager::SaveConfigData(config);
            if (!wundergroundDataProvider.RefreshData(true)) {
                ImGui::OpenPopup("Error");
            }
        }

        if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            ImGui::SetWindowSize(ImVec2{static_cast<float>(windowWidth), 90});
            ImGui::SetWindowPos(ImVec2{0, 0});
            ImGui::Text("Check your API key and PWS ID");
            if (ImGui::Button("Ok", ImVec2{static_cast<float>(windowWidth - buttonPadding), 30})) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(3);
        ImGui::End();

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
