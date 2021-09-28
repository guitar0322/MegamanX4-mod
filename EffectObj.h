#pragma once
#include "GameObject.h"
class EffectObj :
    public GameObject
{
public:
    static enum MODE
    {
        START,
        IDLE,
        END
    };
public:
    EffectObj() {};
    ~EffectObj() {};
    Renderer* renderer;
    Animator* animator;
    Effect* effect;
    virtual void Init();
    virtual void Init(float duration);
    virtual void Update();
    virtual void Render();
    void AddClip(const char* clipFileName, int clipWidth, int clipHeight, int clipFrameNum, float clipFrameTerm, MODE mode, bool dir);
};

