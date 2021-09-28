#include "stdafx.h"
#include "HitState.h"
#include "IdleState.h"
State* HitState::InputHandle(RockMan* rockman)
{
    if (_isIdle == true) {
        Exit(rockman);
        return new IdleState();
    }
    return nullptr;
}

void HitState::Update(RockMan* rockman)
{
    _hitTime += TIMEMANAGER->getElapsedTime();
    if (rockman->dir == false) {
        rockman->transform->MoveX(-_knockbackSpeed * TIMEMANAGER->getElapsedTime());
    }
    else {
        rockman->transform->MoveX(_knockbackSpeed * TIMEMANAGER->getElapsedTime());
    }
    _knockbackSpeed -= _friction * TIMEMANAGER->getElapsedTime();
    if (rockman->controler->CheckGround() == false && rockman->controler->CheckSlope() == false) {
        rockman->transform->MoveY(_fallSpeed * TIMEMANAGER->getElapsedTime());
    }
    if (_knockbackSpeed < 0)
        _knockbackSpeed = 0;
    if (_hitTime >= 1.0f) {
        if(rockman->isDead == false)
            _isIdle = true;
    }
}

void HitState::Enter(RockMan* rockman)
{
    rockman->attackable = false;
    rockman->collider->SetSize(74, 90);
    _isIdle = false;
    _hitTime = 0;
    _knockbackSpeed = 150.0f;
    _friction = 150.0f;
    _fallSpeed = 100.0f;
    if (rockman->dir == false) {
        rockman->ChangeClip("small_hit_right", false);
    }
    else {
        rockman->ChangeClip("small_hit_left", false);
    }
}

void HitState::Exit(RockMan* rockman)
{
    rockman->attackable = true;
}

void HitState::Attack(RockMan* rockman)
{
}
