#pragma once
#include "Object.h"

struct Vector4f {
	float x;
	float y;
	float z;
	float a;
};


class Actor :
	public Object
{
protected:
	Vector4f		m_color;
	int				m_index{ 0 };

public:
	Actor() = default;
	Actor(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y);
	Actor(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y, const int index);
	Actor(const OBJECT_TYPE inputType, const TEAM_TYPE team, const Pos2D pos, const Pos2D direction);
	Actor(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y, const float vectorX, const float vectorY);
	virtual ~Actor();
	
public:
	//void SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY);
	virtual void Update(const DWORD elapsedTime);
	virtual void Draw(Renderer &);

	virtual void DrawLife(Renderer &);

	WEAPON_TYPE	m_nextRespone;
public:
	virtual void ObjectFunction(const DWORD elapsedTime);

public:
	void SetColor(const Vector4f& inputColor);
	void SetColor(const float red, const float green, const float blue, const float alpha);
	int GetIndex() const { return m_index; }
};

