#include "WundergroundDataProvider.h"
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <format>
#include <iostream>

using nlohmann::json;

const std::vector<float>& WundergroundDataProvider::GetData(const std::string& type) const {
    if (strcmp(type.c_str(), "temperature") == 0) {
        return temperatureData;
    }

    if (strcmp(type.c_str(), "humidity") == 0) {
        return humidityData;
    }

    return temperatureData;
}

cpr::Response WundergroundDataProvider::Request() const {
    const std::string url = std::format(
            "https://api.weather.com/v2/pws/observations/all/1day?stationId={}&format=json&units=m&numericPrecision=decimal&apiKey={}",
            pwsId, apiKey);
    return cpr::Get(cpr::Url{url});
}

void WundergroundDataProvider::ProcessResponseData(std::string responseData) {

    wundergroundData::apiObject apiData;
    try {
        apiData = json::parse(responseData);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    std::vector<float> tempDataTemperature;
    std::vector<float> tempDataHumidity;

    for (const auto& observation: apiData.observations) {
        tempDataTemperature.push_back(observation.metric.tempAvg);
        tempDataHumidity.push_back(observation.humidityAvg);
    }

    temperatureData = tempDataTemperature;
    humidityData = tempDataHumidity;
}

bool WundergroundDataProvider::RefreshData(bool oneTimeRefresh) {
    while (true) {

        if ((apiKey.length() == 0 && pwsId.length() == 0) && !oneTimeRefresh) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 300));
            continue;
        }

        cpr::Response response = Request();

        if (response.status_code == 200) {
            ProcessResponseData(response.text);
            if (oneTimeRefresh)
                return true;
        } else {
            if (oneTimeRefresh)
                return false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 300));
    }
}

void WundergroundDataProvider::CreateRefreshThread() {
    if (!refreshThread.joinable()) {
        refreshThread = std::thread([this] { this->RefreshData(false); });
    }
}
