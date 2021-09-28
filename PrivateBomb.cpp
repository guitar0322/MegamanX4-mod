#include "stdafx.h"
#include "PrivateBomb.h"

void PrivateBomb::Update()
{
	Projectile::Update();
	transform->position.x += _speedX * TIMEMANAGER->getElapsedTime();
	transform->position.y += _speedY * TIMEMANAGER->getElapsedTime();
	if (_speedY < 200)
		_speedY += _gravity * TIMEMANAGER->getElapsedTime();
	else
		_speedY = 200;
}

void PrivateBomb::OnTriggerEnter(GameObject* gameObject)
{
	Projectile::OnTriggerEnter(gameObject);
}

void PrivateBomb::Fire(int x, int y, bool dir)
{
	Projectile::Fire(x, y, dir);
	if (dir == false)
		_angle = PI / 4;
	else
		_angle = PI * 3 / 4;
	_speedX = _speed * cosf(_angle);
	_speedY = _speed * -sinf(_angle);
	_gravity = 100;
}
