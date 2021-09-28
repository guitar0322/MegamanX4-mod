#pragma once
#include "Projectile.h"
class StraightProjectile :
    public Projectile
{
private:
    float _speed;
public:
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);

    void SetSpeed(float speed) { _speed = speed; }
    float GetSpeed() { return _speed; }
};

