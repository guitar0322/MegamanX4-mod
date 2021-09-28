#pragma once
#include "GameObject.h"
class TrapManager :
    public Component
{
private:
    typedef struct tagTrap {
        int x;
        vector<int> targetObjectIdx;
    }TRAP;
private:
    RockMan* _rockman;
    vector<GameObject*> _targetObjectV;
    vector<TRAP> _trapV;
public:
    virtual void Init(RockMan* rockman);
    virtual void Update();
    virtual void Render();
    void AddObject(GameObject* targetObject);
};

