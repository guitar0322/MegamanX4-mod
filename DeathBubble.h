#pragma once
#include "GameObject.h"
class DeathBubble :
    public Component
{
private:
    typedef struct tagBubbleInfo {
        float x, y;
        float angle;
        float frameTime;
        int curFrame;
        bool isActive;
    }BUBBLEINFO;
private:
    float _emissionTerm;
    float _speed;
    BUBBLEINFO _bubble[96];
    AnimationClip _bubbleClip;
public:
    UIRenderer* fadeOut;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    void Emission();
};

