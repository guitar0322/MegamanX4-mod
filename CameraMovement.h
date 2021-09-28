#pragma once
#include "GameObject.h"
class CameraMovement :
    public Component
{
private:
    GameObject* _rockman;
    bool _isSinkhole;
    bool _isFloor;
    bool _isEscape;
    bool _isBoss;
    float _recoverySpeed;
public:
    virtual void Init(GameObject* rockman);
    virtual void Update();
    virtual void Render();
};

