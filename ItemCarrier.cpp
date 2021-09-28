#include "stdafx.h"
#include "ItemCarrier.h"

void ItemCarrier::Init()
{
    _right.Init("enemy/item_carrier_right.bmp", 300, 96, 3, 0.12f);
    _left.Init("enemy/item_carrier_left.bmp", 300, 96, 3, 0.12f);
    _animator = gameObject->GetComponent<Animator>();
    _animator->AddClip("right", &_right);
    _animator->AddClip("left", &_left);
    _animator->SetClip(_animator->GetClip("left"));
    _dir = true;
    _speed = 100.0f;
    _stopTime = 0;
}

void ItemCarrier::Update()
{
    if (_dir == true) {
        if (transform->GetX() >= _disablePos - 350) {
			transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime());
        }
        else {
            _stopTime += TIMEMANAGER->getElapsedTime();
            if (_stopTime >= 5.0f) {
                _dir = false;
                _animator->SetClip(_animator->GetClip("right"));
            }
        }
    }
    else {
        transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());
        if (transform->GetX() >= _disablePos) {
            gameObject->SetActive(false);
        }
    }
}

void ItemCarrier::Render()
{
}

void ItemCarrier::OnEnable()
{
    _dir = true;
    _stopTime = 0;
    _animator->SetClip(_animator->GetClip("left"));
    _disablePos = transform->GetX();
}

void ItemCarrier::SpawnHealpack()
{
    healPack->transform->SetPosition(transform->GetX(), transform->GetY());
    healPack->SetActive(true);
}
