#include "stdafx.h"
#include "ObjectInfo.h"
#include "HitState.h"
ObjectInfo::ObjectInfo()
{
}

ObjectInfo::~ObjectInfo()
{
}

void ObjectInfo::Init(int maxHp, int explosionNum, int type)
{
	this->_maxHp = maxHp;
	this->_explosionNum = explosionNum;
	_isDead = false;
	_isHitable = true;
	_type = type;
	_curHp = maxHp;
	_explosionRangeX = 0;
	_explosionRangeY = 0;
	_hitableTime = 0;
	_hitOverlap.Init();
	_hitOverlap.AddComponent(new ChargeOverlap());
	_hitOverlap.GetComponent<ChargeOverlap>()->Init(gameObject->GetComponent<Renderer>(), RGB(255, 255, 255));
	_hitOverlap.SetActive(false);
	_overlapTime = 0;
	_overlapLimitTime = 0.1f;
}

void ObjectInfo::Update()
{
	_hitOverlap.transform->SetPosition(transform->GetX(), transform->GetY());
	_hitOverlap.Update();
	if(_isHitable == false) {
		_hitableTime += TIMEMANAGER->getElapsedTime();
		if (_hitableTime >= 4.0f) {
			_hitableTime = 0;
			_isHitable = true;
		}
	}
	if (_hitOverlap.isActive == true) {
		_overlapTime += TIMEMANAGER->getElapsedTime();
		if (_overlapTime >= _overlapLimitTime) {
			_overlapTime = 0;
			_hitOverlap.SetActive(false);
		}
	}
}

void ObjectInfo::Render()
{
	_hitOverlap.Render();
}
void ObjectInfo::Damage(int damage)
{
	//면역상태일 경우 데미지를 입지 않음. 데미지100(깔려죽는경우) 제외
	if (_isHitable == false && damage != 100)
		return;

	//피격연출 이미지 활성화
	_hitOverlap.SetActive(true);
	_overlapTime = 0;
	_curHp -= damage;

	//보스와 록맨만 피격시 면역상태 활성화
	if (_type == 3) {
		gameObject->GetComponent<RockMan>()->Hit();
		_isHitable = false;
	}
	if (_type == 5) {
		gameObject->GetComponent<Colonel>()->Hit();
		_isHitable = false;
	}

	//체력이 0이하가 되면 사망
	if (_curHp <= 0) {
		_curHp = 0;
		if (_type == 3) {
			gameObject->transform->GetChild(3)->gameObject->SetActive(true);
		}
		Dead();
	}
}

void ObjectInfo::Dead()
{
	//에너미에 따라 다른 파편 생성
	if (_type == 0) {
		FragmentManager::GetInstacne()->EmissionRockFrag(transform->GetX(), transform->GetY());
	}
	else if (_type == 1) {
		FragmentManager::GetInstacne()->EmissionTrapBlastFrag(transform->GetX(), transform->GetY());
	}
	else if (_type == 2) {
		FragmentManager::GetInstacne()->EmissionPrivateFrag(transform->GetX(), transform->GetY());
	}
	else if (_type == 3) {
		gameObject->GetComponent<RockMan>()->Dead();
	}
	else if (_type == 4) {
		FragmentManager::GetInstacne()->EmissionCarrierFrag(transform->GetX(), transform->GetY());
		gameObject->GetComponent<ItemCarrier>()->SpawnHealpack();
	}
	else if (_type == 5) {
		gameObject->GetComponent<Colonel>()->Dead();
		return;
	}
	for (int i = 0; i < _explosionNum; i++) {
		int x = transform->GetX() + RND->getFromIntTo(-_explosionRangeX, _explosionRangeX+1);
		int y = transform->GetY() + RND->getFromIntTo(-_explosionRangeY, _explosionRangeY+1);
		EffectManager::getInstance()->EmissionEffect("fire_explosion", x, y);
	}
	gameObject->SetActive(false);
	_isDead = true;
}

void ObjectInfo::UnActiveObject()
{
}

void ObjectInfo::SetCurHP(int hp)
{
	_curHp = hp;
	if (_curHp > _maxHp)
		_curHp = _maxHp;
}
