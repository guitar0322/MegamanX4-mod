#include "stdafx.h"
#include "SoldierAttack.h"
#include "SoldierIdle.h"
#include "Soldier.h"
SoldierState* SoldierAttack::Update(Soldier* soldier)
{
    _attackTime += TIMEMANAGER->getElapsedTime();
    if (_attackTime >= _attackTerm) {
        _attackNum++;
        if (_attackNum == 1)
            _attackTerm = 0.60f;
        _attackTime = 0;
        ProjectileManager::GetInstance()->FirePrivateProjectile(
            soldier->transform->GetX(),
            soldier->transform->GetY(),
            soldier->dir
        );
        if (_attackNum == _attackMaxNum)
            return new SoldierIdle();
    }
    return nullptr;
}

void SoldierAttack::Enter(Soldier* soldier)
{
    _attackTerm = 0.30f;
    _attackNum = 0;
    _attackMaxNum = RND->getFromIntTo(2, 5);
    if (soldier->dir == false) {
        soldier->ChangeClip("attack_right", false);
    }
    else {
        soldier->ChangeClip("attack_left", false);
    }
}
