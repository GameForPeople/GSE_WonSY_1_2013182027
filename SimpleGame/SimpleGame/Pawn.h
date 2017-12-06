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

	int				m_owner;

	int				m_animCount{};
	int				m_animTimer{};
	int				m_animDirection{};

public:
	Pawn();
	~Pawn();

	Pawn(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y);
	Pawn(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y, const float vectorX, const float vectorY);
	Pawn(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y, const float vectorX, const float vectorY, const int m_owner);

public:
	virtual void Update(const DWORD elapsedTime);
	virtual void Draw(Renderer);

	virtual void DrawLife(Renderer);
public:
	virtual void Move(const Direction dir);
	virtual void Move(const DWORD elapsedTime);
	virtual void LimitMove();
	virtual void OutMoveDeath();

	virtual void ObjectFunction(const DWORD elapsedTime);

public:
	void Animation();

public:
	void SetSpeed(const float);
	int GetOwner() const;
	int GetAnimCount() const { return m_animCount; }
	int GetAnimDirection() const { return m_animDirection; }
	Pos2D GetDirVector() const { return m_dirVector; }
};

