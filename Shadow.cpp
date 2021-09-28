#include "stdafx.h"
#include "Shadow.h"

void Shadow::Init(Renderer* rockmanRenderer)
{
	renderer = gameObject->GetComponent<Renderer>();
	this->rockmanRenderer = rockmanRenderer;
	renderer->SetAlpha(125);
	_active = false;
}

void Shadow::Update()
{
	renderer->Resize(rockmanRenderer->width, rockmanRenderer->height);
	HBRUSH blueBrush, oBrush;
	blueBrush = CreateSolidBrush(_shadowColor);
	oBrush = (HBRUSH)SelectObject(renderer->memDC, blueBrush);
	PatBlt(renderer->memDC, 0, 0, renderer->width, renderer->height, PATCOPY);
	SelectObject(renderer->memDC, oBrush);
	DeleteObject(blueBrush);
	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = 5;
	AlphaBlend(renderer->memDC, 0, 0, renderer->width, renderer->height,
		rockmanRenderer->memDC, 0, 0, rockmanRenderer->width, rockmanRenderer->height, blendFunc);
	COLORREF transColor = GetPixel(renderer->memDC, 0, 0);
	renderer->SetTransColor(transColor);
	_activeTime += TIMEMANAGER->getElapsedTime();

	this->transform->SetPosition(_nextPos.first, _nextPos.second);
	//if (_activeTime > 1.0f) {
	//	_activeTime = 0;
	//	gameObject->SetActive(false);
	//	_active = false;
	//}

}
void Shadow::Render()
{

}

void Shadow::CopyRockman()
{
	_active = true;
	transform->SetPosition(rockmanRenderer->transform->GetX(), rockmanRenderer->transform->GetY());
	renderer->Resize(rockmanRenderer->width, rockmanRenderer->height);
	HBRUSH blueBrush, oBrush;
	blueBrush = CreateSolidBrush(_shadowColor);
	oBrush = (HBRUSH)SelectObject(renderer->memDC, blueBrush);
	PatBlt(renderer->memDC, 0, 0, renderer->width, renderer->height, PATCOPY);
	SelectObject(renderer->memDC, oBrush);
	DeleteObject(blueBrush);
	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = 5;
	AlphaBlend(renderer->memDC, 0, 0, renderer->width, renderer->height,
		rockmanRenderer->memDC, 0, 0, rockmanRenderer->width, rockmanRenderer->height, blendFunc);
	COLORREF transColor = GetPixel(renderer->memDC, 0, 0);
	renderer->SetTransColor(transColor);
	//그림자 사라지는 조건
	//대시가 끝나고 일정시간 이후에 일괄 사라짐
}
