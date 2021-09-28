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
//������ƿ ����
//�ϸ� �⺻����, �߰�����, �ִ����
//Ʈ������Ʈ ����
//�����̺� ����
//���� ���� ����
//
//�ֻ��� ������ƿ
//Ÿ�� �±�, ������鼭 ����� ����Ʈ, �߻�(��ġ, ����), ������, �����ð�

//�������̵� �Լ�
//�����̴°�, �¾����� ����(�����ϰų� ������ų�)
