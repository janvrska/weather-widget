cmake_minimum_required(VERSION 3.23)
project(weather_widget)

set(CMAKE_CXX_STANDARD 20)

add_executable(weather_widget main.cpp)
find_package(imgui REQUIRED)

find_package(GLEW REQUIRED)
target_link_libraries(weather_widget PRIVATE GLEW::GLEW)

target_link_libraries(weather_widget PRIVATE imgui::imgui)
