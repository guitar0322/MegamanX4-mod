#include "stdafx.h"
#include "DeathBubble.h"

void DeathBubble::Init()
{
	_bubbleClip.Init("effect/death_bubble.bmp", 244, 61, 4, 0.12f);
	_speed = 50;
}

void DeathBubble::Update()
{
	_emissionTerm += TIMEMANAGER->getElapsedTime();
	if (fadeOut->alpha <= 253) {
		fadeOut->SetAlpha(fadeOut->alpha + 2);
	}
	else {
		SCENEMANAGER->GetCurScene()->Init();
	}
	if (_emissionTerm > 0.5f) {
		Emission();
		_emissionTerm = 0;
	}

	for (int i = 0; i < 96; i++) {
		if (_bubble[i].isActive == false) continue;
		_bubble[i].x += _speed * cosf(_bubble[i].angle) * TIMEMANAGER->getElapsedTime();
		_bubble[i].y += _speed * -sinf(_bubble[i].angle) * TIMEMANAGER->getElapsedTime();
		_bubble[i].frameTime += TIMEMANAGER->getElapsedTime();
		if (_bubble[i].frameTime >= 0.12f) {
			_bubble[i].frameTime = 0;
			_bubble[i].curFrame++;
			if (_bubble[i].curFrame == _bubbleClip.frameNum) {
				_bubble[i].curFrame = 0;
			}
		}
	}
}

void DeathBubble::Render()
{
	for (int i = 0; i < 96; i++) {
		if (_bubble[i].isActive == false) continue;
		GdiTransparentBlt(_backBuffer->getMemDC(),
			_bubble[i].x - _bubbleClip.frameWidth / 2, _bubble[i].y - _bubbleClip.frameHeight / 2,
			_bubbleClip.frameWidth, _bubbleClip.frameHeight,
			_bubbleClip.wholeDC,
			_bubbleClip.frameWidth * _bubble[i].curFrame, 0,
			_bubbleClip.frameWidth, _bubbleClip.frameHeight,
			RGB(255, 0, 255));
	}
}

void DeathBubble::Emission()
{
	int emissionNum = 0;
	for (int i = 0; i < 96; i++) {
		if (_bubble[i].isActive == true) continue;
		_bubble[i].x = transform->GetX();
		_bubble[i].y = transform->GetY();
		_bubble[i].angle = PI * 2 * i / 8;
		_bubble[i].frameTime = 0;
		_bubble[i].curFrame = 0;
		_bubble[i].isActive = true;
		emissionNum++;
		if (emissionNum == 8)
			break;
	}
}
