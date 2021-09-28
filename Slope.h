#pragma once
#include "GameObject.h"
class Slope :
    public Component
{
public:
    int startX, endX;
    float a, b;
    float x1, y1, x2, y2;
    virtual void Init(int startX, int endX, float x1, float y1, float x2, float y2);
    virtual void Update();
    virtual void Render();
};

