#include "stdafx.h"
#include "TriggerTest.h"

void TriggerTest::Init()
{
	enterNum = 0;
	stayNum = 0;
	exitNum = 0;
}

void TriggerTest::OnTriggerEnter(GameObject* gameObject)
{
	enterNum++;
}

void TriggerTest::OnTriggerStay(GameObject* gameObject)
{
	stayNum++;

}

void TriggerTest::OnTriggerExit(GameObject* gameObject)
{
	exitNum++;
}
