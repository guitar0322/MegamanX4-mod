#include "stdafx.h"
#include "WallJumpState.h"
#include "FallState.h"
#include "WallState.h"

State* WallJumpState::InputHandle(RockMan* rockman)
{
	if (wallJumpPowerY > 0) {
		return new FallState();
	}
	if (wallJumpPowerX == 0) {
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			rockman->dir = false;
			rockman->ChangeClip("jump_right", true);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (rockman->transform->MoveX(rockman->speedX) == false) {
				rockman->dir = true;
				return new WallState();
			}

		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			rockman->dir = true;
			rockman->ChangeClip("jump_left", true);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (rockman->transform->MoveX(-rockman->speedX) == false) {
				rockman->dir = false;
				return new WallState();
			}
		}
	}
	return nullptr;
}

void WallJumpState::Update(RockMan* rockman)
{
	rockman->transform->MoveY(wallJumpPowerY * TIMEMANAGER->getElapsedTime());
	rockman->transform->MoveX(wallJumpPowerX * TIMEMANAGER->getElapsedTime());
	wallJumpPowerY += rockman->gravity;
	if (wallJumpPowerX != 0) {
		if (rockman->dir == false) {
			wallJumpPowerX += airResistance;
			if (wallJumpPowerX > 0)
				wallJumpPowerX = 0;
		}
		else {
			wallJumpPowerX -= airResistance;
			if (wallJumpPowerX < 0)
				wallJumpPowerX = 0;
		}
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
	airResistance = 500 * TIMEMANAGER->getElapsedTime();
}

void WallJumpState::Enter(RockMan* rockman)
{
	if (rockman->dir == false) {
		if (rockman->isAttack == true)
			rockman->ChangeClip("jump_attack_right", false);
		else
			rockman->ChangeClip("jump_right", false);
		rockman->wallSparkEffect->transform->SetPosition(rockman->transform->GetX() + 35, rockman->transform->GetY() + 35);
		if (rockman->isDash == true)
			wallJumpPowerX = -200;
		else
			wallJumpPowerX = -200;
	}
	else {
		if (rockman->isAttack == true)
			rockman->ChangeClip("jump_attack_left", false);
		else
			rockman->ChangeClip("jump_left", false);
		rockman->wallSparkEffect->transform->SetPosition(rockman->transform->GetX() - 35, rockman->transform->GetY() + 35);
		if (rockman->isDash == true)
			wallJumpPowerX = 200;
		else
			wallJumpPowerX = 200;
	}
	rockman->wallSparkEffect->GetComponent<Effect>()->Emission(false);
	airResistance = 500 * TIMEMANAGER->getElapsedTime();
	if (rockman->isDash == true)
		wallJumpPowerY = -350;
	else
		wallJumpPowerY = -300; 
}

void WallJumpState::Exit(RockMan* rockman)
{
}

void WallJumpState::Attack(RockMan* rockman)
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
