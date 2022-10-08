#ifndef WEATHER_WIDGET_TEMPERATUREPLOT_H
#define WEATHER_WIDGET_TEMPERATUREPLOT_H

#include <string>
#include "../abstract/AWeatherPlot.h"

class TemperaturePlot : public AWeatherPlot {
public:
    TemperaturePlot(
            const std::string& plotTitle,
            const std::string& plotUnit,
            const ADataProvider& plotDataProvider
    ) : AWeatherPlot{plotTitle, plotUnit, plotDataProvider} {};

    void CreatePlot() const override;
};

#endif //WEATHER_WIDGET_TEMPERATUREPLOT_H
