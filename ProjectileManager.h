#pragma once
#include "GameObject.h"
#define BASIC_PROJECTILE_NUM 10
#define TRAPBLAST_PROJECTILE_NUM 10
#define PRIVATE_PROJECTILE_NUM 20
#define PRIVATE_BOMB_NUM 10
class ProjectileObj;
class ProjectileManager :
    public Component
{
public:
    static ProjectileManager* _instance;
public:
    ProjectileObj* basicProjectile[BASIC_PROJECTILE_NUM];
    ProjectileObj* middleProjectile;
    ProjectileObj* fullProjectile;
    ProjectileObj* trapBlastProjectile[TRAPBLAST_PROJECTILE_NUM];
    ProjectileObj* privateProjectile[PRIVATE_PROJECTILE_NUM];
    ProjectileObj* privateBomb[PRIVATE_BOMB_NUM];

    virtual void Init();
    virtual void Update();
    virtual void Render();
    void FireBasicProjectile(int x, int y, bool dir);
    void FireMiddleProjectile(int x, int y, bool dir);
    void FireFullProjectile(int x, int y, bool dir);
    void FireTrapBlastProjectile(int x, int y, bool dir);
    void FirePrivateProjectile(int x, int y, bool dir);
    void FirePrivateBomb(int x, int y, bool dir);
    static ProjectileManager* GetInstance();
};

