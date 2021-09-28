#include "stdafx.h"

Component::Component()
{
}

Component::Component(GameObject* gameObject)
{
	this->gameObject = gameObject;
	transform = gameObject->transform;
}

Component::~Component()
{
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::Render()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::OnCollision(GameObject* gameObject)
{
}

void Component::OnTriggerEnter(GameObject* gameObject)
{
}

void Component::OnTriggerStay(GameObject* gameObject)
{
}

void Component::OnTriggerExit(GameObject* gameObject)
{
}

