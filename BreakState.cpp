#include "stdafx.h"
#include "BreakState.h"
#include "RunState.h"
#include "JumpState.h"
#include "FallState.h"
#include "IdleState.h"
State* BreakState::InputHandle(RockMan* rockman)
{
	if (breakTime >= 0.8f) {
		Exit(rockman);
		return new IdleState();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		rockman->dir = false;
		Exit(rockman);
		return new RunState();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		rockman->dir = true;
		Exit(rockman);
		return new RunState();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		Exit(rockman);
		return new JumpState();
	}
    if (isFall == true) {
        return new FallState();
    }
    return nullptr;
}

void BreakState::Update(RockMan* rockman)
{
	breakTime += TIMEMANAGER->getElapsedTime();
    speedX -= friction * TIMEMANAGER->getElapsedTime();
    if (speedX <= 0)
        speedX = 0;
    if (rockman->isBoss == true) {
        if (rockman->dir == true && rockman->transform->GetX() - speedX >= 9900 - WINSIZEX / 2 + 35) {
            rockman->transform->MoveX(-speedX);
        }
        else if (rockman->dir == false && rockman->transform->GetX() + speedX <= 9900 + WINSIZEX / 2 - 35) {
            rockman->transform->MoveX(speedX);
        }
    }
    else {
        if (rockman->dir == true)
            rockman->transform->MoveX(-speedX);
        else
            rockman->transform->MoveX(speedX);
    }
    if (rockman->controler->CheckSlope() == false && rockman->controler->CheckGround() == false) {
        isFall = true;
    }
    if (rockman->dir == false) {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 18);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 18);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 18);
    }
    else {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 18);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 18);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 18);
    }
}

void BreakState::Enter(RockMan* rockman)
{
	breakTime = 0;
    speedX = rockman->speedX;
    friction = 5;
	if (rockman->dir == false) {
        if (rockman->isAttack == true) 
            rockman->ChangeClip("break_attack_right", false);
        else
		    rockman->ChangeClip("break_right", false);
	}
	else {
        if (rockman->isAttack == true)
            rockman->ChangeClip("break_attack_left", false);
        else
		    rockman->ChangeClip("break_left", false);
	}
    rockman->isDash = false;
    rockman->shadowManager->GetComponent<ShadowManager>()->OffShadow();
}

void BreakState::Exit(RockMan* rockman)
{
}

void BreakState::Attack(RockMan* rockman)
{
    if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            rockman->ChangeClip("break_attack_right", true);
        }
        else {
            rockman->ChangeClip("break_attack_left", true);
        }
        if (rockman->isFullChargeAttack == true) {
            rockman->fullAttackEffect->GetComponent<Effect>()->Emission(rockman->dir);
        }
        else if (rockman->isMiddleChargeAttack == true) {
            rockman->middleAttackEffect->GetComponent<Effect>()->Emission(rockman->dir);
        }
        else {
            rockman->basicAttackEffect->GetComponent<Effect>()->Emission(rockman->dir);
        }
        if (rockman->isFullChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 18, rockman->dir);
        }
        else if (rockman->isMiddleChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireMiddleProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 18, rockman->dir);
        }
        else {
            ProjectileManager::GetInstance()->
                FireBasicProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 18, rockman->dir);
        }
    }
    else {
        if (rockman->dir == false) {
            rockman->ChangeClip("break_right", true);
        }
        else {
            rockman->ChangeClip("break_left", true);
        }
    }
}
