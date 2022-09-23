#ifndef WEATHER_WIDGET_RENDERER_H
#define WEATHER_WIDGET_RENDERER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <memory>

class Renderer {
private:
    void Init();

    GLFWwindow *window{};
    ImVec4 clearColor{0, 0, 0, 0};
    bool open{true};
    std::map<std::string, ImFont *> fonts;
public:
    Renderer();

    ~Renderer();

    void Render();
};


#endif //WEATHER_WIDGET_RENDERER_H
