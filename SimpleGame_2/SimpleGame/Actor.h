#pragma once
#include "Object.h"
class Actor :
	public Object
{
private:
	float m_speed;
public:
	Actor();
	virtual ~Actor();

	void Move(Direction dir);
	void SetSpeed(float);
};

