#include "stdafx.h"
#include "SoldierThrow.h"
#include "SoldierIdle.h"
#include "Soldier.h"
SoldierState* SoldierThrow::Update(Soldier* soldier)
{
    _throwTime += TIMEMANAGER->getElapsedTime();
    if (_throwTime >= _throwCastTime) {
        ProjectileManager::GetInstance()->FirePrivateBomb(
            soldier->transform->GetX(),
            soldier->transform->GetY() - 50,
            soldier->dir
        );
        _throwCastTime = 100;
    }
    if (_throwTime >= _throwLimit) {
        return new SoldierIdle();
    }
    return nullptr;
}

void SoldierThrow::Enter(Soldier* soldier)
{
    if (soldier->dir == false) {
        soldier->ChangeClip("throw_right", false);
    }
    else {
        soldier->ChangeClip("throw_left", false);
    }
    _throwLimit = 1.5f;
    _throwCastTime = 0.5f;
}
