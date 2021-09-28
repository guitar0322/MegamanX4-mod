#pragma once
class Colonel;
class ColonelState
{
public:
	virtual ColonelState* Update(Colonel* colonel) = 0;
	virtual void Enter(Colonel* colonel) = 0;
	virtual void Exit(Colonel* colonel) = 0;
};

