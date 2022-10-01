#ifndef WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H
#define WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H

#include <string>
#include <vector>
#include <cpr/response.h>
#include "../../abstract/AApiDataProvider.h"
#include "../WundergroundDataSchema.h"

class WundergroundDataProvider : public AApiDataProvider {
private:
    const char* apiKey{""};
    const char* baseUrl{""};
    const char* pwsId{""};
    std::vector<float> temperatureData{};
protected:
    cpr::Response Request() const override;
    void ProcessResponseData(std::string responseData) override;
    void RefreshData() override;
public:
    const std::vector<float>& GetData(const std::string& type) const override;
    std::thread CreateRefreshThread() override;
    ~WundergroundDataProvider() override = default;
};


#endif //WEATHER_WIDGET_WUNDERGROUNDDATAPROVIDER_H
