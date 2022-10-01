#ifndef WEATHER_WIDGET_WUNDERGROUNDDATASCHEMA_H
#define WEATHER_WIDGET_WUNDERGROUNDDATASCHEMA_H

#include <nlohmann/json.hpp>

namespace wundergroundData {
    using nlohmann::json;
    inline json get_untyped(const json& j, const char* property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return {};
    }

    inline json get_untyped(const json& j, std::string property) {
        return get_untyped(j, property.data());
    }

    struct metric {
        float tempHigh;
        float tempLow;
        float tempAvg;
        float windspeedHigh;
        float windspeedLow;
        float windspeedAvg;
        float windgustHigh;
        float windgustLow;
        float windgustAvg;
        float dewptHigh;
        float dewptLow;
        float dewptAvg;
        float windchillHigh;
        float windchillLow;
        float windchillAvg;
        float heatindexHigh;
        float heatindexLow;
        float heatindexAvg;
        float pressureMax;
        float pressureMin;
        float pressureTrend;
        float precipRate;
        float precipTotal;
    };

    struct observation {
        std::string stationId;
        std::string tz;
        std::string obsTimeUtc;
        std::string obsTimeLocal;
        float epoch{};
        float lat{};
        float lon{};
        float solarRadiationHigh{};
        float uvHigh{};
        float winddirAvg{};
        float humidityHigh{};
        float humidityLow{};
        float humidityAvg{};
        float qcStatus{};
        metric metric{};
    };

    struct apiObject {
        std::vector<observation> observations;
    };

    inline void from_json(const json& j, wundergroundData::metric& x) {
        x.tempHigh = j.at("tempHigh").get<float>();
        x.tempLow = j.at("tempLow").get<float>();
        x.tempAvg = j.at("tempAvg").get<float>();
        x.windspeedHigh = j.at("windspeedHigh").get<float>();
        x.windspeedLow = j.at("windspeedLow").get<float>();
        x.windspeedAvg = j.at("windspeedAvg").get<float>();
        x.windgustHigh = j.at("windgustHigh").get<float>();
        x.windgustLow = j.at("windgustLow").get<float>();
        x.windgustAvg = j.at("windgustAvg").get<float>();
        x.dewptHigh = j.at("dewptHigh").get<float>();
        x.dewptLow = j.at("dewptLow").get<float>();
        x.dewptAvg = j.at("dewptAvg").get<float>();
        x.windchillHigh = j.at("windchillHigh").get<float>();
        x.windchillLow = j.at("windchillLow").get<float>();
        x.windchillAvg = j.at("windchillAvg").get<float>();
        x.heatindexHigh = j.at("heatindexHigh").get<float>();
        x.heatindexLow = j.at("heatindexLow").get<float>();
        x.heatindexAvg = j.at("heatindexAvg").get<float>();
        x.pressureMax = j.at("pressureMax").get<float>();
        x.pressureMin = j.at("pressureMin").get<float>();
        x.pressureTrend = j.at("pressureTrend").get<float>();
        x.precipRate = j.at("precipRate").get<float>();
        x.precipTotal = j.at("precipTotal").get<float>();
    }

    inline void from_json(const json& j, wundergroundData::observation& x) {
        x.stationId = j.at("stationID").get<std::string>();
        x.tz = j.at("tz").get<std::string>();
        x.obsTimeUtc = j.at("obsTimeUtc").get<std::string>();
        x.obsTimeLocal = j.at("obsTimeLocal").get<std::string>();
        x.epoch = j.at("epoch").get<float>();
        x.lat = j.at("lat").get<float>();
        x.lon = j.at("lon").get<float>();
        x.solarRadiationHigh = j.at("solarRadiationHigh").get<float>();
        x.uvHigh = j.at("uvHigh").get<float>();
        x.winddirAvg = j.at("winddirAvg").get<float>();
        x.humidityHigh = j.at("humidityHigh").get<float>();
        x.humidityLow = j.at("humidityLow").get<float>();
        x.humidityAvg = j.at("humidityAvg").get<float>();
        x.qcStatus = j.at("qcStatus").get<float>();
        x.metric = j.at("metric").get<wundergroundData::metric>();
    }

    inline void from_json(const json& j, wundergroundData::apiObject& x) {
        x.observations = j.at("observations").get<std::vector<wundergroundData::observation>>();
    }
}


#endif //WEATHER_WIDGET_WUNDERGROUNDDATASCHEMA_H
