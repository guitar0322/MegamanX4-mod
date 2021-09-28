#pragma once
#include "GameObject.h"
class State;
class RockMan :
    public Component
{
public:
    bool dir;
    bool isFall;
    bool isDash;
    bool isAttack;
    bool isMiddleChargeAttack;
    bool isFullChargeAttack;
    bool isDead;
    bool attackable;
    bool isBoss;
    bool autoMove;
    bool isBossIntro;
    bool isClear;
    float chargeTime;
    float middleChargeTime;
    float fullChargeTime;
    float attackTime;
    float speedX;
    float gravity;

    ObjectInfo* objectInfo;
    EffectObj* dashSmokeEffect;
    EffectObj* dashEffect;
    EffectObj* wallSparkEffect;
    EffectObj* wallSmokeEffect;
    EffectObj* basicAttackEffect;
    EffectObj* middleAttackEffect;
    EffectObj* fullAttackEffect;
    EffectObj* middleChargeEffect;
    EffectObj* fullChargeEffect;
    UIBase* hpBar;
    GameObject* shadowManager;
    GameObject* chargeOverlap;
    GameObject* slope[2];
    GameObject* warning;
    GameObject* colonel;

    State* _state;
    Renderer* renderer;
    BoxCollider* collider;
    Animator* animator;
    PlayerControler* controler;
    AnimationClip* idleRight;
    AnimationClip* idleLeft;
    AnimationClip* idleAttackRight;
    AnimationClip* idleAttackLeft;
    AnimationClip* chargeAttackRight;
    AnimationClip* chargeAttackLeft;

    AnimationClip* runRight;
    AnimationClip* runLeft;
    AnimationClip* runAttackRight;
    AnimationClip* runAttackLeft;

    AnimationClip* jumpRight;
    AnimationClip* jumpLeft;
    AnimationClip* jumpAttackRight;
    AnimationClip* jumpAttackLeft;

    AnimationClip* fallRight;
    AnimationClip* fallLeft;
    AnimationClip* fallAttackRight;
    AnimationClip* fallAttackLeft;

    AnimationClip* wallRight;
    AnimationClip* wallLeft;
    AnimationClip* wallAttackRight;
    AnimationClip* wallAttackLeft;
    
    AnimationClip* groundRight;
    AnimationClip* groundLeft;
    AnimationClip* groundAttackRight;
    AnimationClip* groundAttackLeft;


    AnimationClip* intro;
    AnimationClip* outro;

    AnimationClip* dashRight;
    AnimationClip* dashAttackRight;
    AnimationClip* dashLeft;
    AnimationClip* dashAttackLeft;

    AnimationClip* breakRight;
    AnimationClip* breakAttackRight;
    AnimationClip* breakLeft;
    AnimationClip* breakAttackLeft;

    AnimationClip* smallHitRight;
    AnimationClip* smallHitLeft;

    void InputHandle();
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);
    void InitClip();
    void ChangeClip(string clipName, bool isInitFrame);
    void Attack();

    void MoveBossStart();
    void SetState(State* newState);
    void Dead();
    void Hit();
    void Clear();
};

