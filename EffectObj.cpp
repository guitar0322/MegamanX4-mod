#include "stdafx.h"
#include "EffectObj.h"

void EffectObj::Init()
{
	renderer = new Renderer();
	AddComponent(renderer);
	animator = new Animator();
	AddComponent(animator);
	effect = new Effect();
	AddComponent(effect);

	renderer->Init();
	animator->Init();
	effect->Init();

	isActive = false;
}

void EffectObj::Init(float duration)
{
	renderer = new Renderer();
	AddComponent(renderer);
	animator = new Animator();
	AddComponent(animator);
	effect = new Effect();
	AddComponent(effect);

	renderer->Init();
	animator->Init();
	effect->Init(duration);

	isActive = false;
}

void EffectObj::Update()
{
	GameObject::Update();
}

void EffectObj::Render()
{
	GameObject::Render();
}

void EffectObj::AddClip(const char* clipFileName, int clipWidth, int clipHeight, int clipFrameNum, float clipFrameTerm, MODE mode, bool dir)
{
	AnimationClip* newClip = new AnimationClip();
	newClip->Init(clipFileName, clipWidth, clipHeight, clipFrameNum, clipFrameTerm);
	switch (mode) {
	case START:
		newClip->isLoop = false;
		if (dir == false) {
			animator->AddClip("start_right", newClip);
		}
		else {
			animator->AddClip("start_left", newClip);
		}
		break;
	case IDLE:
		if (dir == false) {
			animator->AddClip("idle_right", newClip);
			animator->AddTransaction("start_idle_right", animator->GetClip("start_right"), newClip);
		}
		else {
			animator->AddClip("idle_left", newClip);
			animator->AddTransaction("start_idle_left", animator->GetClip("start_left"), newClip);
		}
		effect->isEnd = false;
		break;
	case END:
		newClip->isLoop = false;
		if (dir == false) {
			animator->AddClip("end_right", newClip);
		}
		else {
			animator->AddClip("end_left", newClip);
		}
		break;
	}
}
