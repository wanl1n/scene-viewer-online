#pragma once
#include <imgui.h>

class ImGuiUtils
{
public:
	static void LoadingBar(const char* label, float progress, const ImVec2& size = ImVec2(200, 20), const ImVec4& barColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f)) {
        ImGui::Text("%s", label);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));  // Background color
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barColor);  // Progress bar color

        // Ensure progress is between 0 and 1
        progress = progress < 0.0f ? 0.0f : (progress > 1.0f ? 1.0f : progress);

        ImGui::ProgressBar(progress, size);

        ImGui::PopStyleColor(2);
    }
};