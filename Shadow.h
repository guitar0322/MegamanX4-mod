#pragma once
#include "GameObject.h"
class Shadow :
    public Component
{
private:
    bool _active;
    float _activeTime;
    pair<int, int> _nextPos;
    COLORREF _shadowColor;
public:
    Renderer* renderer;
    Renderer* rockmanRenderer;
    virtual void Init(Renderer* rockmanRenderer);
    virtual void Update();
    virtual void Render();
    void CopyRockman();

    bool GetActive() { return _active; }
    void SetNextPos(pair<int, int> nextPos) { _nextPos = nextPos; }
    void SetColor(COLORREF shadowColor) { _shadowColor = shadowColor; }
    COLORREF GetColor() { return _shadowColor; }
};

