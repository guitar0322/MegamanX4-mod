#include "stdafx.h"
#include "RunState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"
#include "DashState.h"

State* RunState::InputHandle(RockMan* rockman)
{
    if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
        return new IdleState();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
        return new JumpState();
    }
    if (isFall == true) {
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyDown('Z')) {
        return new DashState();
    }
    return nullptr;
}

void RunState::Update(RockMan* rockman)
{
    if (rockman->isBoss == true) {
        if (rockman->dir == true && rockman->transform->GetX() - rockman->speedX >= 9900 - WINSIZEX / 2 + 35) {
            rockman->transform->MoveX(-rockman->speedX);
        }
        else if(rockman->dir == false && rockman->transform->GetX() + rockman->speedX <= 9900 + WINSIZEX / 2 - 35){
            rockman->transform->MoveX(rockman->speedX);
        }
    }
    else {
        if (rockman->dir == true)
			rockman->transform->MoveX(-rockman->speedX);
        else
			rockman->transform->MoveX(rockman->speedX);
    }
    if (rockman->dir == false) {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 22);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 22);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 60, rockman->transform->GetY() - 22);
    }
    else {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 22);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 22);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 60, rockman->transform->GetY() - 22);
    }
    if (rockman->controler->CheckSlope() == false && rockman->controler->CheckGround() == false) {
        isFall = true;
    }
}

void RunState::Enter(RockMan* rockman)
{
    if (rockman->dir == false) {
        if (rockman->isAttack == true)
            rockman->ChangeClip("run_attack_right", false);
        else
            rockman->ChangeClip("run_right", false);
    }
    else {
        if (rockman->isAttack == true)
            rockman->ChangeClip("run_attack_left", false);
        else
            rockman->ChangeClip("run_left", false);
    }
    rockman->shadowManager->GetComponent<ShadowManager>()->OffShadow();
    rockman->isDash = false;
    isFall = false;
}

void RunState::Exit(RockMan* rockman)
{
}

void RunState::Attack(RockMan* rockman)
{
    if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            rockman->ChangeClip("run_attack_right", true);
        }
        else {
            rockman->ChangeClip("run_attack_left", true);
        }
        if (rockman->isFullChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 22, rockman->dir);
        }
        else if (rockman->isMiddleChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireMiddleProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 22, rockman->dir);
        }
        else {
            ProjectileManager::GetInstance()->
                FireBasicProjectile(rockman->transform->GetX() + (rockman->dir ? -60 : 60), rockman->transform->GetY() - 22, rockman->dir);
        }
    }
    else {
        if (rockman->dir == false) {
            rockman->ChangeClip("run_right", true);
        }
        else {
            rockman->ChangeClip("run_left", true);
        }
    }
}
