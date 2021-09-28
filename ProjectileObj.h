#pragma once
#include "GameObject.h"
class ProjectileObj :
    public GameObject
{
public:
    ProjectileObj() {};
    ~ProjectileObj() {};
    Renderer* renderer;
    Animator* animator;
    BoxCollider* collider;
    AnimationClip* clip;
    Projectile* projectileComponent;
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void SetProjectileComponent(Projectile* projectileComponent);
};

