#include "stdafx.h"
#include "ShadowManager.h"

void ShadowManager::Init(RockMan* rockman)
{
	_rockman = rockman;
	_onShadowTime = 0;
	_offShadowTime = 0;
	_isOffShadow = false;
	_isOnShadow = false;
}

void ShadowManager::Update()
{
	if (_isOnShadow == true) {
		_onShadowTime += TIMEMANAGER->getElapsedTime();
		if (_onShadowTime >= 0.17f) {
			_onShadowTime = 0;
			ActiveShadow();
			SetShadowPos();
		}
	}

	if (_isOffShadow == true) {
		_offShadowTime += TIMEMANAGER->getElapsedTime();
		if (_offShadowTime >= 1.0f) {
			_isOffShadow = false;
			_isOnShadow = false;
			UnActiveShadow();
		}
	}
}

void ShadowManager::Render()
{
}

void ShadowManager::ActiveShadow()
{
	for (int i = 0; i < 3; i++) {
		if (shadow[i]->gameObject->isActive == true) continue;
		shadow[i]->CopyRockman();
		if (i == 0) {
			shadow[i]->SetColor(RGB(143, 222, 255));
		}
		else if (i == 1) {
			shadow[i]->SetColor(RGB(115, 199, 255));
		}
		else {
			shadow[i]->SetColor(RGB(97, 124, 255));
		}
		shadow[i]->gameObject->SetActive(true);
		break;
	}
}

void ShadowManager::UnActiveShadow()
{
	for (int i = 0; i < 3; i++) {
		shadow[i]->gameObject->SetActive(false);
	}
}

void ShadowManager::OffShadow()
{
	_offShadowTime = 0;
	_isOffShadow = true;
}

void ShadowManager::OnShadow()
{
	_isOnShadow = true;
	_isOffShadow = false;
}

void ShadowManager::SetShadowPos()
{
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			shadow[i]->SetNextPos({ _rockman->transform->GetX(), _rockman->transform->GetY() });
		}
		else if (i == 1) {
			shadow[i]->SetNextPos({ shadow[0]->transform->GetX(), shadow[0]->transform->GetY() });
		}
		else {
			shadow[i]->SetNextPos({ shadow[1]->transform->GetX(), shadow[1]->transform->GetY() });
		}
	}
}
