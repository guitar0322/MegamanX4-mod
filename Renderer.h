#pragma once
#include "GameObject.h"
#include "image.h"
class Renderer :
    public Component
{
private:
    BLENDFUNCTION blendFunc;
public:
    Renderer();
    ~Renderer();
    COLORREF transColor;
    HDC memDC, alphaMemDC;
    HBITMAP oBit, hBit;
    RECT rc;
    int alpha;
    int width;
    int height;
    virtual void Init(const char* filename, int width, int height);
    virtual void Init();
    virtual void Render();
    virtual void Update();
    virtual void OnEnable();
    void SetAlpha(int alpha) { this->alpha = alpha; blendFunc.SourceConstantAlpha = alpha;}
    void Resize(int objWidth, int objHeight);
    void SetTransColor(COLORREF transColor) { this->transColor = transColor; }
};

