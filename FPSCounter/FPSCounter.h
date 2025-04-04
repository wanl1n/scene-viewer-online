#pragma once
#include "imgui.h"

class FPSCounter
{
public:
    FPSCounter();
    ~FPSCounter();

    void update(double deltaTime);
    void draw();

private:
    void updateFPS(double elapsedTime);

    float fps;
    double updateTime;
    int frameCount = 0;

    float timer = 0;
};
