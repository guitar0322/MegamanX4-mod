#pragma once
#include "Behavior.h"
class MoveBehavior :
    public Behavior
{
public:
    static enum dirEnum {
        DOWN,
        UP,
        RIGHT,
        LEFT
    };
private:
    float _speed;
    float _gravity;
    float _maxSpeed;
    bool _isSlow;
    int _moveTerm;
    int _isOn;
    GameObject* _rockman;
    dirEnum _dir;
    vector<float> _maxPos;
public:
    virtual void Init(vector<GameObject*> targetObject, dirEnum dir, float speedY, float gravity, float maxSpeedY, vector<float> maxY, GameObject* rockman);
    virtual void Update();
    void CheckLack(int x, int y, int idx);
    bool CheckCollision(RECT rc);
    bool CheckEnd();
    void Start();
};

