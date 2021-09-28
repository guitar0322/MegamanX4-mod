#pragma once
#include "Behavior.h"
class EffectBehavior :
    public Behavior
{
private:
    string _effectName;
    int _emissionNum;
    pair<int, int> _rangeX;
    pair<int, int> _rangeY;
public:
    virtual void Init(string effectName, int emissionNum, pair<int,int> rangeX, pair<int,int> rangeY);
    virtual void Update();
    virtual void Emission();
};

