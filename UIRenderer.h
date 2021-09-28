#pragma once
#include "GameObject.h"
class UIRenderer :
    public Component
{
private:
    HBITMAP hBit, oBit;
    HDC memDC, alphaMemDC;
    BLENDFUNCTION blendFunction;
    int width;
    int height;
public:
    UIRenderer();
    ~UIRenderer();
    int alpha;
    virtual void Init();
    virtual void Init(const char* filename, int width, int height);
    virtual void Update();
    virtual void Render();
    void Resize(int width, int height);
    void SetAlpha(int alpha);
    void FillColor(COLORREF color);
};

