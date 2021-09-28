#include "stdafx.h"
#include "TrapBehavior.h"

void TrapBehavior::Init(GameObject* rockman, int activeX, int activeY)
{
	_rockman = rockman;
	_activeX = activeX;
	_activeY = activeY;
	isOn = false;
	isEnd = false;
}

void TrapBehavior::Update()
{
	if (_rockman->transform->GetX() >= _activeX && _rockman->transform->GetY() >= _activeY) {
		if(isOn == false && isEnd == false)
			TrapOn();
	}
	if (isOn == true) {
		for (int i = 0; i < _startMoveBehavior.size(); i++) {
			_startMoveBehavior[i].Update();
		}
		for (int i = 0; i < _startEffectBehavior.size(); i++) {
			_startEffectBehavior[i].Emission();
		}
		for (int i = 0; i < _startSpawnBehavior.size(); i++) {
			_startSpawnBehavior[i].Spawn();
		}
		if (CheckEnd())
			TrapEnd();
	}

	if (isEnd == true) {
		for (int i = 0; i < _endMoveBehavior.size(); i++) {
			_endMoveBehavior[i].Update();
		}
		for (int i = 0; i < _endEffectBehavior.size(); i++) {
			_endEffectBehavior[i].Emission();
		}
		for (int i = 0; i < _endSpawnBehavior.size(); i++) {
			_endSpawnBehavior[i].Spawn();
		}
	}
}

void TrapBehavior::Render()
{
}

void TrapBehavior::OnTriggerEnter(GameObject* gameObject)
{
}

void TrapBehavior::OnCollision(GameObject* gameObject)
{
}

void TrapBehavior::AddMoveBehavior(bool flag, vector<GameObject*> targetObject, MoveBehavior::dirEnum _dir, float speedY, float gravity, float maxSpeedY, vector<float> maxY)
{
	MoveBehavior newHavior;
	newHavior.Init(targetObject, _dir, speedY, gravity, maxSpeedY, maxY, _rockman);
	if (flag == true) {
		_startMoveBehavior.push_back(newHavior);
	}
	else {
		_endMoveBehavior.push_back(newHavior);
	}
}

void TrapBehavior::AddEffectBehavior(bool flag, string effectName, int effectNum, pair<int, int> rangeX, pair<int,int> rangeY)
{
	EffectBehavior newHavior;
	newHavior.Init(effectName, effectNum, rangeX, rangeY);
	if (flag == true) {
		_startEffectBehavior.push_back(newHavior);
	}
	else {
		_endEffectBehavior.push_back(newHavior);
	}
}

void TrapBehavior::AddSpawnBehavior(bool flag, vector<bool> spawnFlag, vector<GameObject*> targetObject)
{
	SpawnBehavior newHavior;
	newHavior.Init(spawnFlag, targetObject);
	if (flag == true) {
		_startSpawnBehavior.push_back(newHavior);
	}
	else {
		_endSpawnBehavior.push_back(newHavior);
	}
}

void TrapBehavior::TrapOn()
{
	for (int i = 0; i < _startMoveBehavior.size(); i++) {
		_startMoveBehavior[i].Start();
	}
	isOn = true;
}

void TrapBehavior::TrapEnd()
{
	isOn = false;
	isEnd = true;
}

bool TrapBehavior::CheckEnd()
{
	for (int i = 0; i < _startMoveBehavior.size(); i++) {
		if (_startMoveBehavior[i].isEnd == false)
			return false;
	}
	return true;
}
