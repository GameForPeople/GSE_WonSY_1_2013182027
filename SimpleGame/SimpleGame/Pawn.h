#pragma once
#include "Actor.h"

enum class Direction
{
	Up			= 1,
	Down		= 2,
	Left		= 3,
	Right		= 4,
	UpLeft		= 5,
	UpRight		= 6,
	DownLeft	= 7,
	DownRight	= 8
};


class Pawn :
	public Actor
{
private:
	float			m_speed;

	Pos2D			m_dirVector;
	Direction		m_direction;

public:
	Pawn();
	~Pawn();

	Pawn(const OBJECT_TYPE inputType, const float x, const float y);
	Pawn(const OBJECT_TYPE inputType, const float x, const float y, const float vectorX, const float vectorY);

public:
	virtual void Update(const DWORD elapsedTime);
	virtual void Draw(Renderer);

public:
	virtual void Move(const Direction dir);
	virtual void Move(const DWORD elapsedTime);
	virtual void LimitMove();

	virtual void ObjectFunction(const DWORD elapsedTime);

public:
	void SetSpeed(const float);

};

