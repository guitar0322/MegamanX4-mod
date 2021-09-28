#include "stdafx.h"
#include "Colonel.h"
#include "ColonelIdle.h"
void Colonel::Init(GameObject* rockman)
{
	_rockman = rockman;
	_rockmanComponent = rockman->GetComponent<RockMan>();
	_renderer = gameObject->GetComponent<Renderer>();
	_renderer->enable = false;
	_collider = gameObject->GetComponent<BoxCollider>();
	_animator = gameObject->GetComponent<Animator>();
	_objectInfo = gameObject->GetComponent<ObjectInfo>();
	_objectInfo->SetCurHP(0);
	//_overlap = gameObject->GetComponent<Overlap>();
	//_overlap->enable = false;
	_isIntro = true;
	_isDead = false;
	_destroyFlag = false;
	_destroyTime = 0;
	_destroyChangeTime = 0.5f;
	_overlapFlag = false;
	_overlapChangeTime = 0;
	_whiteAlpha = 0;
	destroyNum = 0;
	PropertyInit();
	ClipInit();
	ShadowInit();
	HPBarInit();
	OverlapInit();
	ProjectileInit();
}

void Colonel::Update()
{
	shadowRight.Update();
	shadowLeft.Update();
	hpBar.Update();
	ShadowMove();
	destroy1.Update();
	destroy2.Update();
	for (int i = 0; i < 3; i++) {
		_slashProjectile[i].Update();
	}
	if (_isIntro == true) {
		if (shadowRight.transform->GetX() > gameObject->transform->GetX())
			shadowRight.transform->MoveX(-_shadowSpeed * TIMEMANAGER->getElapsedTime());
		else {
			shadowRight.transform->SetPosition(transform->GetX(), transform->GetY());
			shadowRight.SetActive(false);
		}

		if (shadowLeft.transform->GetX() < gameObject->transform->GetX())
			shadowLeft.transform->MoveX(_shadowSpeed * TIMEMANAGER->getElapsedTime());
		else {
			_renderer->enable = true;
			shadowLeft.transform->SetPosition(transform->GetX(), transform->GetY());
			hpBar.GetComponent<HPBar>()->Heal(hpBar.GetComponent<HPBar>()->GetMaxHP(), 8);
			shadowLeft.SetActive(false);
		}
		if (_objectInfo->GetCurHP() == _objectInfo->GetMaxHP()) {
			_rockmanComponent->isBossIntro = false;
			_rockmanComponent->attackable = true;
			_isIntro = false;
			_state = new ColonelIdle();
		}
		return;
	}
	if (_isHit == true && _isDead == false) {
		_hitTime += TIMEMANAGER->getElapsedTime();
		_overlapChangeTime += TIMEMANAGER->getElapsedTime();
		if (_overlapChangeTime >= 0.1f) {
			//_overlap->enable = _overlapFlag;
			_overlapFlag = !_overlapFlag;
			_overlapChangeTime = 0;
		}
		if (_hitTime >= 4.0f) {
			overlap.SetActive(false);
			//_overlap->enable = false;
			_isHit = false;
		}
	}
	if (_isDead == false) {
		ColonelState* newState = _state->Update(this);
		if (newState != nullptr) {
			SAFE_DELETE(_state);
			_state = newState;
			_state->Enter(this);
		}
	}
	else {
		Destroy();
	}
	overlap.transform->SetPosition(transform->GetX(), transform->GetY());
	overlap.Update();
}

void Colonel::Render()
{
	shadowRight.Render();
	shadowLeft.Render();
	hpBar.Render();
	overlap.Render();
	destroy1.Render();
	destroy2.Render();
	for (int i = 0; i < 3; i++) {
		_slashProjectile[i].Render();
	}
}

void Colonel::OnEnable()
{
	shadowRight.SetActive(true);
	shadowLeft.SetActive(true);
}

void Colonel::PropertyInit()
{
	_dir = true;
	_stateTime = 0;
	_dashSpeed = 250;
	_friction = 80;
	_shadowSpeed = 40;
}

void Colonel::ClipInit()
{
	destroy1.Init();
	destroy2.Init();
	destroy1.renderer->Init("effect/destroy1.bmp", 640, 480);
	destroy2.renderer->Init("effect/destroy2.bmp", 640, 480);
	destroy1.SetActive(false);
	destroy2.SetActive(false);
	_idleRight.Init("colonel/colonel_idle_right.bmp", 550, 202, 2, 0.08f);
	_idleLeft.Init("colonel/colonel_idle_left.bmp", 550, 202, 2, 0.08f);

	_upSwordRight.Init("colonel/colonel_upsword_right.bmp", 1650, 202, 6, 0.08f);
	_upSwordLeft.Init("colonel/colonel_upsword_left.bmp", 1650, 202, 6, 0.08f);
	_upSwordRight.isLoop = false;
	_upSwordLeft.isLoop = false;

	_downSwordRight.Init("colonel/colonel_downsword_right.bmp", 1375, 202, 5, 0.08f);
	_downSwordLeft.Init("colonel/colonel_downsword_left.bmp", 1375, 202, 5, 0.08f);
	_downSwordRight.isLoop = false;
	_downSwordLeft.isLoop = false;

	_dashRight.Init("colonel/colonel_dash_right.bmp", 275, 202, 1, INT_MAX);
	_dashLeft.Init("colonel/colonel_dash_left.bmp", 275, 202, 1, INT_MAX);

	_dead.Init("colonel/colonel_dead.bmp", 275, 202, 1, INT_MAX);

	_animator->AddClip("idle_right", &_idleRight);
	_animator->AddClip("idle_left", &_idleLeft);
	_animator->AddClip("upsword_right", &_upSwordRight);
	_animator->AddClip("upsword_left", &_upSwordLeft);
	_animator->AddClip("downsword_right", &_downSwordRight);
	_animator->AddClip("downsword_left", &_downSwordLeft);
	_animator->AddClip("dash_right", &_dashRight);
	_animator->AddClip("dash_left", &_dashLeft);
	_animator->AddClip("dead", &_dead);

	_animator->SetClip(_animator->GetClip("idle_left"));
}

void Colonel::ShadowInit()
{
	_shadowRight.Init("colonel/colonel_shadow_right.bmp", 1100, 202, 4, 0.08f);
	_shadowLeft.Init("colonel/colonel_shadow_left.bmp", 1100, 202, 4, 0.08f);

	shadowRight.animator->AddClip("shadow_right", &_shadowRight);
	shadowRight.animator->AddClip("shadow_left", &_shadowLeft);
	shadowLeft.animator->AddClip("shadow_right", &_shadowRight);
	shadowLeft.animator->AddClip("shadow_left", &_shadowLeft);
	shadowRight.transform->SetPosition(gameObject->transform->GetX() + 64, gameObject->transform->GetY());
	shadowLeft.transform->SetPosition(gameObject->transform->GetX() - 64, gameObject->transform->GetY());
	shadowRight.renderer->SetAlpha(170);
	shadowLeft.renderer->SetAlpha(170);
	shadowRight.animator->SetClip(shadowRight.animator->GetClip("shadow_left"));
	shadowLeft.animator->SetClip(shadowLeft.animator->GetClip("shadow_left"));
	shadowRight.SetActive(false);
	shadowLeft.SetActive(false);
}

void Colonel::HPBarInit()
{
	hpBar.uiRenderer->Init("ui/boss_hp_bar.bmp", 52, 140);
	hpBar.transform->SetPosition(260, -60);
	hpBar.AddComponent(new HPBar());
	hpBar.GetComponent<HPBar>()->Init(90, gameObject->GetComponent<ObjectInfo>());
	hpBar.GetComponent<HPBar>()->SetDelta(0, 15);
	hpBar.GetComponent<HPBar>()->SetCurHP(0);
}

void Colonel::OverlapInit()
{
	overlap.AddComponent(new ChargeOverlap());
	overlap.GetComponent<ChargeOverlap>()->Init(_renderer, RGB(255, 255, 255));
	overlap.SetActive(false);
}

void Colonel::ProjectileInit()
{
	_projectileRight = new AnimationClip();
	_projectileLeft = new AnimationClip();
	_projectileRight->Init("projectile/colonel_projectile_right.bmp", 180, 112, 3, 0.08f);
	_projectileLeft->Init("projectile/colonel_projectile_left.bmp", 180, 112, 3, 0.08f);
	for (int i = 0; i < 3; i++) {
		_slashProjectile[i].Init();
		_slashProjectile[i].AddComponent(new StraightProjectile());
		_slashProjectile[i].SetProjectileComponent(_slashProjectile[i].GetComponent<StraightProjectile>());
		_slashProjectile[i].projectileComponent->Init("player", "none", 10, 3.0f);
		_slashProjectile[i].projectileComponent->SetNeedEffectDir(false);
		_slashProjectile[i].GetComponent<StraightProjectile>()->SetSpeed(300.0f);
		_slashProjectile[i].animator->AddClip("right", _projectileRight);
		_slashProjectile[i].animator->AddClip("left", _projectileLeft);
		_slashProjectile[i].collider->SetSize(60, 112);
		_slashProjectile[i].collider->isTrigger = true;
		_slashProjectile[i].SetActive(false);
	}
}

void Colonel::Hit()
{
	//overlap.SetActive(true);
	_hitTime = 0;
	_isHit = true;
}

void Colonel::ChangeClip(string clipName)
{
	if (_dir == false) {
		_animator->SetClip(_animator->GetClip(clipName.append("_right")));
	}
	else {
		_animator->SetClip(_animator->GetClip(clipName.append("_left")));
	}
}

void Colonel::FireProjectile()
{
	int y = 60;
	if (_slashNum % 3 == 1) {
		y *= -1;
	}
	_slashProjectile[_slashNum].projectileComponent->Fire(transform->GetX(), transform->GetY() - y, _dir);
	_slashNum++;
	if (_slashNum == 3)
		_slashNum = 0;
}

void Colonel::Disappear()
{
	_renderer->enable = false;
	_animator->enable = false;
	_collider->enable = false;
	//_overlap->enable = false;
	_isHit = false;
	_hitTime = 0;
	_overlapChangeTime = 0;
	overlap.SetActive(false);
	shadowRight.transform->SetX(gameObject->transform->GetX());
	shadowLeft.transform->SetX(gameObject->transform->GetX());
	shadowRight.SetActive(true);
	shadowLeft.SetActive(true);
}

void Colonel::Appear()
{
	if (_renderer->enable == true) return;

	if (_dir == false) {
		transform->SetX(_rockman->transform->GetX() - 120);
		attackRc = RectMakeCenter(transform->GetX() + 120, transform->GetY(), 30, 80);
	}
	else {
		transform->SetX(_rockman->transform->GetX() + 120);
		attackRc = RectMakeCenter(transform->GetX() - 120, transform->GetY(), 30, 80);
	}
	overlap.transform->SetPosition(transform->GetX(), transform->GetY());
	_renderer->enable = true;
	_renderer->Update();
	_animator->enable = true;
	_collider->enable = true;
	ChangeClip("upsword");
	//업데이트 호출순서
	//렌더러 콜라이더 애니메이터 오브젝트인포 콜로넬
}

void Colonel::ShadowMove()
{
	if (shadowRight.isActive == false || _isIntro == true) return;

	if (shadowRight.transform->GetX() <= transform->GetX() + 64) {
		shadowRight.transform->MoveX(_shadowSpeed * TIMEMANAGER->getElapsedTime());
		shadowLeft.transform->MoveX(-_shadowSpeed * TIMEMANAGER->getElapsedTime());
	}
	else {
		shadowRight.SetActive(false);
		shadowLeft.SetActive(false);
	}
}

void Colonel::CheckHit()
{
	RECT intersectRc;
	if (IntersectRect(&intersectRc, &_rockman->GetComponent<BoxCollider>()->rc, &attackRc)) {
		_rockman->GetComponent<ObjectInfo>()->Damage(10);
	}
}

void Colonel::SetDashDir()
{
	if (_rockman->transform->GetX() > transform->GetX()) {
		_dir = true;
	}
	else {
		_dir = false;
	}
}

void Colonel::Dead()
{
	_isDead = true;
	_animator->SetClip(_animator->GetClip("dead"));
	overlap.SetActive(true);
	overlap.GetComponent<ChargeOverlap>()->SetSwitchTime(_destroyChangeTime);
	destroy1.transform->SetPosition(transform->GetX(), transform->GetY() + 20);
	destroy2.transform->SetPosition(transform->GetX(), transform->GetY() + 20);
	whiteFadeOut->SetActive(true);
}

void Colonel::Destroy()
{
	_destroyTime += TIMEMANAGER->getElapsedTime();
	if (_renderer->enable == true) {
		if (_destroyTime >= _destroyChangeTime) {
			EffectManager::getInstance()->EmissionEffect("fire_explosion",
				RND->getFromIntTo(transform->GetX() - 150, transform->GetX() + 150),
				RND->getFromIntTo(transform->GetY() - 150, transform->GetY() + 150));
			if (_destroyFlag == true) {
				destroy1.SetActive(true);
				destroy2.SetActive(false);
			}
			else {
				destroy2.SetActive(true);
				destroy1.SetActive(false);
			}
			_whiteAlpha += 5;
			whiteFadeOut->uiRenderer->SetAlpha(_whiteAlpha);
			destroyNum++;
			if (destroyNum == 25) {
				_destroyChangeTime = 0.25f;
				overlap.GetComponent<ChargeOverlap>()->SetSwitchTime(_destroyChangeTime);
			}
			_destroyFlag = !_destroyFlag;
			_destroyTime = 0;
			if (_whiteAlpha == 255) {
				_renderer->enable = false;
				_collider->enable = false;
				overlap.SetActive(false);
				destroy1.SetActive(false);
				destroy2.SetActive(false);
			}
		}
	}
	else {
		if (_destroyTime >= 0.04f) {
			hpBar.SetActive(false);
			_destroyTime = 0;
			_whiteAlpha -= 2;
			if (_whiteAlpha <= 0) {
				_whiteAlpha = 0;
				_rockman->GetComponent<RockMan>()->Clear();
			}
			whiteFadeOut->uiRenderer->SetAlpha(_whiteAlpha);
		}
	}
}
