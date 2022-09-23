cmake_minimum_required(VERSION 3.23)
project(weather_widget)

set(CMAKE_CXX_STANDARD 20)

add_executable(weather_widget src/main.cpp src/render/Renderer.cpp src/render/Renderer.h src/interface/IWeatherPlot.h)
find_package(imgui REQUIRED)

find_package(GLEW REQUIRED)
target_link_libraries(weather_widget PRIVATE GLEW::GLEW)

find_package(implot CONFIG REQUIRED)
target_link_libraries(weather_widget PRIVATE implot::implot)

target_link_libraries(weather_widget PRIVATE imgui::imgui)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()