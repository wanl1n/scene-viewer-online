#include "FPSCounter.h"
#include "imgui.h"

FPSCounter::FPSCounter() : fps(0), updateTime(0.f)
{
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::update(double deltaTime)
{
    this->updateFPS(deltaTime);
}

void FPSCounter::draw()
{
    ImGui::SetNextWindowPos(ImVec2(1280 - 150, 680), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("FPS Counter", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::SetWindowFontScale(2);

    ImGui::Text("FPS: %d", static_cast<int>(this->fps));

    ImGui::End();
}

void FPSCounter::updateFPS(double deltaTime)
{
    this->updateTime += deltaTime;  

    if (this->updateTime >= 1.0) 
    {
        this->fps = frameCount / this->updateTime; 
        this->updateTime = 0.0; 
        this->frameCount = 0;   
    }

    this->frameCount++; 
}
