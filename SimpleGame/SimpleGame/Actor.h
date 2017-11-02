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

public:
	Actor() = default;
	Actor(const OBJECT_TYPE inputType, const float x, const float y);
	Actor(const OBJECT_TYPE inputType, const Pos2D pos, const Pos2D direction);
	Actor(const OBJECT_TYPE inputType, const float x, const float y, const float vectorX, const float vectorY);
	virtual ~Actor();
	
public:
	//void SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY);
	virtual void Update(const DWORD elapsedTime);
	virtual void Draw(Renderer);

public:
	virtual void ObjectFunction(const DWORD elapsedTime);

public:
	void SetColor(const Vector4f& inputColor) ;
	void SetColor(const float red, const float green, const float blue, const float alpha);
};

