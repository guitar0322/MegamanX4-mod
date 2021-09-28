#include "stdafx.h"
#include "BackgroundControl.h"

void BackgroundControl::Init(GameObject* rockman)
{
	_rockman = rockman;
}

void BackgroundControl::Update()
{
	_rockmanX = _rockman->transform->GetX();
	_rockmanY = _rockman->transform->GetY();
	for (int i = 0; i < 16; i++) {
		if (_rockmanX >= 640 * i - 360 && _rockmanX <= 640 * (i + 1) + 360) {
			if (background[i]->isActive == false)
				background[i]->SetActive(true);
		}
		else if (background[i]->isActive == true)
			background[i]->SetActive(false);
	}

	if (_rockmanX >= 7736 - 320 && _rockmanX <= 7736 + 1540 + 320) {
		if (holeBackground->isActive == false)
			holeBackground->SetActive(true);
	}
	else if (holeBackground->isActive == true)
		holeBackground->SetActive(false);
}

void BackgroundControl::Render()
{
}
