#pragma once
#include "Behavior.h"
class SpawnBehavior :
    public Behavior
{
private:
    vector<bool> _spawnFlag;
    vector<GameObject*> _targetObject;
public:
    virtual void Init(vector<bool> spawnFlag, vector<GameObject*> targetObject);
    void Spawn();
};

