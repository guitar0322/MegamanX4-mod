#include "stdafx.h"
#include "ItemCarrierSpawner.h"

void ItemCarrierSpawner::Init()
{
    _spawnPercent = 80;
    _spawnPos[0] = 200;
    _spawnPos[1] = 3600;
    _spawnPos[2] = 5650;

    for (int i = 0; i < 3; i++) {
        _spawnFlag[i] = false;
    }
}

void ItemCarrierSpawner::Update()
{
    for (int i = 0; i < 3; i++) {
        if (_rockmanTr->GetX() >= _spawnPos[i] && _spawnFlag[i] == false) {
            SpawnItemCarrier(i);
        }
    }
}

void ItemCarrierSpawner::SpawnItemCarrier(int idx)
{
    int randNum = RND->getInt(100);
    _spawnFlag[idx] = true;
    if (_rockmanInfo->GetCurHP() > 80 || randNum >= _spawnPercent)
        return;
    _itemCarrier->transform->SetPosition(_spawnPos[idx] + 500, 240);
    _itemCarrier->SetActive(true);
}
