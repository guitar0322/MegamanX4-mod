#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
}


Animator::~Animator()
{

}

void Animator::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	if (renderer == nullptr) {
		throw "Animator에서 발생 : 게임 오브젝트에 Renderer컴포넌트가 없습니다";
	}
	currentFrame = 0;
}

void Animator::Update()
{
	if (curClip == nullptr)
		return;
	frameTime += TIMEMANAGER->getElapsedTime();
	if (frameTime >= curClip->frameTerm) {
		BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
			curClip->wholeDC, curClip->frameWidth * currentFrame, 0, SRCCOPY);
		currentFrame++;
		if (currentFrame == curClip->frameNum) {
			if (curClip->isLoop == true)
				currentFrame = 0;
			else {
				currentFrame = curClip->frameNum - 1;
				for (transactionIter = transactionMap.begin(); transactionIter != transactionMap.end(); transactionIter++) {
					if (transactionIter->second.startClip == curClip) {
						SetClip(transactionIter->second.nextClip);
					}
				}
			}
		}
		frameTime = 0;
	}
}

void Animator::Render()
{

}

void Animator::SetClip(AnimationClip* newClip)
{
	preClip = curClip;
	curClip = newClip;
	curClip->currentFrame = 0;
	currentFrame = 0;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, 0, 0, SRCCOPY);
}

void Animator::SetClip(AnimationClip* newClip, int startFrame)
{
	preClip = curClip;
	curClip = newClip;
	curClip->currentFrame = startFrame;
	currentFrame = startFrame;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, curClip->currentFrame * curClip->frameWidth, 0, SRCCOPY);
}

void Animator::AddClip(string clipName, AnimationClip* newClip)
{
	clipMap.insert(make_pair(clipName, newClip));
}

AnimationClip* Animator::GetClip(string clipName)
{
	map<string, AnimationClip*>::iterator iter;
	iter = clipMap.find(clipName);
	if (iter != clipMap.end()) {
		return iter->second;
	}
	return nullptr;
}

void Animator::AddTransaction(string name, AnimationClip* startClip, AnimationClip* nextClip)
{
	TRANSACTION newTransaction = { startClip, nextClip };
	transactionMap.insert(make_pair( name, newTransaction));
}
