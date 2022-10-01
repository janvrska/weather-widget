#include "WundergroundDataProvider.h"
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "../WundergroundDataSchema.h"

using nlohmann::json;

const std::vector<float>& WundergroundDataProvider::GetData(const std::string& type) const {
    /*if(strcmp(type.c_str(),"temperature") == 0) {
        return temperatureData;
    }*/

    return temperatureData;
}

cpr::Response WundergroundDataProvider::Request() const {
    return cpr::Get(cpr::Url{baseUrl});
}

void WundergroundDataProvider::ProcessResponseData(std::string responseData) {
    wundergroundData::apiObject apiData = json::parse(responseData);

    std::vector<float> tempData;
    for (const auto& observation: apiData.observations) {
        tempData.push_back(observation.metric.tempAvg);
    }

    temperatureData = tempData;
}

void WundergroundDataProvider::RefreshData() {
    while(true){
        cpr::Response response = Request();
        ProcessResponseData(response.text);
        std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    }
}

std::thread WundergroundDataProvider::CreateRefreshThread() {
    return std::thread([this] { this->RefreshData(); });
}
