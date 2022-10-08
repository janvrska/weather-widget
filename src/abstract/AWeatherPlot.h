#ifndef WEATHER_WIDGET_AWEATHERPLOT_H
#define WEATHER_WIDGET_AWEATHERPLOT_H

#include <string>
#include "ADataProvider.h"

class AWeatherPlot {
protected:
    const std::string& title;
    const std::string& unit;
    const ADataProvider& dataProvider;
public:
    AWeatherPlot(
            const std::string& plotTitle,
            const std::string& plotUnit,
            const ADataProvider& plotDataProvider
    ) : title(plotTitle), unit(plotUnit), dataProvider(plotDataProvider) {}

    virtual void CreatePlot() const = 0;
    virtual ~AWeatherPlot() = default;
};

#endif //WEATHER_WIDGET_AWEATHERPLOT_H
