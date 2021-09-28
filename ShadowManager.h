#pragma once
#include "GameObject.h"
class ShadowManager :
    public Component
{
private:
    RockMan* _rockman;
    float _onShadowTime;
    float _offShadowTime;
    bool _isOffShadow;
    bool _isOnShadow;
public:
    Shadow* shadow[3];
    virtual void Init(RockMan* rockman);
    virtual void Update();
    virtual void Render();
    void ActiveShadow();
    void UnActiveShadow();
    void OffShadow();
    void OnShadow();
    void SetShadowPos();
};

