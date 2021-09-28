#include "stdafx.h"
#include "EffectBehavior.h"

void EffectBehavior::Init(string effectName, int emissionNum, pair<int, int> rangeX, pair<int, int> rangeY)
{
	_effectName = effectName;
	_emissionNum = emissionNum;
	_rangeX = rangeX;
	_rangeY = rangeY;
}

void EffectBehavior::Update()
{
}

void EffectBehavior::Emission()
{
	if (isEnd == true) return;
	int distanceX = (_rangeX.second - _rangeX.first) / _emissionNum;
	for (int i = 0; i < _emissionNum; i++) {
		EffectManager::getInstance()->EmissionEffect(_effectName, _rangeX.first + distanceX * i, RND->getFromIntTo(_rangeY.first, _rangeY.second));
	}
	isEnd = true;
}
