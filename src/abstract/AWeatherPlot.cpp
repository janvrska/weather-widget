#include <algorithm>
#include <sstream>
#include <iomanip>
#include "AWeatherPlot.h"
#include "implot.h"
#include "../render/Renderer.h"

void AWeatherPlot::CreatePlot() const {
    const std::vector<float> plotData = dataProvider.GetData(title);

    if (plotData.empty()) {
        return;
    }

    ImPlotFlags plotFlags =
            ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoInputs | ImPlotFlags_AntiAliased;

    if (ImPlot::BeginPlot(title.c_str(), ImVec2{Renderer::windowWidth, Renderer::plotHeight}, plotFlags)) {
        double min = *min_element(plotData.begin(), plotData.end());
        double max = *max_element(plotData.begin(), plotData.end());

        ImPlot::SetupAxesLimits(0, std::size(plotData), min, max, ImPlotCond_Always);
        ImPlot::SetupAxes(
                nullptr,
                nullptr,
                ImPlotAxisFlags_NoDecorations | ImPlotAxisFlags_AutoFit,
                ImPlotAxisFlags_NoDecorations
        );

        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.7f);
        ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2{0, 0});
        ImPlot::PushStyleColor(ImPlotCol_PlotBg, ImVec4{0, 0, 0, 0.7f});
        ImPlot::PushStyleColor(ImPlotCol_Fill, ImVec4{0.6, 0.8, 0.3, 0.7f});

        ImPlot::PlotShaded(title.c_str(), plotData.data(), static_cast<int>(plotData.size()));

        ImPlot::PopStyleVar(2);
        ImPlot::PopStyleColor(2);

        ImPlot::PlotLine(title.c_str(), plotData.data(), static_cast<int>(plotData.size()));
        ImGui::PushFont(Renderer::fonts["light"]);

        std::ostringstream oss;
        oss << std::setprecision(5) << std::noshowpoint << plotData.back();
        std::string plotValue = oss.str();

        std::string plotText{plotValue + unit};

        ImPlot::PlotText(plotText.c_str(), (plotData.size() / 2.0), ((max - min) / 2) + min);
        ImGui::PopFont();

        ImPlot::EndPlot();
    }
}