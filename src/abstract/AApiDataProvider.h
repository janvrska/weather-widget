#ifndef WEATHER_WIDGET_AAPIDATAPROVIDER_H
#define WEATHER_WIDGET_AAPIDATAPROVIDER_H

#include <string>
#include "ADataProvider.h"
#include <vector>
#include <cpr/response.h>

class AApiDataProvider : public ADataProvider {
protected:
    virtual cpr::Response Request() const = 0;

    virtual void ProcessResponseData(std::string responseData) = 0;

    virtual void RefreshData() = 0;

public:
    virtual const std::vector<float>& GetData(const std::string& type) const = 0;
    virtual std::thread CreateRefreshThread() = 0;

    ~AApiDataProvider() = default;
};


#endif //WEATHER_WIDGET_AAPIDATAPROVIDER_H
