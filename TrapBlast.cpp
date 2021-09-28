#include "stdafx.h"
#include "TrapBlast.h"
#include "TrapBlastIdle.h"

void TrapBlast::Init(GameObject* rockman, bool dir)
{
	this->dir = dir;
	isDead = true;
    animator = gameObject->GetComponent<Animator>();
    this->rockman = rockman;
    ClipInit();
    GameObject _projectile;
}

void TrapBlast::Update()
{
    if (isDead == false) {
		TrapBlastState* newState = _state->Update(this);
		if (newState != nullptr) {
			SAFE_DELETE(_state);
			_state = newState;
			_state->Enter(this);
		}
    }
}

void TrapBlast::Render()
{
}

void TrapBlast::OnEnable()
{
    SAFE_DELETE(_state);
    _state = new TrapBlastIdle();
    _state->Enter(this);
}
void TrapBlast::OnDisable()
{
    isDead = true;
}
void TrapBlast::OnTriggerEnter(GameObject* gameObject)
{
    if (gameObject->tag == TAGMANAGER->GetTag("player")) {
        gameObject->GetComponent<ObjectInfo>()->Damage(10);
    }
}
void TrapBlast::ClipInit()
{
    _introRight = new AnimationClip();
    _introLeft = new AnimationClip();
    _idleRight = new AnimationClip();
    _idleLeft = new AnimationClip();
    _attackRight = new AnimationClip();
    _attackLeft = new AnimationClip();

    _introRight->Init("trap_blast/trap_blast_intro_right.bmp", 2040, 62, 17, 0.08f);
    _introRight->isLoop = false;
    _introLeft->Init("trap_blast/trap_blast_intro_left.bmp", 2040, 62, 17, 0.08f);
    _introLeft->isLoop = false;
    _idleRight->Init("trap_blast/trap_blast_idle_right.bmp", 960, 62, 8, 0.15f);
    _idleLeft->Init("trap_blast/trap_blast_idle_left.bmp", 960, 62, 8, 0.15f);
    _attackRight->Init("trap_blast/trap_blast_attack_right.bmp", 360, 62, 3, 0.06f);
    _attackLeft->Init("trap_blast/trap_blast_attack_left.bmp", 360, 62, 3, 0.06f);

    animator->AddClip("intro_right", _introRight);
    animator->AddClip("intro_left", _introLeft);
    animator->AddClip("idle_right", _idleRight);
    animator->AddClip("idle_left", _idleLeft);
    animator->AddClip("attack_right", _attackRight);
    animator->AddClip("attack_left", _attackLeft);

    animator->AddTransaction("intro_idle_right", _introRight, _idleRight);
    animator->AddTransaction("intro_idle_left", _introLeft, _idleLeft);

    if (dir == false) {
        animator->SetClip(_introRight);
    }
    else {
        animator->SetClip(_introLeft);
    }
}

void TrapBlast::ChangeClip(string clipName, bool isInitFrame)
{
    if (isInitFrame == true) {
        animator->SetClip(animator->GetClip(clipName), isInitFrame);
    }
    else{
        animator->SetClip(animator->GetClip(clipName));
    }
}
