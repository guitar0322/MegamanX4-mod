#pragma once
#include "GameObject.h"

class RockMan;
class PlayerControler :
    public Component
{
public:
    PlayerControler() {};
    ~PlayerControler() {};
    RockMan* rockman;
    BoxCollider* collider;
    float gravity;
    float jumpPower;
    float speed;
    float wallJumpPower;
    int diveTime;
    RECT groundRc;
    void Init();
    void Update();
    void Render();
    bool CheckGround();
    bool CheckSlope();
    void SetRockman(RockMan* rockman) { this->rockman = rockman; }
};

