#pragma once
#include "Object.h"

enum class Direction
{
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
	UpLeft = 5,
	UpRight,
	DownLeft,
	DownRight,
};

class Actor :
	public Object
{
private:
	float m_speed;
	
	Pos2D m_dirVector;
	Direction m_direction;

public:
	Actor();
	Actor(Pos2D pos, float size, Vector4f color, float speed, Pos2D direction);
	Actor(float x, float y, float size, Vector4f color, float speed, float vectorX, float vectorY);	
	Actor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY);
	virtual ~Actor();

	void Move(Direction dir);
	void Move();

	void SetSpeed(float);
};

