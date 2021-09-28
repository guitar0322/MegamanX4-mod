#include "stdafx.h"
#include "HPBar.h"

void HPBar::Init(int maxHeight, ObjectInfo* targetInfo)
{
	_targetInfo = targetInfo;
	_maxHeight = _curHeight = _backCurHeight = maxHeight;
	_hp = RectMakeCenter(transform->GetX() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() - 11,
		transform->GetY() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() - 13,
		11, _curHeight);
	_redHP = RectMakeCenter(transform->GetX() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() - 11,
		transform->GetY() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() - 13,
		11, _backCurHeight);
	gBrush = CreateSolidBrush(RGB(8, 211, 66));
	yBrush = CreateSolidBrush(RGB(250, 230, 95));
	rBrush = CreateSolidBrush(RGB(255, 20, 0));
	nullPen= CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	_isDamaged = false;
	_deltaReduce = 1;
	_healStack = 0;
	_isHeal = false;
}

void HPBar::Update()
{
	if (_isHeal == true) {
		_healStack++;
		if(_targetInfo->GetCurHP() < _targetInfo->GetMaxHP())
			_targetInfo->SetCurHP(_targetInfo->GetCurHP() + _deltaHeal);
		if (_healStack == _healAmount) {
			_healStack = 0;
			_isHeal = false;
			_backCurHeight = _curHeight;
		}
	}
	_curHeight = _targetInfo->GetCurHP() * _maxHeight / _targetInfo->GetMaxHP();
	if (_curHeight != _backCurHeight) {
		_isDamaged = true;
	}
	if (_isDamaged == true) {
		_delay += TIMEMANAGER->getElapsedTime();
		if (_delay >= 1.5f) {
			if (_backCurHeight > _curHeight)
				_backCurHeight -= _deltaReduce;
			else {
				_isDamaged = false;
				_backCurHeight = _curHeight;
				_delay = 0;
			}
		}
	}
	_hp = RectMakeCenter(transform->GetX() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() - _deltaX,
		transform->GetY() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() - _deltaY + (_maxHeight - _curHeight) / 2,
		12, _curHeight);
	_redHP = RectMakeCenter(transform->GetX() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() - _deltaX,
		transform->GetY() + SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() - _deltaY + (_maxHeight - _backCurHeight) / 2,
		12, _backCurHeight);
}

void HPBar::Render()
{
	oBrush = (HBRUSH)SelectObject(_backBuffer->getMemDC(), rBrush);
	oPen = (HPEN)SelectObject(_backBuffer->getMemDC(), nullPen);
	Rectangle(_backBuffer->getMemDC(), _redHP);
	SelectObject(_backBuffer->getMemDC(), gBrush);
	Rectangle(_backBuffer->getMemDC(), _hp);
	SelectObject(_backBuffer->getMemDC(), oBrush);
	SelectObject(_backBuffer->getMemDC(), oPen);
}

void HPBar::Heal(int healAmount, int deltaHeal)
{
	_healStack = 0;
	_deltaHeal = deltaHeal;
	_healAmount = healAmount;
	_isHeal = true;
}


