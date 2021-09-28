#pragma once
#include "GameObject.h"
class Warning :
    public Component
{
private:
    ImageObject _warning[30];
    float _renderTerm;
    int _alpha;
    int _deltaAlpha;
    int _idx;
    int _num;
public:
    GameObject* colonel;
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

