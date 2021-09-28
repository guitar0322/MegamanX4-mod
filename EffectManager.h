#pragma once
#include "GameObject.h"
#define EFFECT_MAX 15
class EffectManager :
    public Component
{
private:
    typedef struct tagEffectInfo {
        int x, y;
        int curFrame;
        int maxFrame;
        float frameTerm;
        float time;
        bool active;
    }EFFECTINFO;
public:
    static EffectManager* instance;
    map<string, AnimationClip> effectMap;
    map<string, AnimationClip>::iterator effectMapIter;
    map<string, vector<EFFECTINFO>> effectInfoMap;
    map<string, vector<EFFECTINFO>>::iterator effectInfoMapIter;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    void AddEffect(string effectName, AnimationClip newEffect);
    void EmissionEffect(string effectName, int x, int y);
    static EffectManager* getInstance();
};

