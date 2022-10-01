cmake_minimum_required(VERSION 3.23)
project(weather_widget)

set(CMAKE_CXX_STANDARD 20)

add_executable(weather_widget src/main.cpp src/render/Renderer.cpp src/render/Renderer.h src/abstract/AWeatherPlot.cpp src/abstract/AWeatherPlot.h src/plot/TemperaturePlot.cpp src/plot/TemperaturePlot.h src/abstract/ADataProvider.cpp src/abstract/ADataProvider.h src/abstract/AApiDataProvider.cpp src/abstract/AApiDataProvider.h src/data/api/WundergroundDataProvider.cpp src/data/api/WundergroundDataProvider.h src/data/WundergroundDataSchema.h)
find_package(imgui REQUIRED)

find_package(GLEW REQUIRED)
target_link_libraries(weather_widget PRIVATE GLEW::GLEW)

find_package(implot CONFIG REQUIRED)
target_link_libraries(weather_widget PRIVATE implot::implot)

target_link_libraries(weather_widget PRIVATE imgui::imgui)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(weather_widget PRIVATE cpr::cpr)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(weather_widget PRIVATE nlohmann_json::nlohmann_json)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()