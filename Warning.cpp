#include "stdafx.h"
#include "Warning.h"

void Warning::Init()
{
	char warningFileName[32];
	int startX = 9900 - (19 * 14) - 19 / 2;
	for (int i = 0; i < 30; i++) {
		sprintf_s(warningFileName, "ui/warning%d.bmp", i + 1);
		_warning[i].transform->SetPosition(startX + i * 19, 150);
		_warning[i].renderer->Init(warningFileName, 19, 141);
		_warning[i].SetActive(false);
	}
	_renderTerm = 0;
	_idx = 0;
	_alpha = 255;
	_deltaAlpha = 7;
	_num = 0;
}

void Warning::Update()
{
	_renderTerm += TIMEMANAGER->getElapsedTime();
	if (_renderTerm >= 0.11f) {
		if (_idx != 30) {
			_renderTerm = 0;
			_warning[_idx++].SetActive(true);
		}
	}
	if (_idx == 30) {
		if (_renderTerm >= 0.03f) {
			for (int i = 0; i < 30; i++) {
				_warning[i].renderer->SetAlpha(_alpha);
			}
			_alpha -= _deltaAlpha;
			if (_alpha <= 0) {
				_num++;
				_alpha = 0;
				_deltaAlpha *= -1;
			}
			else if (_alpha >= 255) {
				_alpha = 255;
				_deltaAlpha *= -1;
			}
			if (_num == 5) {
				gameObject->SetActive(false);
				colonel->SetActive(true);
			}
			_renderTerm = 0;
		}
	}
}

void Warning::Render()
{
	for (int i = 0; i < 30; i++) {
		_warning[i].Render();
	}
}
