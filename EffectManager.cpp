#include "stdafx.h"
#include "EffectManager.h"

void EffectManager::Init()
{
}

void EffectManager::Update()
{
	for (effectMapIter = effectMap.begin(); effectMapIter != effectMap.end(); effectMapIter++) {
		string effectName = effectMapIter->first;
		effectInfoMapIter = effectInfoMap.find(effectName);
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effectInfoMapIter->second[i].active == false) continue;
			effectInfoMapIter->second[i].time += TIMEMANAGER->getElapsedTime();
			if (effectInfoMapIter->second[i].time >= effectInfoMapIter->second[i].frameTerm) {
				effectInfoMapIter->second[i].time = 0;
				effectInfoMapIter->second[i].curFrame++;
				if (effectInfoMapIter->second[i].curFrame == effectInfoMapIter->second[i].maxFrame) {
					effectInfoMapIter->second[i].active = false;
				}
			}
		}
	}
}

void EffectManager::Render()
{
	for (effectMapIter = effectMap.begin(); effectMapIter != effectMap.end(); effectMapIter++) {
		string effectName = effectMapIter->first;
		AnimationClip curEffect = effectMapIter->second;
		effectInfoMapIter = effectInfoMap.find(effectName);
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effectInfoMapIter->second[i].active == false) continue;
			GdiTransparentBlt(_backBuffer->getMemDC(),
				effectInfoMapIter->second[i].x, effectInfoMapIter->second[i].y,
				curEffect.frameWidth, curEffect.frameHeight,
				curEffect.wholeDC,
				effectInfoMapIter->second[i].curFrame * curEffect.frameWidth, 0,
				curEffect.frameWidth, curEffect.frameHeight,
				RGB(255, 0, 255));
		}
	}
}

void EffectManager::AddEffect(string effectName, AnimationClip newEffect)
{
	effectMap.insert(pair<string, AnimationClip>(effectName, newEffect));
	vector<EFFECTINFO> newVector;
	for (int i = 0; i < EFFECT_MAX; i++) {
		newVector.push_back(EFFECTINFO());
		newVector[i].active = false;
		newVector[i].curFrame = 0;
		newVector[i].maxFrame = newEffect.frameNum;
		newVector[i].frameTerm = newEffect.frameTerm;
		newVector[i].time = 0;
	}
	effectInfoMap.insert(pair<string, vector<EFFECTINFO>>(effectName, newVector));
}

void EffectManager::EmissionEffect(string effectName, int x, int y)
{
	effectInfoMapIter = effectInfoMap.find(effectName);
	AnimationClip targetEffect = effectMap.find(effectName)->second;
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effectInfoMapIter->second[i].active == true) continue;

		effectInfoMapIter->second[i].time = 0;
		effectInfoMapIter->second[i].active = true;
		effectInfoMapIter->second[i].x = x - targetEffect.frameWidth / 2;
		effectInfoMapIter->second[i].y = y - targetEffect.frameHeight / 2;
		effectInfoMapIter->second[i].curFrame = 0;
		break;
	}

}

EffectManager* EffectManager::instance = 0;

EffectManager* EffectManager::getInstance()
{
	if (instance == nullptr) {
		instance = new EffectManager();
	}
	return instance;
}
