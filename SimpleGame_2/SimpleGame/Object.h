#pragma once

#include "Renderer.h"

struct Pos2D {
	float x;
	float y;
};

struct Vector {
	float x;
	float y;
	float z;
	float a;
};

enum class Direction
{
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};

class Object
{
private:
	Pos2D m_pos;
	Vector m_color;
	float m_size;
	
public:
	Object();
	virtual ~Object();
	

	void SetColor(Vector& inputColor);

	void SetPos(float x, float y);

	virtual void Update();
	virtual void Draw(Renderer&);
};

