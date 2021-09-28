#pragma once
#include "GameObject.h"
class BackgroundControl :
    public Component
{
private:
    GameObject* _rockman;
    float _rockmanX;
    float _rockmanY;
public:
    ImageObject* background[16];
    ImageObject* holeBackground;
    virtual void Init(GameObject* rockman);
    virtual void Update();
    virtual void Render();
};

