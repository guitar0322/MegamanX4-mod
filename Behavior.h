#pragma once
class Behavior
{
public:
	bool isEnd;
	vector<GameObject*> targetObject;
	virtual void Init();
	virtual void Update();
};

