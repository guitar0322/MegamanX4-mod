#include "stdafx.h"
#include "Overlap.h"

void Overlap::Init()
{
	HDC hdc = GetDC(_hWnd);
	_renderer = gameObject->GetComponent<Renderer>();
	_overlapDC = CreateCompatibleDC(hdc);
	_bitmap = CreateCompatibleBitmap(hdc, _renderer->width, _renderer->height);
	_preWidth = _renderer->width;
	_preHeight = _renderer->height;
	_overlapBrush = CreateSolidBrush(_overlapColor);
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.SourceConstantAlpha = 200;
	_alpha = 200;
}

void Overlap::Update()
{
	if (_preWidth != _renderer->width || _preHeight != _renderer->height) {
		HDC hdc = GetDC(_hWnd);
		_bitmap = CreateCompatibleBitmap(hdc, _renderer->width, _renderer->height);
		SelectObject(_overlapDC, _bitmap);
		_preWidth = _renderer->width;
		_preHeight = _renderer->height;
	}
	_overlapBrush = CreateSolidBrush(_overlapColor);
	SelectObject(_overlapDC, _overlapBrush);
	PatBlt(_overlapDC, 0, 0, _preWidth, _preHeight, PATCOPY);
	AlphaBlend(_overlapDC, 0, 0, _preWidth, _preHeight, _renderer->memDC, 0, 0, _preWidth, _preHeight, _blendFunc);
	_transColor = GetPixel(_overlapDC, 0, 0);
}

void Overlap::Render()
{
	int startX = transform->GetX() - _preWidth / 2;
	int startY = transform->GetY() - _preHeight / 2;
	GdiTransparentBlt(_backBuffer->getMemDC(), startX, startY, _preWidth, _preHeight,
		_overlapDC, 0, 0, _preWidth, _preHeight, _transColor);
}
