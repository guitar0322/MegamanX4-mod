#pragma once
#include "GameObject.h"
#include "MoveBehavior.h"
#include "EffectBehavior.h"
#include "SpawnBehavior.h"
class TrapBehavior :
    public Component
{
private:
    vector<MoveBehavior> _startMoveBehavior;
    vector<MoveBehavior> _endMoveBehavior;
    vector<EffectBehavior> _startEffectBehavior;
    vector<EffectBehavior> _endEffectBehavior;
    vector<SpawnBehavior> _startSpawnBehavior;
    vector<SpawnBehavior> _endSpawnBehavior;

    float _activeX, _activeY;
    GameObject* _rockman;
public:
    bool isOn;
    bool isEnd;
    virtual void Init(GameObject* rockman, int activeX, int activeY);
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void OnCollision(GameObject* gameObject);
    void AddMoveBehavior(bool flag, vector<GameObject*> targetObject, MoveBehavior::dirEnum _dir, float speedY, float gravity, float maxSpeedY, vector<float> maxY);
    void AddEffectBehavior(bool flag, string effectName, int effectNum, pair<int, int> rangeX, pair<int, int> rangeY);
    void AddSpawnBehavior(bool flag, vector<bool> spawnFlag, vector<GameObject*> targetObject);
    void TrapOn();
    void TrapEnd();
    bool CheckEnd();
};

