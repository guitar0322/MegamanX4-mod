#pragma once
#include "GameObject.h"
class ItemCarrier :
    public Component
{
private:
    AnimationClip _right;
    AnimationClip _left;
    Animator* _animator;
    bool _dir;
    float _speed;
    float _stopTime;
    int _disablePos;
public:
    GameObject* healPack;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnEnable();
    void SpawnHealpack();
};

