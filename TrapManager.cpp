#include "stdafx.h"
#include "TrapManager.h"

void TrapManager::Init(RockMan* rockman)
{
	_rockman = rockman;
	_trapV.push_back({ 995, {0}});
	_trapV.push_back({ 1250, {1} });
	_trapV.push_back({ 1660, {2} });
}

void TrapManager::Update()
{
	for (int i = 0; i < _trapV.size(); i++) {
		if (_rockman->transform->GetX() >= _trapV[i].x) {
			for (int j = 0; j < _trapV[i].targetObjectIdx.size(); j++) {
				int objIdx = _trapV[i].targetObjectIdx[j];
				if(_targetObjectV[objIdx]->isActive == true &&
					_targetObjectV[objIdx]->GetComponent<TrapBehavior>()->isOn == false &&
					_targetObjectV[objIdx]->GetComponent<TrapBehavior>()->isEnd == false)
					_targetObjectV[objIdx]->GetComponent<TrapBehavior>()->TrapOn();
			}
		}
	}
}

void TrapManager::Render()
{
}

void TrapManager::AddObject(GameObject* targetObject)
{
	_targetObjectV.push_back(targetObject);
}
