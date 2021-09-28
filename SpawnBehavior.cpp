#include "stdafx.h"
#include "SpawnBehavior.h"

void SpawnBehavior::Init(vector<bool> spawnFlag, vector<GameObject*> targetObject)
{
	_targetObject = targetObject;
	_spawnFlag = spawnFlag;
}

void SpawnBehavior::Spawn()
{
	for (int i = 0; i < _spawnFlag.size(); i++) {
		if (_spawnFlag[i] == true) {
			if (_targetObject[i]->isActive == false) {
				_targetObject[i]->SetActive(true);
				isEnd = true;
			}
		}
		else {
			if (_targetObject[i]->isActive == true) {
				_targetObject[i]->SetActive(false);
				isEnd = true;
			}
		}
	}
}
