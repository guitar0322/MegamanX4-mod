#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->width = width;
	this->height = height;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = alpha;
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
	transColor = RGB(255, 0, 255);
}

void Renderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	width = transform->GetWidth();
	height = transform->GetHeight();
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	SelectObject(alphaMemDC, hBit);
	alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = alpha;
	rc = RectMakeCenter(this->transform->GetX(), transform->GetY(),
		width, height);
	ReleaseDC(_hWnd, hdc);
	transColor = RGB(255, 0, 255);
}

void Renderer::Render()
{
	string name = gameObject->name;
	BitBlt(alphaMemDC, 0, 0, width, height, _backBuffer->getMemDC(), rc.left, rc.top, SRCCOPY);
	GdiTransparentBlt(
		alphaMemDC,					//복사될 영역의 DC
		0,				//복사될 좌표(left)
		0,					//복사될 좌표(top)
		width,					//복사될 크기 (가로크기)
		height,					//복사될 크기 (세로크기)
		memDC,					//복사해올 DC 
		0, 0,					//복사해올 시작좌표(left, top)
		width,					//복사해올 가로크기
		height,					//복사해올 세로크기
		transColor		//복사할때 제외할 픽셀값
	);
	AlphaBlend(
		_backBuffer->getMemDC(),					//복사될 영역의 DC
		rc.left,				//복사될 좌표(left)
		rc.top,					//복사될 좌표(top)
		width,					//복사될 크기 (가로크기)
		height,					//복사될 크기 (세로크기)
		alphaMemDC,					//복사해올 DC 
		0, 0,					//복사해올 시작좌표(left, top)
		width,					//복사해올 가로크기
		height,					//복사해올 세로크기
		blendFunc		//복사할때 제외할 픽셀값
	);
}


void Renderer::Update()
{
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::OnEnable()
{
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::Resize(int newWidth, int newHeight)
{
	if (width == newWidth && height == newHeight)
		return;
	HDC hdc = GetDC(_hWnd);
	HDC temp;

	HBITMAP scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, scaleBitmap);

	scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(alphaMemDC, scaleBitmap);

	ReleaseDC(_hWnd, hdc);
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		newWidth,
		newHeight);

	DeleteObject(scaleBitmap);
	width = newWidth;
	height = newHeight;
}


