#pragma once
#include "gameNode.h"
class playGround : public gameNode
{
private:
	int deltaTime;
	int curTime, oldTime;
public:
	int frame;
	int x, y;
	int camX, camY;
	UIBase _ui;
	Text text;
	GameObject particleObj;
	ParticleSystem* demoParticleSys;
	image* testParticle2;
	image* testParticle;
	int changeParticleTime;
	int _camShakeFrame;
	int _alphaFrame;
	playGround();
	~playGround();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

