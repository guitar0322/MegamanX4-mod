#pragma once
#include "Scene.h"
class SecondScene :
    public Scene
{
public:
    SecondScene();
    ~SecondScene();
    ImageObject background;
    ImageObject start;
    ImageObject fadeOut;
    float twinkleTime;
    float fadeOutTime;
    bool isStart;
    int alpha;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

