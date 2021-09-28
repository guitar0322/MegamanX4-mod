#include "stdafx.h"
#include "TrapBlastProjectile.h"

void TrapBlastProjectile::Update()
{
	Projectile::Update();
	transform->position.x += _speed * cosf(_angle) * TIMEMANAGER->getElapsedTime();
	transform->position.y += _speed * -sinf(_angle) * TIMEMANAGER->getElapsedTime();
}

void TrapBlastProjectile::OnTriggerEnter(GameObject* gameObject)
{
	Projectile::OnTriggerEnter(gameObject);
}

void TrapBlastProjectile::Fire(int x, int y, bool dir)
{
	Projectile::Fire(x, y, dir);
	_angle = GetAngle(gameObject->transform->GetX(), gameObject->transform->GetY(),
		_rockman->transform->GetX(), _rockman->transform->GetY());

}
