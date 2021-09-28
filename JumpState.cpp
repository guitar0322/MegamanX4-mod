#include "stdafx.h"
#include "JumpState.h"
#include "FallState.h"
#include "WallState.h"
State* JumpState::InputHandle(RockMan* rockman)
{
    if (isFall == true) {
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyUp(VK_SPACE) || jumpTime >= jumpLimitTime || jumpPower > 0) {
		return new FallState();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
        rockman->dir = false;
        rockman->ChangeClip("jump_right", true);
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        if (rockman->isBoss == true) {
            if (rockman->transform->GetX() + rockman->speedX <= 9900 + WINSIZEX / 2 - 35) {
                rockman->transform->MoveX(rockman->speedX);
            }
        }
        else {
			if (rockman->transform->MoveX(rockman->speedX) == false) {
				rockman->dir = true;
				return new WallState();
			}
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
        rockman->dir = true;
        rockman->ChangeClip("jump_left", true);
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        if (rockman->isBoss == true) {
            if (rockman->transform->GetX() - rockman->speedX >= 9900 - WINSIZEX / 2 + 35) {
                rockman->transform->MoveX(-rockman->speedX);
            }
        }
        else {
            if (rockman->transform->MoveX(-rockman->speedX) == false) {
                rockman->dir = false;
                return new WallState();
            }
        }
    }

    return nullptr;
}

void JumpState::Update(RockMan* rockman)
{
    if (rockman->transform->MoveY((int)(jumpPower * TIMEMANAGER->getElapsedTime())) == false) {
        isFall = true;
    }
    jumpPower += rockman->gravity;
	jumpTime += TIMEMANAGER->getElapsedTime();
    if (rockman->dir == false) {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
    }
    else {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
    }
}

void JumpState::Enter(RockMan* rockman)
{
    if (rockman->dir == false) {
        if (rockman->isAttack == true)
            rockman->ChangeClip("jump_attack_right", false);
        else
            rockman->ChangeClip("jump_right", false);
    }
    else {
        if (rockman->isAttack == true)
            rockman->ChangeClip("jump_attack_left", false);
        else
            rockman->ChangeClip("jump_left", false);
    }
    jumpPower = -300;
    jumpTime = 0;
    jumpLimitTime = 1;
}

void JumpState::Exit(RockMan* rockman)
{
}

void JumpState::Attack(RockMan* rockman)
{
    if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            rockman->ChangeClip("jump_attack_right", true);
        }
        else {
            rockman->ChangeClip("jump_attack_left", true);
        }
        if (rockman->isFullChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() + (rockman->dir ? -50 : 50), rockman->transform->GetY() - 20, rockman->dir);
        }
        else if (rockman->isMiddleChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireMiddleProjectile(rockman->transform->GetX() + (rockman->dir ? -50 : 50), rockman->transform->GetY() - 20, rockman->dir);
        }
        else {
            ProjectileManager::GetInstance()->
                FireBasicProjectile(rockman->transform->GetX() + (rockman->dir ? -50 : 50), rockman->transform->GetY() - 20, rockman->dir);
        }
    }
    else {
        if (rockman->dir == false) {
            rockman->ChangeClip("jump_right", true);
        }
        else {
            rockman->ChangeClip("jump_left", true);
        }
    }
}
