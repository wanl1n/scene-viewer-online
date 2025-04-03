#pragma once
#include <imgui.h>
#include "../stb_image.h"
#include "glad/glad.h"

class ImGuiUtils
{
public:
	static void LoadingBar(const char* label, float progress, const ImVec2& size = ImVec2(100, 10), const ImVec4& barColor = ImVec4(1.0f, 0.4f, 0.5f, 1.0f)) {
        /*ImGui::Text("%s", label);
        ImGui::SameLine();*/

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));  // Background color
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barColor);  // Progress bar color

        // Ensure progress is between 0 and 1
        progress = progress < 0.0f ? 0.0f : (progress > 1.0f ? 1.0f : progress);

        ImGui::ProgressBar(progress, size);

        ImGui::PopStyleColor(2);
    }

    // Load texture function
    static GLuint LoadTexture(const char* filename) {
        int width, height, channels;
        unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
        if (!data) return 0;

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        return textureID;
    }

    // Use the texture in ImGui
    static void Image(const char* filename, int width, int height) {
        GLuint img = LoadTexture(filename);
        ImGui::Image((ImTextureID)(intptr_t)img, ImVec2(width, height));
    }
};