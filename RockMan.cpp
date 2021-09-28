#include "stdafx.h"
#include "RockMan.h"
#include "IntroState.h"
#include "HitState.h"
#include "IdleState.h"
void RockMan::InputHandle()
{
    State* state = _state->InputHandle(this);
    if (state != nullptr) {
        SAFE_DELETE(_state);
        _state = state;
        _state->Enter(this);
    }
}

void RockMan::Init()
{
    renderer = gameObject->GetComponent<Renderer>();
    collider = gameObject->GetComponent<BoxCollider>();
    animator = gameObject->GetComponent<Animator>();
    controler = gameObject->GetComponent<PlayerControler>();
    objectInfo = gameObject->GetComponent<ObjectInfo>();
    _state = new IntroState();
    dir = false;//false면 오른쪽 true 면 왼쪽
    isFall = false;
    isDash = false;
    isAttack = false;
    isMiddleChargeAttack = false;
    isFullChargeAttack = false;
    chargeTime = 0;
    middleChargeTime = 2.0f;
    fullChargeTime = 4.0f;
    attackTime = 0;
    isDead = false;
    isBoss = false;
    isBossIntro = false;
    isClear = false;
    autoMove = false;
    InitClip();
    _state->Enter(this);
}

void RockMan::Update()
{
    if (isDead == true)
        return;
    if (isClear == true) {
        if (animator->currentFrame == animator->curClip->frameNum - 1) {
            transform->MoveY(-250 * TIMEMANAGER->getElapsedTime());
        }
        return;
    }
    speedX = 140 * TIMEMANAGER->getElapsedTime();
    gravity = 400 * TIMEMANAGER->getElapsedTime();
    if (isDash == true) {
        speedX *= 1.8f;
    }

    if (transform->GetX() >= 9900 && isBoss == false) {
        attackable = false;
        ChangeClip("run_left", false);
        shadowManager->GetComponent<ShadowManager>()->OffShadow();
        isDash = false;
        _state = new IdleState();
        autoMove = true;
        isBoss = true;
    }
    if (autoMove == true) {
        transform->MoveX(-speedX);
        if (transform->GetX() <= 9700) {
            ChangeClip("idle_right", false);
            dir = false;
            autoMove = false;
            isBossIntro = true;
            warning->SetActive(true);
        }
        return;
    }
    if (isBossIntro == true)
        return;
    InputHandle();
    _state->Update(this);
    if (isAttack == true) {
        attackTime += TIMEMANAGER->getElapsedTime();
        if (attackTime > 1.3f) {
            attackTime = 0;
            isAttack = false;
            _state->Attack(this);
        }
    }
    if (chargeTime >= middleChargeTime && isMiddleChargeAttack == false) {
        isMiddleChargeAttack = true;
        middleChargeEffect->GetComponent<Effect>()->Emission(false);
        chargeOverlap->transform->SetPosition(transform->GetX(), transform->GetY());
        chargeOverlap->SetActive(true);
    }
    if (chargeTime >= fullChargeTime && isFullChargeAttack == false) {
        isMiddleChargeAttack = false;
        isFullChargeAttack = true;
        fullChargeEffect->GetComponent<Effect>()->Emission(false);
    }
}

void RockMan::Render()
{
}

void RockMan::OnTriggerEnter(GameObject* gameObject)
{
}

void RockMan::InitClip()
{
    idleRight = new AnimationClip();
    idleRight->Init("idle/idle_right.bmp", 740, 90, 10, 0.20f);
    idleAttackRight = new AnimationClip();
    idleAttackRight->Init("idle/idle_attack_right.bmp", 640, 90, 8, 0.12f);
    idleAttackRight->isLoop = false;
    chargeAttackRight = new AnimationClip();
    chargeAttackRight->Init("idle/charge_attack_right.bmp", 492, 102, 6, 0.12f);
    chargeAttackRight->isLoop = false;

    idleLeft = new AnimationClip();
    idleLeft->Init("idle/idle_left.bmp", 740, 90, 10, 0.20f);
    idleAttackLeft = new AnimationClip();
    idleAttackLeft->Init("idle/idle_attack_left.bmp", 640, 90, 8, 0.12f);
    idleAttackLeft->isLoop = false;
    chargeAttackLeft = new AnimationClip();
    chargeAttackLeft->Init("idle/charge_attack_left.bmp", 492, 102, 6, 0.12f);
    chargeAttackLeft->isLoop = false;

    runRight = new AnimationClip();
    runRight->Init("run/run_right.bmp", 1358, 94, 14, 0.08f);
    runAttackRight = new AnimationClip();
    runAttackRight->Init("run/run_attack_right.bmp", 1512, 94, 14, 0.08f);

    runLeft = new AnimationClip();
    runLeft->Init("run/run_left.bmp", 1358, 94, 14, 0.08f);
    runAttackLeft = new AnimationClip();
    runAttackLeft->Init("run/run_attack_left.bmp", 1512, 94, 14, 0.08f);

    jumpRight = new AnimationClip();
    jumpRight->Init("jump/jump_right.bmp", 272, 114, 4, 0.10f);
    jumpRight->isLoop = false;
    jumpAttackRight = new AnimationClip();
    jumpAttackRight->Init("jump/jump_attack_right.bmp", 328, 114, 4, 0.10f);
    jumpAttackRight->isLoop = false;

    jumpLeft = new AnimationClip();
    jumpLeft->Init("jump/jump_left.bmp", 272, 114, 4, 0.10f);
    jumpLeft->isLoop = false;
    jumpAttackLeft = new AnimationClip();
    jumpAttackLeft->Init("jump/jump_attack_left.bmp", 328, 114, 4, 0.10f);
    jumpAttackLeft->isLoop = false;

    fallRight = new AnimationClip();
    fallRight->Init("fall/fall_right.bmp", 272, 114, 4, 0.08f);
    fallRight->isLoop = false;
    fallAttackRight = new AnimationClip();
    fallAttackRight->Init("fall/fall_attack_right.bmp", 328, 114, 4, 0.10f);
    fallAttackRight->isLoop = false;

    fallLeft = new AnimationClip();
    fallLeft->Init("fall/fall_left.bmp", 272, 114, 4, 0.08f);
    fallLeft->isLoop = false;
    fallAttackLeft = new AnimationClip();
    fallAttackLeft->Init("fall/fall_attack_left.bmp", 328, 114, 4, 0.10f);
    fallAttackLeft->isLoop = false;

    wallRight = new AnimationClip();
    wallRight->Init("wall/wall_right.bmp", 384, 128, 4, 0.08f);
    wallRight->isLoop = false;
    wallLeft = new AnimationClip();
    wallLeft->Init("wall/wall_left.bmp", 384, 128, 4, 0.08f);
    wallLeft->isLoop = false;

    wallAttackRight = new AnimationClip();
    wallAttackRight->Init("wall/wall_attack_right.bmp", 384, 128, 4, 0.08f);
    wallAttackRight->isLoop = false;
    wallAttackLeft = new AnimationClip();
    wallAttackLeft->Init("wall/wall_attack_left.bmp", 384, 128, 4, 0.08f);
    wallAttackLeft->isLoop = false;

    groundRight = new AnimationClip();
    groundRight->Init("ground/ground_right.bmp", 192, 102, 3, 0.06f);
    groundRight->isLoop = false;
    groundAttackRight = new AnimationClip();
    groundAttackRight->Init("ground/ground_attack_right.bmp", 252, 102, 3, 0.06f);
    groundAttackRight->isLoop = false;

    groundLeft = new AnimationClip();
    groundLeft->Init("ground/ground_left.bmp", 192, 102, 3, 0.06f);
    groundLeft->isLoop = false;
    groundAttackLeft = new AnimationClip();
    groundAttackLeft->Init("ground/ground_attack_left.bmp", 252, 102, 3, 0.06f);
    groundAttackLeft->isLoop = false;
    
    
    dashRight = new AnimationClip();
    dashRight->Init("dash/dash_right.bmp", 536, 84, 4, 0.06f);
    dashRight->isLoop = false;
    dashAttackRight = new AnimationClip();
    dashAttackRight->Init("dash/dash_attack_right.bmp", 536, 84, 4, 0.06f);
    dashAttackRight->isLoop = false;

    dashLeft = new AnimationClip();
    dashLeft->Init("dash/dash_left.bmp", 536, 84, 4, 0.06f);
    dashLeft->isLoop = false;
    dashAttackLeft = new AnimationClip();
    dashAttackLeft->Init("dash/dash_attack_left.bmp", 536, 84, 4, 0.06f);
    dashAttackLeft->isLoop = false;

    breakRight = new AnimationClip();
    breakRight->Init("dash/break_right.bmp", 684, 90, 6, 0.06f);
    breakRight->isLoop = false;
    breakAttackRight = new AnimationClip();
    breakAttackRight->Init("dash/break_attack_right.bmp", 684, 90, 6, 0.06f);
    breakAttackRight->isLoop = false;

    breakLeft = new AnimationClip();
    breakLeft->Init("dash/break_left.bmp", 684, 90, 6, 0.06f);
    breakLeft->isLoop = false;
    breakAttackLeft = new AnimationClip();
    breakAttackLeft->Init("dash/break_attack_left.bmp", 684, 90, 6, 0.06f);
    breakAttackLeft->isLoop = false;

    smallHitRight = new AnimationClip();
    smallHitRight->Init("hit/small_hit_right.bmp", 280, 112, 4, 0.20f);
    smallHitRight->isLoop = false;
    smallHitLeft = new AnimationClip();
    smallHitLeft->Init("hit/small_hit_left.bmp", 280, 112, 4, 0.20f);
    smallHitLeft->isLoop = false;

    intro = new AnimationClip();
    intro->Init("other/intro.bmp", 1920, 144, 15, 0.12f);
    intro->isLoop = false;
    outro = new AnimationClip();
    outro->Init("other/outro.bmp", 1080, 180, 9, 0.15f);
    outro->isLoop = false;

    animator->AddClip("idle_right", idleRight);
    animator->AddClip("idle_left", idleLeft);
    animator->AddClip("idle_attack_right", idleAttackRight);
    animator->AddClip("idle_attack_left", idleAttackLeft);
    animator->AddClip("charge_attack_right", chargeAttackRight);
    animator->AddClip("charge_attack_left", chargeAttackLeft);

    animator->AddClip("run_right", runRight);
    animator->AddClip("run_left", runLeft);
    animator->AddClip("run_attack_right", runAttackRight);
    animator->AddClip("run_attack_left", runAttackLeft);

    animator->AddClip("jump_right", jumpRight);
    animator->AddClip("jump_left", jumpLeft);
    animator->AddClip("jump_attack_right", jumpAttackRight);
    animator->AddClip("jump_attack_left", jumpAttackLeft);

    animator->AddClip("fall_right", fallRight);
    animator->AddClip("fall_left", fallLeft);
    animator->AddClip("fall_attack_right", fallAttackRight);
    animator->AddClip("fall_attack_left", fallAttackLeft);

    animator->AddClip("wall_right", wallRight);
    animator->AddClip("wall_left", wallLeft);
    animator->AddClip("wall_attack_right", wallAttackRight);
    animator->AddClip("wall_attack_left", wallAttackLeft);

    animator->AddClip("ground_right", groundRight);
    animator->AddClip("ground_left", groundLeft);
    animator->AddClip("ground_attack_right", groundAttackRight);
    animator->AddClip("ground_attack_left", groundAttackLeft);


    animator->AddClip("dash_right", dashRight);
    animator->AddClip("dash_left", dashLeft);
    animator->AddClip("dash_attack_right", dashAttackRight);
    animator->AddClip("dash_attack_left", dashAttackLeft);

    animator->AddClip("break_right", breakRight);
    animator->AddClip("break_left", breakLeft);
    animator->AddClip("break_attack_right", breakAttackRight);
    animator->AddClip("break_attack_left", breakAttackLeft);

    animator->AddClip("small_hit_right", smallHitRight);
    animator->AddClip("small_hit_left", smallHitLeft);

    animator->AddClip("intro", intro);
    animator->AddClip("outro", outro);

    animator->AddTransaction("ground_idle_right", groundRight, idleRight);
    animator->AddTransaction("ground_idle_left", groundLeft, idleLeft);
}

void RockMan::ChangeClip(string clipName, bool isInitFrame)
{
    if(isInitFrame == false)
        animator->SetClip(animator->GetClip(clipName));
    else {
        animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
    }
}

void RockMan::Attack()
{
    middleChargeEffect->SetActive(false);
    fullChargeEffect->SetActive(false);
    chargeOverlap->SetActive(false);
    chargeTime = 0;
    isAttack = true;
    attackTime = 0;
    _state->Attack(this);
    if (isFullChargeAttack == true) {
        fullAttackEffect->GetComponent<Effect>()->Emission(dir);
    }
    else if (isMiddleChargeAttack == true) {
        middleAttackEffect->GetComponent<Effect>()->Emission(dir);
    }
    else {
        basicAttackEffect->GetComponent<Effect>()->Emission(dir);
    }
    isMiddleChargeAttack = false;
    isFullChargeAttack = false;
}

void RockMan::MoveBossStart()
{
}

void RockMan::SetState(State* newState)
{
    SAFE_DELETE(_state);
    _state = newState;
    _state->Enter(this);
}

void RockMan::Dead()
{
    SAFE_DELETE(_state);
    isDead = true;
    gameObject->SetActive(false);
}

void RockMan::Hit()
{
    SetState(new HitState());
    chargeTime = 0;
    middleChargeEffect->SetActive(false);
    fullChargeEffect->SetActive(false);
    chargeOverlap->SetActive(false);
    chargeOverlap->GetComponent<ChargeOverlap>()->FillTransparent();
}

void RockMan::Clear()
{
    if (isClear == false) {
        transform->SetY(transform->GetY() - 50);
        ChangeClip("outro", false);
    }
    isClear = true;
}
