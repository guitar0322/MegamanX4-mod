#include "stdafx.h"
#include "MoveBehavior.h"

void MoveBehavior::Init(vector<GameObject*> targetObject, dirEnum dir, float speedY, float gravity, float maxSpeedY, vector<float> maxY, GameObject* rockman)
{
	this->targetObject = targetObject;
	_speed = speedY;
	if (_speed <= 1.0f) {
		_isSlow = true;
		_speed = 1.0f;
	}
	else
		_isSlow = false;
	_gravity = gravity;
	_maxSpeed = maxSpeedY;
	_maxPos = maxY;
	_dir = dir;
	_moveTerm = 0;
	_rockman = rockman;
	_isOn = false;
}

void MoveBehavior::Update()
{
	if (isEnd == true) return;
	if (_isSlow == true) {
		if (_moveTerm == 0) {
			_moveTerm++;
			return;
		}
		else
			_moveTerm = 0;
	}
	if (CheckEnd() == true)
		isEnd = true;
	for (int i = 0; i < targetObject.size(); i++) {
		if (targetObject[i]->isActive == false) {
			if (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->IsShake() == true)
				SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->ShakeOff();
			continue;
		}
		switch (_dir)
		{
		case DOWN:
			if (targetObject[i]->transform->GetY() <= _maxPos[i]) {
				if (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->IsShake() == false) {
					SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->Shake(5, 1);
				}
				CheckLack(targetObject[i]->transform->GetX(), targetObject[i]->transform->GetY() + _speed * TIMEMANAGER->getElapsedTime(), i);
				targetObject[i]->transform->MoveY(_speed * TIMEMANAGER->getElapsedTime());
				_speed += _gravity * TIMEMANAGER->getElapsedTime();
				if (_speed >= _maxSpeed) {
					_speed = _maxSpeed;
				}
			}
			else {
				SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->ShakeOff();
			}
			break;
		case UP:
			if (targetObject[i]->transform->GetY() >= _maxPos[i]) {
				if (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->IsShake() == false) {
					SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->Shake(5, 1);
				}
				CheckLack(targetObject[i]->transform->GetX(), targetObject[i]->transform->GetY() - _speed * TIMEMANAGER->getElapsedTime(), i);
				targetObject[i]->transform->MoveY(-_speed * TIMEMANAGER->getElapsedTime());
				_speed += _gravity * TIMEMANAGER->getElapsedTime();
				if (_speed >= _maxSpeed) {
					_speed = _maxSpeed;
				}
			}
			else {
				SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->ShakeOff();
			}
			break;
		case RIGHT:
			if (targetObject[i]->transform->GetX() <= _maxPos[i]) {
				if (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->IsShake() == false) {
					SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->Shake(5, 1);
				}
				CheckLack(targetObject[i]->transform->GetX() + _speed * TIMEMANAGER->getElapsedTime(), targetObject[i]->transform->GetY(), i);
				targetObject[i]->transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());
				_speed += _gravity * TIMEMANAGER->getElapsedTime();
				if (_speed >= _maxSpeed) {
					_speed = _maxSpeed;
				}
			}
			else {
				SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->ShakeOff();
			}
			break;
		case LEFT:
			if (targetObject[i]->transform->GetX() >= _maxPos[i]) {
				if (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->IsShake() == false) {
					SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->Shake(5, 1);
				}
				CheckLack(targetObject[i]->transform->GetX() - _speed * TIMEMANAGER->getElapsedTime(), targetObject[i]->transform->GetY(), i);
				targetObject[i]->transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime());
				_speed += _gravity * TIMEMANAGER->getElapsedTime();
				if (_speed >= _maxSpeed) {
					_speed = _maxSpeed;
				}
			}
			else {
				SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->ShakeOff();
			}
			break;
		}
	}
}

void MoveBehavior::CheckLack(int x, int y, int idx)
{
	RECT rockmanRc = _rockman->GetComponent<BoxCollider>()->rc;
	RECT tempRc = RectMakeCenter(x, y, targetObject[idx]->GetComponent<BoxCollider>()->width,
		targetObject[idx]->GetComponent<BoxCollider>()->height);
	RECT intersectRc;
	RECT colCheckRc;
	bool isLack = false;
	if (IntersectRect(&intersectRc, &rockmanRc, &tempRc) == true) {
		switch (_dir) {
		case UP:
			colCheckRc = RectMakeCenter(
				_rockman->transform->GetX(),
				_rockman->transform->GetY() - _rockman->GetComponent<BoxCollider>()->height / 2 - 2,
				_rockman->GetComponent<BoxCollider>()->width, 2);
			isLack = CheckCollision(colCheckRc);
			break;
		case DOWN:
			colCheckRc = RectMakeCenter(
				_rockman->transform->GetX(),
				_rockman->transform->GetY() + _rockman->GetComponent<BoxCollider>()->height / 2 + 2,
				_rockman->GetComponent<BoxCollider>()->width, 2);
			isLack = CheckCollision(colCheckRc);
			break;
		case RIGHT:
			colCheckRc = RectMakeCenter(
				_rockman->transform->GetX() + _rockman->GetComponent<BoxCollider>()->width / 2,
				_rockman->transform->GetY(),
				2, _rockman->GetComponent<BoxCollider>()->height);
			isLack = CheckCollision(colCheckRc);
			break;
		case LEFT:
			colCheckRc = RectMakeCenter(
				_rockman->transform->GetX() - _rockman->GetComponent<BoxCollider>()->width / 2,
				_rockman->transform->GetY(),
				2, _rockman->GetComponent<BoxCollider>()->height);
			isLack = CheckCollision(colCheckRc);
			break;
		}
	}
	if (isLack == true) {
		_rockman->GetComponent<ObjectInfo>()->Damage(100);
	}
}

bool MoveBehavior::CheckCollision(RECT rc)
{
	int colNum = COLLIDERMANAGER->colliderList.size();
	RECT intersectRc;
	RECT targetRc;
	for (int i = 0; i < colNum; i++) {
		if (COLLIDERMANAGER->colliderList[i]->gameObject->isActive == false) continue;
		if (_rockman->GetComponent<BoxCollider>() == COLLIDERMANAGER->colliderList[i]) continue;
		targetRc = COLLIDERMANAGER->colliderList[i]->rc;
		if (IntersectRect(&intersectRc, &rc, &targetRc) == true){
			string name = COLLIDERMANAGER->colliderList[i]->gameObject->name;
			return true;
		}
	}
	return false;
}

bool MoveBehavior::CheckEnd()
{
	for (int i = 0; i < targetObject.size(); i++) {
		switch (_dir) {
		case DOWN:
			if (targetObject[i]->transform->GetY() <= _maxPos[i]) {
				return false;
			}
			break;
		case UP:
			if (targetObject[i]->transform->GetY() >= _maxPos[i]) {
				return false;
			}
			break;
		case RIGHT:
			if (targetObject[i]->transform->GetX() <= _maxPos[i]) {
				return false;
			}
			break;
		case LEFT:
			if (targetObject[i]->transform->GetX() >= _maxPos[i]) {
				return false;
			}
			break;
		}
	}
	return true;
}

void MoveBehavior::Start()
{
	_isOn = true;
	SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->Shake(2, 1);
}
