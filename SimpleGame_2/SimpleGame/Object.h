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

struct Vector4f {
	float x;
	float y;
	float z;
	float a;
};

class Object
{
protected:
	Pos2D m_pos;
	Vector4f m_color;
	float m_size;
	
public:
	Object();
	virtual ~Object();
	

	void SetColor(Vector4f& inputColor);
	void SetPos(float x, float y);

	virtual void Update();
	virtual void Draw(Renderer&);
};

