#include "stdafx.h"
#include "ProjectileManager.h"
#include "Projectile.h"

void ProjectileManager::Init()
{
}

void ProjectileManager::Update()
{
}

void ProjectileManager::Render()
{
}

void ProjectileManager::FireBasicProjectile(int x, int y, bool dir)
{
	for (int i = 0; i < BASIC_PROJECTILE_NUM; i++) {
		if (basicProjectile[i]->isActive == true) continue;
		basicProjectile[i]->GetComponent<StraightProjectile>()->Fire(x, y, dir);
		break;
	}
}

void ProjectileManager::FireMiddleProjectile(int x, int y, bool dir)
{
	middleProjectile->GetComponent<StraightProjectile>()->Fire(x, y, dir);
}

void ProjectileManager::FireFullProjectile(int x, int y, bool dir)
{
	fullProjectile->GetComponent<StraightProjectile>()->Fire(x, y, dir);
}

void ProjectileManager::FireTrapBlastProjectile(int x, int y, bool dir)
{
	for (int i = 0; i < TRAPBLAST_PROJECTILE_NUM; i++) {
		if (trapBlastProjectile[i]->isActive == true) continue;
		trapBlastProjectile[i]->GetComponent<TrapBlastProjectile>()->Fire(x, y, dir);
		break;
	}
}

void ProjectileManager::FirePrivateProjectile(int x, int y, bool dir)
{
	for (int i = 0; i < PRIVATE_PROJECTILE_NUM; i++) {
		if (privateProjectile[i]->isActive == true) continue;
		privateProjectile[i]->GetComponent<StraightProjectile>()->Fire(x, y, dir);
		break;
	}
}

void ProjectileManager::FirePrivateBomb(int x, int y, bool dir)
{
	for (int i = 0; i < PRIVATE_BOMB_NUM; i++) {
		if (privateBomb[i]->isActive == true) continue;
		privateBomb[i]->GetComponent<PrivateBomb>()->Fire(x, y, dir);
		break;
	}
}

ProjectileManager* ProjectileManager::_instance = 0;

ProjectileManager* ProjectileManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new ProjectileManager();
	}
	return _instance;
}
