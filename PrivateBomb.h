#pragma once
#include "Projectile.h"
class PrivateBomb :
    public Projectile
{
private:
    float _gravity;
    float _angle;
    float _speedY;
    float _speedX;
    float _speed;
public:
    virtual void Update();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void Fire(int x, int y, bool dir);

    void SetSpeed(float speed) { _speed = speed; }
    float GetSpeed() { return _speed; }
};

