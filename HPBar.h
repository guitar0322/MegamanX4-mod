#pragma once
#include "GameObject.h"
class HPBar :
    public Component
{
private:
    RECT _hp;
    RECT _redHP;
    HBRUSH gBrush, yBrush, rBrush, oBrush;
    HPEN nullPen, oPen;
    int _maxHeight;
    int _curHeight;
    int _backCurHeight;
    float _delay;
    float _deltaReduce;
    bool _isDamaged;
    bool _isHeal;
    int _healAmount;
    int _deltaHeal;
    int _healStack;
    int _deltaX, _deltaY;
    ObjectInfo* _targetInfo;
public:
    virtual void Init(int maxHeight, ObjectInfo* targetInfo);
    virtual void Update();
    virtual void Render();

    void Heal(int healAmount, int deltaHeal);
    bool GetIsHeal() { return _isHeal; }
    int GetMaxHP() { return _maxHeight; }
    void SetCurHP(int hp) { _curHeight = hp; _backCurHeight = hp; }
    void SetDelta(int x, int y) { _deltaX = x; _deltaY = y; }
};

