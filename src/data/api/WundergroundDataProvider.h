#ifndef WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H
#define WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H

#include <string>
#include <vector>
#include <cpr/response.h>
#include "../../abstract/AApiDataProvider.h"
#include "../WundergroundDataSchema.h"

class WundergroundDataProvider : public AApiDataProvider {
private:
    std::string& apiKey;
    std::string& pwsId;
    std::vector<float> temperatureData;
    std::vector<float> humidityData;
    std::thread refreshThread;
protected:
    cpr::Response Request() const override;
    void ProcessResponseData(std::string responseData) override;
public:
    const std::vector<float>& GetData(const std::string& type) const override;
    void CreateRefreshThread() override;
    bool RefreshData(bool oneTimeRefresh) override;
    ~WundergroundDataProvider() override = default;

    WundergroundDataProvider(std::string& key, std::string& pws) : apiKey(key), pwsId(pws) {};
};

#endif //WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H
