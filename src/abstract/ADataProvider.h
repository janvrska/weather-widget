#ifndef WEATHER_WIDGET_ADATAPROVIDER_H
#define WEATHER_WIDGET_ADATAPROVIDER_H

#include <vector>
#include <string>

class ADataProvider {
public:
    virtual const std::vector<float>& GetData(const std::string& type) const = 0;

    virtual ~ADataProvider() = default;
};

#endif //WEATHER_WIDGET_ADATAPROVIDER_H
