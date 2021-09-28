#pragma once
#include "GameObject.h"
class HealPack :
    public Component
{
private:
    AnimationClip basic;
    AnimationClip intro;
    AnimationClip idle;
    Animator* _animator;
    float _speedY;
    float _gravity;
    bool _isGround;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void OnEnable();
};

