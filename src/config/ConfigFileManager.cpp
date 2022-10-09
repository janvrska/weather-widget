#include "ConfigFileManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using nlohmann::json;

void ConfigFileManager::SaveConfigData(Config& config) {
    json j;

    ns::to_json(j, config);
    std::ofstream o("widget.json");
    o << j << std::endl;
    o.close();
}

Config ConfigFileManager::LoadConfigData() {
    Config config;

    try {
        std::ifstream i("widget.json");
        json j;
        i >> j;
        ns::from_json(j, config);
        i.close();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return config;
}
