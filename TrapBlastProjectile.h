#pragma once
#include "Projectile.h"
class TrapBlastProjectile :
    public Projectile
{
private:
    float _speed;
    float _angle;
    GameObject* _rockman;
public:
    virtual void Update();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void Fire(int x, int y, bool dir);
    void SetSpeed(float speed) { _speed = speed; }
    float GetSpeed() { return _speed; }

    void SetRockman(GameObject* rockman) { _rockman = rockman; }
};

