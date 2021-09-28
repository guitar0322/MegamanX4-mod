#pragma once
#include "GameObject.h"
class TriggerTest :
    public Component
{
public:
    int enterNum;
    int exitNum;
    int stayNum;
    void Init();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void OnTriggerStay(GameObject* gameObject);
    virtual void OnTriggerExit(GameObject* gameObject);
};

