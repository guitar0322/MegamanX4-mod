#include "stdafx.h"
#include "PlayerControler.h"
#include "RockMan.h"
#include "FallState.h"
void PlayerControler::Init()
{
	collider = gameObject->GetComponent<BoxCollider>();
}

void PlayerControler::Update()
{
	if (rockman->attackable == true) {
		if (KEYMANAGER->isOnceKeyDown('C')) {
			rockman->isMiddleChargeAttack = false;
			rockman->isFullChargeAttack = false;
			rockman->Attack();
		}
		if (KEYMANAGER->isStayKeyDown('C')) {
			rockman->chargeTime += TIMEMANAGER->getElapsedTime();
		}
		if (KEYMANAGER->isOnceKeyUp('C')) {
			if (rockman->chargeTime >= rockman->middleChargeTime) {
				rockman->Attack();
			}
		}
	}
}

void PlayerControler::Render()
{
	if(!KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(_backBuffer->getMemDC(), groundRc);
}

//경사면 객체 생성.
//양끝지점, a,b 속성 가짐

//rockman에 경사면 객체 포인터 생성
//idle, run, fall상태일때 경사면 충돌 검사 실행
// 
//경사면 충돌 검사
//x좌표가 경사면 양끝지점 x좌표 사이에 있을때만 수행
//y좌표 +- 5지점이 경사면의 1차함수의 해이면  y좌표를 1차함수의 해y로 바꿈.

bool PlayerControler::CheckGround()
{
	RECT intersectRc;
	RECT* targetRc;
	bool result = false;
	int colNum = COLLIDERMANAGER->colliderList.size();
	if (collider == nullptr)
		return result;
	groundRc = RectMakeCenter(transform->GetX(), transform->GetY() + 46, collider->width, 2);
	for (int i = 0; i < colNum; i++) {
		if (collider == COLLIDERMANAGER->colliderList[i]) continue;
		if (COLLIDERMANAGER->colliderList[i]->isTrigger == true) continue;
		if (COLLIDERMANAGER->colliderList[i]->gameObject->isActive == false) continue;
		if (COLLIDERMANAGER->colliderList[i]->enable == false) continue;
		targetRc = &COLLIDERMANAGER->colliderList[i]->rc;
		if (IntersectRect(&intersectRc, &groundRc, targetRc)) {
			int w = intersectRc.right - intersectRc.left;
			int h = intersectRc.bottom - intersectRc.top;
			if (intersectRc.bottom < GetCenterY(*targetRc) && w > h) {
				result = true;
				return result;
			}
		}
	}
	return result;
}

bool PlayerControler::CheckSlope()
{
	float rockmanY = rockman->transform->GetY() + 45;
	float rockmanX = rockman->transform->GetX();
	for (int i = 0; i < 2; i++) {
		int startX = rockman->slope[i]->GetComponent<Slope>()->startX;
		int endX = rockman->slope[i]->GetComponent<Slope>()->endX;
		float slopeX1 = rockman->slope[i]->GetComponent<Slope>()->x1;
		float slopeY1 = rockman->slope[i]->GetComponent<Slope>()->y1;
		float slopeX2 = rockman->slope[i]->GetComponent<Slope>()->x2;
		float slopeY2 = rockman->slope[i]->GetComponent<Slope>()->y2;
		float a = rockman->slope[i]->GetComponent<Slope>()->a;
		float b = rockman->slope[i]->GetComponent<Slope>()->b;

		if (rockmanX < startX || rockmanX > endX) continue;

		if (rockmanX > slopeX1 && rockmanX < slopeX2) {
			if (a * rockmanX + b + 20 > rockmanY && a * rockmanX + b - 20 < rockmanY) {
				float deltaY = a * rockmanX + b - rockmanY;
				rockman->transform->MoveY(deltaY);
				return true;
			}
		}
		else {
			if (rockmanY < slopeY1 + 5 && rockmanY > slopeY1 - 5) {
				float deltaY = slopeY1 - rockmanY;
				rockman->transform->MoveY(deltaY);
				return true;
			}
			else if (rockmanY < slopeY2 + 5 && rockmanY > slopeY2 - 5) {
				float deltaY = slopeY2 - rockmanY;
				rockman->transform->MoveY(deltaY);
				return true;
			}
		}
	}

	return false;
}


