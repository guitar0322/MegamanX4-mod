#include "stdafx.h"
#include "SoldierIdle.h"
#include "SoldierThrow.h"
#include "SoldierAttack.h"
#include "Soldier.h"
SoldierState* SoldierIdle::Update(Soldier* soldier)
{
    _idleTime += TIMEMANAGER->getElapsedTime();
    float distance = GetDistance(soldier->transform->GetX(), soldier->transform->GetY(),
        soldier->rockman->transform->GetX(), soldier->rockman->transform->GetY());
    if (distance <= 300) {
		if (_idleTime >= _attackTerm) {
			int pattern = RND->getInt(10);
			if (pattern <= 6) {
				return new SoldierAttack();
			}
			else {
				return new SoldierThrow();
			}
		}
    }
    return nullptr;
}

void SoldierIdle::Enter(Soldier* soldier)
{
    if (soldier->dir == false) {
        soldier->ChangeClip("idle_right", false);
    }
    else {
        soldier->ChangeClip("idle_left", false);
    }
    _attackTerm = 5.0f;
}
