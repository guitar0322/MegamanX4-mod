#pragma once
#include "GameObject.h"
class SoldierState;

class Soldier :
    public Component
{
private:
    SoldierState* _state;
    AnimationClip* _idleRight;
    AnimationClip* _idleLeft;
    AnimationClip* _attackRight;
    AnimationClip* _attackLeft;
    AnimationClip* _throwRight;
    AnimationClip* _throwLeft;
public:
    bool isDead;
    bool dir;
    Animator* animator;
    GameObject* rockman;
    
    virtual void Init(GameObject* rockman, bool dir);
    virtual void Update();

    void ChangeClip(string clipName, bool isInitFrame);
    void ClipInit();
    void OnTriggerEnter(GameObject* gameObject);
};

