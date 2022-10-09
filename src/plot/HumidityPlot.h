#ifndef WEATHER_WIDGET_HUMIDITYPLOT_H
#define WEATHER_WIDGET_HUMIDITYPLOT_H

#include <string>
#include "../abstract/AWeatherPlot.h"

class HumidityPlot : public AWeatherPlot {
public:
    HumidityPlot(
            const std::string& plotTitle,
            const std::string& plotUnit,
            const ADataProvider& plotDataProvider
    ) : AWeatherPlot{plotTitle, plotUnit, plotDataProvider} {}

    void CreatePlot() const override;
};

#endif //WEATHER_WIDGET_HUMIDITYPLOT_H
