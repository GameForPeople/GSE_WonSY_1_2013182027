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
	Pos2D			m_pos;
	Vector4f		m_color;
	float			m_size;
	
	int				m_life{ 0 };
	int				m_lifeCount{};

	OBJECT_TYPE		m_type;

	int				m_objectTime{ 0 };

public:
	Object();
	Object(OBJECT_TYPE m_type);
	virtual ~Object();
	

	void SetColor(Vector4f& inputColor);
	void SetColor(float x, float y, float z, float alpha);

	void SetPos(float x, float y);

	virtual void Update();
	void Draw(Renderer);

	int GetLife() { return m_life; }
	//void UpdateLifeCount() {
	//	m_lifeCount++; 
	//	if (m_lifeCount > 100) {
	//		m_life--; m_lifeCount = 0;
	//	}
	//}
	void Damaged();
	void Damaged(int damage);
};

