#include "stdafx.h"
#include "IntroState.h"
#include "IdleState.h"
State* IntroState::InputHandle(RockMan* rockman)
{
    _introTime += TIMEMANAGER->getElapsedTime();
    if (_introTime >= 3.0f) {
        Exit(rockman);
        return new IdleState();
    }
    return nullptr;
}

void IntroState::Update(RockMan* rockman)
{
}

void IntroState::Enter(RockMan* rockman)
{
    rockman->attackable = false;
    rockman->ChangeClip("intro", false);
}

void IntroState::Exit(RockMan* rockman)
{
    rockman->attackable = true;
}

void IntroState::Attack(RockMan* rockman)
{
}
