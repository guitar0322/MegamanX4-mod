#pragma once
#include "GameObject.h"
class ChargeOverlap :
    public Component
{
private:
    COLORREF _overlapColor;
    COLORREF _transColor;
    Renderer* _renderer;
    Renderer* _targetRenderer;
    HBRUSH blueBrush, oBrush;
    BLENDFUNCTION blendFunc;
    float _switchTotalTime;
    float _switchTime;
    bool _switchFlag;
public:
    ChargeOverlap() {};
    ~ChargeOverlap() {};
    virtual void Init(Renderer* targetRenderer, COLORREF color);
    virtual void Update();
    virtual void Render();
    void FillTransparent();

    void SetSwitchTime(float switchTime) { _switchTime = switchTime; }
};

