#pragma once
#include "GameObject.h"
class EnemySpawner :
    public Component
{
private:
    RockMan* _rockman;
public:
    GameObject* trapBlast[2];
    virtual void Init(RockMan* rockman);
    virtual void Update();
    virtual void Render();

    void SpawnTrapBlast(int idx);
};

