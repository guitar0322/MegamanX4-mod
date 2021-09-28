#include "stdafx.h"
#include "StraightProjectile.h"

void StraightProjectile::Update()
{
	Projectile::Update();
	if (_dir == false) {
		transform->position.x += _speed * TIMEMANAGER->getElapsedTime();
	}
	else {
		transform->position.x -= _speed * TIMEMANAGER->getElapsedTime();
	}
}

void StraightProjectile::Render()
{
}

void StraightProjectile::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == _targetTag) {

		if (gameObject->GetComponent<ObjectInfo>()->GetCurHP() >= _damage && _targetTag != TAGMANAGER->GetTag("player")) {
			this->gameObject->SetActive(false);
		}
		if (_hitEffectName.compare("none") != 0) {
			if (gameObject->GetComponent<ObjectInfo>()->GetHitable() == false) {
				string effectName = "block_hit";
				if (_dir == false)
					effectName.append("_right");
				else
					effectName.append("_left");
				EffectManager::getInstance()->EmissionEffect(effectName, transform->GetX(), transform->GetY());
				this->gameObject->SetActive(false);
				return;
			}
			if (_isNeedEffectDir == true) {
				string effectName = _hitEffectName;
				if (_dir == false)
					effectName.append("_right");
				else
					effectName.append("_left");
				EffectManager::getInstance()->EmissionEffect(effectName, transform->GetX(), transform->GetY());
			}
			else {
				EffectManager::getInstance()->EmissionEffect(_hitEffectName, transform->GetX(), transform->GetY());
			}
		}
		gameObject->GetComponent<ObjectInfo>()->Damage(_damage);
	}
}
//프로젝틸 종류
//록맨 기본공격, 중간공격, 최대공격
//트랩블래스트 공격
//프라이빗 공격
//각종 보스 공격
//
//최상위 프로젝틸
//타겟 태그, 사라지면서 생기는 이펙트, 발사(위치, 방향), 데미지, 유지시간

//오버라이딩 함수
//움직이는거, 맞았을때 동작(관통하거나 사라지거나)
