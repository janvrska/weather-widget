#ifndef WEATHER_WIDGET_CONFIG_H
#define WEATHER_WIDGET_CONFIG_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Config {
    std::string apiKey;
    std::string pwsId;
};

namespace ns {
    void from_json(const json& j, Config& x);
    void to_json(json& j, const Config& x);

    inline void from_json(const json& j, Config& x) {
        x.apiKey = j.at("apiKey").get<std::string>();
        x.pwsId = j.at("pwsId").get<std::string>();
    }

    inline void to_json(json& j, const Config& x) {
        j = json::object();
        j["apiKey"] = x.apiKey;
        j["pwsId"] = x.pwsId;
    }
}

#endif //WEATHER_WIDGET_CONFIG_H
