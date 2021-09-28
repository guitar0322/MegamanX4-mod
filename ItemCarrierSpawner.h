#pragma once
#include "GameObject.h"
class ItemCarrierSpawner :
    public Component
{
private:
    bool _spawnFlag[3];
    int _spawnPos[3];
    ObjectInfo* _rockmanInfo;
    Transform* _rockmanTr;
    int _spawnPercent;
    GameObject* _itemCarrier;
public:
    virtual void Init();
    virtual void Update();
    void SetItemCarrier(GameObject* itemCarrier) { _itemCarrier = itemCarrier; }
    void SpawnItemCarrier(int idx);
    void SetRockmanInfo(ObjectInfo* rockmanInfo) { _rockmanInfo = rockmanInfo; _rockmanTr = rockmanInfo->transform; }
};

