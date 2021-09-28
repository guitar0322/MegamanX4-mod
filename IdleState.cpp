#include "stdafx.h"
#include "IdleState.h"
#include "RunState.h"
#include "RockMan.h"
#include "JumpState.h"
#include "FallState.h"
#include "DashState.h"
State* IdleState::InputHandle(RockMan* rockman)
{
    if(KEYMANAGER->isStayKeyDown(VK_RIGHT)){
        rockman->dir = false;
        return new RunState();
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        rockman->dir = true;
        return new RunState();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		return new JumpState();
    }
    if (KEYMANAGER->isOnceKeyDown('Z')) {
        return new DashState();
    }
    if (isFall == true) {
        return new FallState();
    }
    return nullptr;
}

void IdleState::Update(RockMan* rockman)
{
    if (rockman->controler->CheckSlope() == false && rockman->controler->CheckGround() == false) {
        isFall = true;
    }
}

void IdleState::Enter(RockMan* rockman)
{
    if (rockman->dir == false) {
        rockman->ChangeClip("idle_right", false);
    }
    else {
        rockman->ChangeClip("idle_left", false);
    }
    isFall = false;
}

void IdleState::Exit(RockMan* rockman)
{
}

void IdleState::Attack(RockMan* rockman)
{
    if (rockman->isFullChargeAttack == true) {
        if (rockman->dir == false) {
            rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18);
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18, false);
            rockman->ChangeClip("charge_attack_right", false);
        }
        else {
            rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18);
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18, true);
            rockman->ChangeClip("charge_attack_left", false);
        }
    }
    else if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            if (rockman->isMiddleChargeAttack == true) {
                rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18);
                ProjectileManager::GetInstance()->
                    FireMiddleProjectile(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18, false);
            }
            else {
				rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18);
                ProjectileManager::GetInstance()->
                    FireBasicProjectile(rockman->transform->GetX() + 40, rockman->transform->GetY() - 18, false);
            }
			rockman->ChangeClip("idle_attack_right", false);
        }
        else {
            if (rockman->isMiddleChargeAttack == true) {
                rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18);
                ProjectileManager::GetInstance()->
                    FireMiddleProjectile(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18, true);
            }
            else {
				rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18);
                ProjectileManager::GetInstance()->
                    FireBasicProjectile(rockman->transform->GetX() - 40, rockman->transform->GetY() - 18, true);
            }
			rockman->ChangeClip("idle_attack_left", false);
        }
    }
    else {
        if (rockman->dir == false) {
            rockman->ChangeClip("idle_right", false);
        }
        else {
            rockman->ChangeClip("idle_left", false);
        }
    }
}
