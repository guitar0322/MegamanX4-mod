#include "stdafx.h"
#include "ProjectileObj.h"

void ProjectileObj::Init()
{
	renderer = new Renderer();
	AddComponent(renderer);
	animator = new Animator();
	AddComponent(animator);
	collider = new BoxCollider();
	AddComponent(collider);

	renderer->Init();
	animator->Init();
	collider->Init();
}

void ProjectileObj::Update()
{
	GameObject::Update();
}

void ProjectileObj::Render()
{
	GameObject::Render();
}

void ProjectileObj::SetProjectileComponent(Projectile* projectileComponent)
{
	this->projectileComponent = projectileComponent;
}
