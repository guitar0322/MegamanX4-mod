#pragma once
#include "GameObject.h"
class ObjectInfo :
    public Component
{
private:
    int _maxHp, _curHp;
    int _explosionRangeX, _explosionRangeY;
    int _explosionNum;
    bool _isDead;
    int _type;
    bool _isHitable;
    float _hitableTime;
    float _overlapTime;
    float _overlapLimitTime;
    ImageObject _hitOverlap;
public:
    ObjectInfo();
    ~ObjectInfo();
    virtual void Init(int maxHp, int explosionNum, int type);
    virtual void Update();
    virtual void Render();
    void Damage(int damage);
    void Dead();
    void UnActiveObject();
    void SetExplosionRange(int rangeX, int rangeY) { _explosionRangeX = rangeX; _explosionRangeY = rangeY; }

    int GetCurHP() { return _curHp; }
    void SetCurHP(int hp);

    int GetMaxHP() { return _maxHp; }

    bool GetHitable() { return _isHitable; }
    void SetOverlapTime(float overlapTime) { _overlapLimitTime = overlapTime; }
};

