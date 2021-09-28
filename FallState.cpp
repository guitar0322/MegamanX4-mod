#include "stdafx.h"
#include "FallState.h"
#include "IdleState.h"
#include "WallState.h"
#include "GroundState.h"

State* FallState::InputHandle(RockMan* rockman)
{
	if (isGround == true) {
		rockman->isFall = false;
		return new GroundState();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		rockman->dir = false;
		rockman->ChangeClip("fall_right", true);
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
		rockman->ChangeClip("fall_left", true);
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

void FallState::Update(RockMan* rockman)
{
	if (rockman->transform->MoveY(speedY * TIMEMANAGER->getElapsedTime()) == false || rockman->controler->CheckSlope() == true) {
		isGround = true;
	}
	speedY += rockman->gravity;
	if (speedY >= 300) {
		speedY = 300;
	}
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

void FallState::Enter(RockMan* rockman)
{
	if (rockman->dir == false) {
		if (rockman->isAttack == true)
			rockman->ChangeClip("fall_attack_right", false);
		else
			rockman->ChangeClip("fall_right", false);
	}
	else {
		if (rockman->isAttack == true)
			rockman->ChangeClip("fall_attack_left", false);
		else
			rockman->ChangeClip("fall_left", false);
	}
	speedY = 0;
	isGround = false;
}

void FallState::Exit(RockMan* rockman)
{
}

void FallState::Attack(RockMan* rockman)
{
	if (rockman->isAttack == true) {
		if (rockman->dir == false) {
			rockman->ChangeClip("fall_attack_right", true);
		}
		else {
			rockman->ChangeClip("fall_attack_left", true);
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
			rockman->ChangeClip("fall_right", true);
		}
		else {
			rockman->ChangeClip("fall_left", true);
		}
	}
}
