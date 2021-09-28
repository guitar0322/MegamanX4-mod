#pragma once
#include "GameObject.h"
class TrapBlastState;
class TrapBlast :
    public Component
{
private:
    TrapBlastState* _state;
    AnimationClip* _introRight;
    AnimationClip* _introLeft;
    AnimationClip* _idleRight;
    AnimationClip* _idleLeft;
    AnimationClip* _attackRight;
    AnimationClip* _attackLeft;
public:
    GameObject* rockman;
    Animator* animator;
    bool isDead;
    bool dir;
    virtual void Init(GameObject* rockman, bool dir);
    virtual void Update();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void OnTriggerEnter(GameObject* gameObject);
    void ClipInit();
    void ChangeClip(string clipName, bool isInitFrame);
};

