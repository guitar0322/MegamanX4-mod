#include "stdafx.h"
#include "Effect.h"

void Effect::Init()
{
	animator = gameObject->GetComponent<Animator>();
	isEnd = true;
}

void Effect::Init(float unActiveTime)
{
	isEnd = true;
	animator = gameObject->GetComponent<Animator>();
	this->unActiveTime = unActiveTime;
}

void Effect::Update()
{
	if (isEnd == true) {
		activeTime += TIMEMANAGER->getElapsedTime();
		if (activeTime >= unActiveTime) {
			activeTime = 0;
			isEnd = false;
			gameObject->SetActive(false);
		}
	}
}

void Effect::Render()
{
}

void Effect::Emission(bool dir)
{
	gameObject->SetActive(true);
	if (animator->GetClip("idle_right") == nullptr) {
		isEnd = true;
	}
	if (dir == false){
		animator->SetClip(animator->GetClip("start_right"));
	}
	else {
		animator->SetClip(animator->GetClip("start_left"));
	}
}

void Effect::End(bool dir)
{
	isEnd = true;
	if (dir == false) {
		animator->SetClip(animator->GetClip("end_right"));
	}
	else {
		animator->SetClip(animator->GetClip("end_left"));
	}
}
