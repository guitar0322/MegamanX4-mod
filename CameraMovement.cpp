#include "stdafx.h"
#include "CameraMovement.h"

void CameraMovement::Init(GameObject* rockman)
{
	_rockman = rockman;
	_isSinkhole = false;
	_isFloor = false;
	_recoverySpeed = 50;
	_isEscape = false;
	_isBoss = false;

}

void CameraMovement::Update()
{
	if (_rockman->transform->GetX() >= 7250 && _rockman->transform->GetX() <= 7880) {
		if (_rockman->transform->GetY() >= 460 && _isFloor == false && _isEscape == false) {
			_isSinkhole = true;
		}
		if (_rockman->transform->GetY() >= 1380 && _isSinkhole == true) {
			_isSinkhole = false;
			_isFloor = true;
		}
		if (_rockman->transform->GetX() >= 7800 && _isFloor == true) {
			_isFloor = false;
   			_isEscape = true;
		}
	}
	if (_rockman->transform->GetX() >= 9900) {
		_isBoss = true;
	}
	if (_isSinkhole == true) {
		if (_rockman->transform->GetY() >= 460) {
			SCENEMANAGER->GetCurScene()->mainCam->transform->SetPosition(_rockman->transform->GetX(), _rockman->transform->GetY() - 170);
		}
	}
	else if (_isFloor == true) {
		if (_rockman->transform->GetY() <= SCENEMANAGER->GetCurScene()->mainCam->transform->GetY()) {
       			SCENEMANAGER->GetCurScene()->mainCam->transform->SetPosition(_rockman->transform->GetX(), _rockman->transform->GetY());
		}
		else {
			SCENEMANAGER->GetCurScene()->mainCam->transform->SetPosition(
				_rockman->transform->GetX(), SCENEMANAGER->GetCurScene()->mainCam->transform->GetY());
		}
	}
	else if (_isEscape == true) {
		float nextY = SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() - _recoverySpeed * TIMEMANAGER->getElapsedTime();
		float text = SCENEMANAGER->GetCurScene()->mainCam->transform->GetY();
  		if (nextY <= WINSIZEY / 2) {
			nextY = WINSIZEY / 2;
			_isEscape = false;
		}
		SCENEMANAGER->GetCurScene()->mainCam->transform->SetPosition(_rockman->transform->GetX(), nextY);
	}
	else if(_isBoss == false){
		if (_rockman->transform->GetX() >= WINSIZEX / 2 && _rockman->transform->GetX() <= SCENEMANAGER->GetCurScene()->GetWidth() - WINSIZEX / 2) {
			SCENEMANAGER->GetCurScene()->mainCam->transform->SetPosition(
				_rockman->transform->GetX(), SCENEMANAGER->GetCurScene()->mainCam->transform->GetY());
		}
	}
}

void CameraMovement::Render()
{

}
