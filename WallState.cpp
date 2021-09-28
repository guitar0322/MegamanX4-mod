#include "stdafx.h"
#include "WallState.h"
#include "FallState.h"
#include "GroundState.h"
#include "WallJumpState.h"

State* WallState::InputHandle(RockMan* rockman)
{
    if (isGround == true) {
        rockman->wallSmokeEffect->GetComponent<Effect>()->End(rockman->dir);
        return new GroundState();
    }
    if (isFall == true) {
        rockman->wallSmokeEffect->GetComponent<Effect>()->End(rockman->dir);
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && rockman->dir == true) {
        rockman->wallSmokeEffect->GetComponent<Effect>()->End(rockman->dir);
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && rockman->dir == false) {
        rockman->wallSmokeEffect->GetComponent<Effect>()->End(rockman->dir);
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
        rockman->wallSmokeEffect->GetComponent<Effect>()->End(rockman->dir);
        rockman->dir = !rockman->dir;
        if (KEYMANAGER->isStayKeyDown('Z')) {
            rockman->shadowManager->GetComponent<ShadowManager>()->OnShadow();
            rockman->isDash = true;
        }
        return new WallJumpState();
    }
    return nullptr;
}

void WallState::Update(RockMan* rockman)
{
    slipSpeed = 70 * TIMEMANAGER->getElapsedTime();
    if (rockman->transform->MoveY(slipSpeed) == false) {
        isGround = true;
    }
    if (CheckWall(rockman) == false) {
        isFall = true;
    }
    if (rockman->dir == false) {
        rockman->wallSmokeEffect->transform->SetPosition(rockman->transform->GetX() - 35, rockman->transform->GetY() + 20);
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() + 50, rockman->transform->GetY() - 20);
    }
    else {
        rockman->wallSmokeEffect->transform->SetPosition(rockman->transform->GetX() + 35, rockman->transform->GetY() + 20);
        rockman->basicAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
        rockman->middleAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
        rockman->fullAttackEffect->transform->SetPosition(rockman->transform->GetX() - 50, rockman->transform->GetY() - 20);
    }
}

void WallState::Enter(RockMan* rockman)
{
    if (rockman->dir == false) {
        if (rockman->isAttack == true)
            rockman->ChangeClip("wall_attack_left", false);
        else
            rockman->ChangeClip("wall_left", false);
        rockman->wallSmokeEffect->transform->SetPosition(rockman->transform->GetX() - 35, rockman->transform->GetY() + 20);
    }
    else {
        if (rockman->isAttack == true)
            rockman->ChangeClip("wall_attack_right", false);
        else
            rockman->ChangeClip("wall_right", false);
        rockman->wallSmokeEffect->transform->SetPosition(rockman->transform->GetX() + 35, rockman->transform->GetY() + 20);
    }
    rockman->wallSmokeEffect->GetComponent<Effect>()->Emission(!rockman->dir);
    rockman->shadowManager->GetComponent<ShadowManager>()->OffShadow();
    rockman->isDash = false;
    slipSpeed = 100 * TIMEMANAGER->getElapsedTime();
}

void WallState::Exit(RockMan* rockman)
{
}

void WallState::Attack(RockMan* rockman)
{
    if (rockman->isAttack == true) {
        if (rockman->dir == false) {
            rockman->ChangeClip("wall_attack_left", true);
        }
        else {
            rockman->ChangeClip("wall_attack_right", true);
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
            rockman->ChangeClip("wall_left", true);
        }
        else {
            rockman->ChangeClip("wall_right", true);
        }
    }
}

bool WallState::CheckWall(RockMan* rockman)
{
    bool result = false;
    BoxCollider* collider = rockman->gameObject->GetComponent<BoxCollider>();
    if (collider == nullptr)
        return result;
    RECT intersectRc;
    RECT* targetRc;
    if (rockman->dir == false) {
        sideRc = RectMakeCenter(rockman->transform->GetX() - collider->width / 2 - 1, rockman->transform->GetY(), 10, collider->height);
    }
    else {
        sideRc = RectMakeCenter(rockman->transform->GetX() + collider->width / 2 + 1, rockman->transform->GetY(), 10, collider->height);
    }
    int colNum = COLLIDERMANAGER->colliderList.size();
    for (int i = 0; i < colNum; i++) {
        if (collider == COLLIDERMANAGER->colliderList[i]) continue;
        if (COLLIDERMANAGER->colliderList[i]->isTrigger == true) continue;
        targetRc = &COLLIDERMANAGER->colliderList[i]->rc;
        if (IntersectRect(&intersectRc, &sideRc, targetRc)) {
            int w = intersectRc.right - intersectRc.left;
            int h = intersectRc.bottom - intersectRc.top;
            if (h > w) {
                result = true;
                return result;
            }
        }
    }
    return result;
}
