#pragma once
#include "Scene.h"
#define BACKGROUND_NUM 16
#define WALL_NUM 9
#define GROUND_NUM 11
#define ROCK_NUM 5
#define FOUNDATION_NUM 1
#define FOUNDATION_DOWN_NUM 1
#define TRAP_NUM 14
#define SINKHALL_NUM 2
#define FRONT_NUM 9
#define TRAPBLAST_NUM 12
#define PRIVATE_NUM 4
#define BASIC_PROJECTILE_NUM 10
#define TRAPBLAST_PROJECTILE_NUM 10
#define PRIVATE_PROJECTILE_NUM 20
#define PRIVATE_BOMB_NUM 10
class StartScene :
    public Scene
{
private:
    float timeStack;
public:
    StartScene();
    ~StartScene();
    ImageObject background[16];
    ImageObject holeBackground;
    GameObject backgroundControl;
    ImageObject introLazer;
    GameObject deathBubble;
    AnimationClip rockFrag1, rockFrag2, rockFrag3;
    AnimationClip trapBlastFrag1, trapBlastFrag2, trapBlastFrag3;
    AnimationClip privateFrag1, privateFrag2, privateFrag3, privateFrag4, privateFrag5;
    EffectObj wallSparkEffect;
    EffectObj wallSmokeEffect;
    EffectObj dashEffect;
    EffectObj dashSmokeEffect;
    EffectObj basicAttackEffect;
    EffectObj middleAttackEffect;
    EffectObj fullAttackEffect;
    EffectObj middleChargeEffect;
    EffectObj fullChargeEffect;

    ImageObject shadow[3];
    ImageObject chargeOverlap;
    GameObject trap[TRAP_NUM];
    GameObject shadowManager;
    GameObject trapManager;
    GameObject cameraMovement;
    GameObject warning;
    UIBase hpBar;
    UIBase fadeOut;
    UIBase whiteFadeOut;

    ProjectileObj basicProjectile[BASIC_PROJECTILE_NUM];
    ProjectileObj middleProjectile;
    ProjectileObj fullProjectile;
    ProjectileObj trapBlastProjectile[TRAPBLAST_PROJECTILE_NUM];
    ProjectileObj privateProjectile[PRIVATE_PROJECTILE_NUM];
    ProjectileObj privateBomb[PRIVATE_BOMB_NUM];

    GameObject rockman;
    Character colonel;
    GameObject trapBlast[TRAPBLAST_NUM];
    GameObject soldier[PRIVATE_NUM];
    GameObject itemCarrier;
    GameObject itemCarrierSpawner;
    Box healPack;

    Zone clearZone;
    Box ground[GROUND_NUM];
    Box wall[WALL_NUM];
    Box rock[ROCK_NUM];
    Box foundation[FOUNDATION_NUM];
    Box foundationDown[FOUNDATION_DOWN_NUM];
    Box sinkhole[SINKHALL_NUM];
    Box trapWall[2];
    ImageObject frontObj[FRONT_NUM];
    GameObject slope[2];
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
    void BackgroundInit();
    void RockmanInit();
    void ColonelInit();
    void MapInit();
    void EnemyInit();
    void EffectInit();
    void ShadowInit();
    void ProjectileInit();
    void TrapInit();
};

