#include "stdafx.h"
#include "HealPack.h"

void HealPack::Init()
{
    basic.Init("item/big_potion.bmp", 44, 26, 1, INT_MAX);
    intro.Init("item/big_potion_intro.bmp", 308, 26, 7, 0.20f);
    intro.isLoop = false;
    idle.Init("item/big_potion_idle.bmp", 176, 26, 4, 0.30f);

    _animator = gameObject->GetComponent<Animator>();
    _animator->AddClip("basic", &basic);
    _animator->AddClip("intro", &intro);
    _animator->AddClip("idle", &idle);
    _animator->AddTransaction("intro_idle", &intro, &idle);
    _speedY = -300;
    _gravity = 300;
    _isGround = false;
}

void HealPack::Update()
{
    if (_isGround == true) return;
    transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());
    _speedY += _gravity * TIMEMANAGER->getElapsedTime();
    if (_speedY >= 300)
        _speedY = 300;
}

void HealPack::Render()
{
}

void HealPack::OnTriggerEnter(GameObject* gameObject)
{
    if (gameObject->tag == TAGMANAGER->GetTag("ground")) {
        _animator->SetClip(_animator->GetClip("intro"));
        _isGround = true;
    }
    if (gameObject->tag == TAGMANAGER->GetTag("player")) {
        gameObject->GetComponent<RockMan>()->hpBar->GetComponent<HPBar>()->Heal(40, 1);
        this->gameObject->SetActive(false);
    }
}

void HealPack::OnEnable()
{
    _animator->SetClip(_animator->GetClip("basic"));
    _isGround = false;
    _speedY = -300;
}
