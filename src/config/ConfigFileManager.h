#ifndef WEATHER_WIDGET_CONFIGFILEMANAGER_H
#define WEATHER_WIDGET_CONFIGFILEMANAGER_H

#include <string>
#include "Config.h"

class ConfigFileManager {
public:
    static void SaveConfigData(Config& config);
    static Config LoadConfigData();
};

#endif //WEATHER_WIDGET_CONFIGFILEMANAGER_H
