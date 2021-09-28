#pragma once
#include "GameObject.h"
class Overlap :
    public Component
{
private:
    HDC _overlapDC;
    HBITMAP _bitmap;
    HBRUSH _overlapBrush;
    COLORREF _overlapColor;
    COLORREF _transColor;
    Renderer* _renderer;
    BLENDFUNCTION _blendFunc;
    int _alpha;
    int _preWidth, _preHeight;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void SetColor(COLORREF color) { _overlapColor = color; }
    void SetAlpha(int alpha) { _alpha = alpha; _blendFunc.SourceConstantAlpha = alpha; }
};

