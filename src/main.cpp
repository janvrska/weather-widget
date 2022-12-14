#include <iostream>
#include <Windows.h>
#include "render/Renderer.h"

int main() {
    try {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        FreeConsole();

        Renderer renderer;
        renderer.Render();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}