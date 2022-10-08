#ifndef WEATHER_WIDGET_RENDERER_H
#define WEATHER_WIDGET_RENDERER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <memory>
#include <vector>

class Renderer {
private:
    void Init();
    GLFWwindow* window = nullptr;
    const ImVec4 clearColor{0, 0, 0, 0};
public:
    Renderer();
    ~Renderer();
    void Render();
    static inline std::map<std::string, ImFont*> fonts;
    static const int plotHeight{100};
    static const int windowHeight{330};
    static const int windowWidth{200};
};

#endif //WEATHER_WIDGET_RENDERER_H
