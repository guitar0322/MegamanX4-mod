#pragma once
#include "GameObject.h"
class ColonelState;
class Colonel :
    public Component
{
private:
    bool _isIntro;
    bool _isHit;
    bool _isDead;
    float _hitTime;
    float _stateTime;
    float _dashSpeed;
    float _friction;
    float _shadowSpeed;
    float _destroyTime;
    float _destroyChangeTime;
    bool _destroyFlag;
    int _slashNum;
    int _whiteAlpha;
    int destroyNum;
    bool _overlapFlag;
    float _overlapChangeTime;
    Overlap* _overlap;
    ProjectileObj _slashProjectile[3];
    AnimObject shadowLeft;
    AnimObject shadowRight;
    ImageObject overlap;
    ImageObject destroy1, destroy2;
    UIBase hpBar;
    ObjectInfo* _objectInfo;
    GameObject* _rockman;
    RockMan* _rockmanComponent;
    RECT attackRc;
    Renderer* _renderer;
    BoxCollider* _collider;
    Animator* _animator;
    ColonelState* _state;
private:
    AnimationClip _idleRight;
    AnimationClip _idleLeft;
    AnimationClip _upSwordRight;
    AnimationClip _upSwordLeft;
    AnimationClip _downSwordRight;
    AnimationClip _downSwordLeft;
    AnimationClip _dashRight;
    AnimationClip _dashLeft;
    AnimationClip _dead;
    
    AnimationClip _shadowRight;
    AnimationClip _shadowLeft;

    AnimationClip* _projectileRight;
    AnimationClip* _projectileLeft;
public:
    UIBase* whiteFadeOut;
    bool _dir;
    virtual void Init(GameObject* rockman);
    virtual void Update();
    virtual void Render();
    virtual void OnEnable();
    void PropertyInit();
    void ClipInit();
    void ShadowInit();
    void HPBarInit();
    void OverlapInit();
    void ProjectileInit();
    void Hit();
    void ChangeClip(string clipName);
    void FireProjectile();
    int GetSlashNum() { return _slashNum; }
    void Disappear();
    void Appear();
    void ShadowMove();
    void CheckHit();
    void SetDashDir();
    void Dead();
    void Destroy();
};

