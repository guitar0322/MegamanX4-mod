#include "stdafx.h"
#include "Soldier.h"
#include "SoldierIdle.h"
void Soldier::Init(GameObject* rockman, bool dir)
{
    this->rockman = rockman;
    this->dir = dir;
    animator = gameObject->GetComponent<Animator>();
	ClipInit();
	_state = new SoldierIdle();
	_state->Enter(this);
}

void Soldier::Update()
{
    SoldierState* newState = _state->Update(this);
    if (newState != nullptr) {
        SAFE_DELETE(_state);
        _state = newState;
        _state->Enter(this);
    }
    if (rockman->transform->GetX() > this->transform->GetX())
        dir = false;
    else
        dir = true;
}

void Soldier::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == true) {
        animator->SetClip(animator->GetClip(clipName), isInitFrame);
	}
	else {
        animator->SetClip(animator->GetClip(clipName));
	}
}

void Soldier::ClipInit()
{
    _idleRight = new AnimationClip();
    _idleLeft = new AnimationClip();
    _attackRight = new AnimationClip();
    _attackLeft = new AnimationClip();
    _throwRight = new AnimationClip();
    _throwLeft = new AnimationClip();

    _idleRight->Init("private/private_idle_right.bmp", 644, 110, 7, 0.30);
    _idleLeft->Init("private/private_idle_left.bmp", 644, 110, 7, 0.30);
    _attackRight->Init("private/private_attack_right.bmp", 240, 98, 2, 0.30f);
    _attackLeft->Init("private/private_attack_left.bmp", 240, 98, 2, 0.30);
    _throwRight->Init("private/private_throw_right.bmp", 936, 124, 6, 0.20);
    _throwRight->isLoop = false;
    _throwLeft->Init("private/private_throw_left.bmp", 936, 124, 6, 0.20);
    _throwLeft->isLoop = false;

    animator->AddClip("throw_right", _throwRight);
    animator->AddClip("throw_left", _throwLeft);
    animator->AddClip("idle_right", _idleRight);
    animator->AddClip("idle_left", _idleLeft);
    animator->AddClip("attack_right", _attackRight);
    animator->AddClip("attack_left", _attackLeft);

    if (dir == false) {
        animator->SetClip(_idleRight);
    }
    else {
        animator->SetClip(_idleLeft);
    }
}

void Soldier::OnTriggerEnter(GameObject* gameObject)
{
    if (gameObject->tag == TAGMANAGER->GetTag("player")) {
        gameObject->GetComponent<ObjectInfo>()->Damage(10);
    }
}
