#include "stdafx.h"
#include "ChargeOverlap.h"

void ChargeOverlap::Init(Renderer* rockmanRenderer, COLORREF color)
{
	_renderer = gameObject->GetComponent<Renderer>();
	_renderer->SetAlpha(180);
	_overlapColor = color;
	this->_targetRenderer = rockmanRenderer;
	_switchTotalTime = 0;
	_switchTime = 0.10f;
	_switchFlag = false;
	blueBrush = CreateSolidBrush(_overlapColor);
	oBrush = (HBRUSH)SelectObject(_renderer->memDC, blueBrush);
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = 5;
}

void ChargeOverlap::Update()
{
	if (_switchFlag == false) {
		transform->SetPosition(_targetRenderer->transform->GetX(), _targetRenderer->transform->GetY());
		_renderer->Resize(_targetRenderer->width, _targetRenderer->height);
		PatBlt(_renderer->memDC, 0, 0, _renderer->width, _renderer->height, PATCOPY);
		AlphaBlend(_renderer->memDC, 0, 0, _renderer->width, _renderer->height,
			_targetRenderer->memDC, 0, 0, _targetRenderer->width, _targetRenderer->height, blendFunc);
		_transColor = GetPixel(_renderer->memDC, 0, 0);
		_renderer->SetTransColor(_transColor);
	}
	else {
		transform->SetPosition(_targetRenderer->transform->GetX(), _targetRenderer->transform->GetY());
		_renderer->Resize(_targetRenderer->width, _targetRenderer->height);
		FillTransparent();
	}
	_switchTotalTime += TIMEMANAGER->getElapsedTime();
	if (_switchTotalTime >= _switchTime) {
		_switchFlag = !_switchFlag;
		_switchTotalTime = 0;
	}
}

void ChargeOverlap::Render()
{
}

void ChargeOverlap::FillTransparent()
{
	HBRUSH blueBrush, oBrush;
	blueBrush = CreateSolidBrush(_transColor);
	oBrush = (HBRUSH)SelectObject(_renderer->memDC, blueBrush);
	PatBlt(_renderer->memDC, 0, 0, _renderer->width, _renderer->height, PATCOPY);
	SelectObject(_renderer->memDC, oBrush);
	DeleteObject(blueBrush);
}

