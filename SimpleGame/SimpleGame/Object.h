#pragma once

#include "Renderer.h"

struct Pos2D {
	float x;
	float y;

	void CalCulNomalVector(float arguX, float arguY) {
		x = (arguX / sqrt(arguX * arguX + arguY * arguY));
		y = (arguY / sqrt(arguX * arguX + arguY * arguY));
	}
};


class Object
{
protected:
	OBJECT_TYPE			m_type;
	TEAM_TYPE			m_team;

	Pos2D				m_pos;
	float				m_size;
	
	int					m_life{ 0 };
	int					m_lifeCount{0};

	int					m_objectTime{ 0 };

public:
	Object(const OBJECT_TYPE type, const TEAM_TYPE team, const float posX, const float posY);

	virtual void Update(); //= 0;
	
public:
	void Damaged();
	void Damaged(const int damage);
	
	void ObjectFunction(const DWORD elapsedTime);

public:
	Pos2D GetPos() const;
	TEAM_TYPE GetTeam() const;
	int GetObejctTime() const;
	int GetLife() const;
	float GetSize() const;

	void SetPos(const float x, const float y);
	void SetObjectTime(const int inputTime);

public:
	Object() = default;
	virtual ~Object() = default;
};

