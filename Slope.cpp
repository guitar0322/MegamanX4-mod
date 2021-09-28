#include "stdafx.h"
#include "Slope.h"

void Slope::Init(int startX, int endX, float x1, float y1, float x2, float y2)
{
	this->startX = startX;
	this->endX = endX;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	a = (y2 - y1) / (x2 - x1);
	b = y1 - (a * x1);
	//y = ax + b;
	// 
	//1,2  2,3
	//y = 1 * x + b;
	//y = x + 1;

	//2, 6 4, 7
	//y = 1/2 * x + b;
	//y = 1/2 * x + 5;


	//y > a*x + b;
}

void Slope::Update()
{
}

void Slope::Render()
{
}
