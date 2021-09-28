#pragma once
#include "GameObject.h"
class Effect :
    public Component
{
public:
    Effect() {};
    ~Effect() {};
    Animator* animator;
    bool isEnd;
    float activeTime;
    float unActiveTime;
    virtual void Init();
    virtual void Init(float unActiveTime);
    virtual void Update();
    virtual void Render();
    void Emission(bool dir);
    void End(bool dir);
};

