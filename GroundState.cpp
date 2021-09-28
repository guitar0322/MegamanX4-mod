#include "stdafx.h"
#include "GroundState.h"
#include "RunState.h"
#include "JumpState.h"
#include "IdleState.h"
State* GroundState::InputHandle(RockMan* rockman)
{
	if (groundTime >= 0.5f) {
		return new IdleState();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
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
	return nullptr;
}

void GroundState::Update(RockMan* rockman)
{
	groundTime += TIMEMANAGER->getElapsedTime();
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

void GroundState::Enter(RockMan* rockman)
{
	groundTime = 0;
	if (rockman->dir == false) {
		if (rockman->isAttack == true)
			rockman->ChangeClip("ground_attack_right", false);
		else
			rockman->ChangeClip("ground_right", false);
	}
	else {
		if (rockman->isAttack == true)
			rockman->ChangeClip("ground_attack_left", false);
		else
			rockman->ChangeClip("ground_left", false);
	}
	rockman->shadowManager->GetComponent<ShadowManager>()->OffShadow();
	rockman->isDash = false;
}

void GroundState::Exit(RockMan* rockman)
{
}

void GroundState::Attack(RockMan* rockman)
{
	if (rockman->isAttack == true) {
		if (rockman->dir == false) {
			rockman->ChangeClip("ground_attack_right", true);
		}
		else {
			rockman->ChangeClip("ground_attack_left", true);
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
			rockman->ChangeClip("ground_right", true);
		}
		else {
			rockman->ChangeClip("ground_left", true);
		}
	}
}
