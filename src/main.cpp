#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include "render/Renderer.h"

int main() {
    try {
        //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
        Renderer renderer;
        renderer.Render();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}