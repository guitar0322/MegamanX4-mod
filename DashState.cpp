#include "stdafx.h"
#include "DashState.h"
#include "BreakState.h"
#include "RunState.h"
#include "JumpState.h"
#include "FallState.h"

State* DashState::InputHandle(RockMan* rockman)
{
    if (dashTime >= dashLimitTime) {
        Exit(rockman);
        return new BreakState();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
        rockman->isDash = true;
        Exit(rockman);
        return new JumpState();
    }
    if (rockman->dir == false) {
        if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
            rockman->dir = true;
            Exit(rockman);
            return new RunState();
        }
        if (KEYMANAGER->isStayKeyDown(VK_RIGHT) == false && KEYMANAGER->isOnceKeyUp('Z')) {
            Exit(rockman);
            return new BreakState();
        }
    }
    else {
        if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
            rockman->dir = false;
            Exit(rockman);
            return new RunState();
        }
        if (KEYMANAGER->isStayKeyDown(VK_LEFT) == false && KEYMANAGER->isOnceKeyUp('Z')) {
            Exit(rockman);
            return new BreakState();
        }
    }
    if (isFall == true) {
        Exit(rockman);
        return new FallState();
    }
    return nullptr;
}

void DashState::Update(RockMan* rockman)
{
    if (rockman->isBoss == true) {
        if (rockman->dir == true && rockman->transform->GetX() - rockman->speedX >= 9900 - WINSIZEX / 2 + 35) {
            rockman->transform->MoveX(-rockman->speedX);
        }
        else if (rockman->dir == false && rockman->transform->GetX() + rockman->speedX <= 9900 + WINSIZEX / 2 - 35) {
            rockman->transform->MoveX(rockman->speedX);
        }
    }
    else {
        if (rockman->dir == true)
            rockman->transform->MoveX(-rockman->speedX);
        else
            rockman->transform->MoveX(rockman->speedX);
    }
    dashTime += TIMEMANAGER->getElapsedTime();
    if (rockman->controler->CheckSlope() == false && rockman->controler->CheckGround() == false) {
        isFall = true;
    }
    if (rockman->dir == false) {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 67, rockman->transform->GetY() + 7);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 67, rockman->transform->GetY() + 7);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 67, rockman->transform->GetY() + 7);
    }
    else {
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 67, rockman->transform->GetY() + 7);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 67, rockman->transform->GetY() + 7);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 67, rockman->transform->GetY() + 7);
    }
}

void DashState::Enter(RockMan* rockman)
{
    rockman->collider->SetSize(74, 45);
    if (rockman->dir == false) {
        rockman->ChangeClip("dash_right", false);
        rockman->dashEffect->transform->SetPosition(rockman->transform->GetX() - 120, rockman->transform->GetY() + 15);
        rockman->dashSmokeEffect->transform->SetPosition(rockman->transform->GetX() - 100, rockman->transform->GetY() + 15);
    }
    else {
        rockman->ChangeClip("dash_left", false);
        rockman->dashEffect->transform->SetPosition(rockman->transform->GetX() + 120, rockman->transform->GetY() + 15);
        rockman->dashSmokeEffect->transform->SetPosition(rockman->transform->GetX() + 100, rockman->transform->GetY() + 15);

    }
    rockman->dashEffect->GetComponent<Effect>()->Emission(rockman->dir);
    rockman->dashSmokeEffect->GetComponent<Effect>()->Emission(rockman->dir);
    rockman->shadowManager->GetComponent<ShadowManager>()->OnShadow();
    rockman->isDash = true;
    dashLimitTime = 1.2f;
    dashTime = 0;
}

void DashState::Exit(RockMan* rockman)
{
    rockman->collider->SetSize(74, 90);
}

void DashState::Attack(RockMan* rockman)
{
    if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            rockman->ChangeClip("dash_attack_right", true);
        }
        else {
            rockman->ChangeClip("dash_attack_left", true);
        }

        if (rockman->isFullChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireFullProjectile(rockman->transform->GetX() + (rockman->dir ? -67 : 67), rockman->transform->GetY() + 7, rockman->dir);
        }
        else if (rockman->isMiddleChargeAttack == true) {
            ProjectileManager::GetInstance()->
                FireMiddleProjectile(rockman->transform->GetX() + (rockman->dir ? -67 : 67), rockman->transform->GetY() + 7, rockman->dir);
        }
        else {
            ProjectileManager::GetInstance()->
                FireBasicProjectile(rockman->transform->GetX() + (rockman->dir ? -67 : 67), rockman->transform->GetY() + 7, rockman->dir);
        }
    }
    else {
        if (rockman->dir == false) {
            rockman->ChangeClip("dash_right", true);
        }
        else {
            rockman->ChangeClip("dash_left", true);
        }
    }
}
