#include "stdafx.h"
#include "Actor.h"


Actor::Actor()
{
}

Actor::Actor(Pos2D pos, float size, Vector4f color, float speed, Pos2D direction) {
	m_pos = pos;
	m_size = size;
	m_color = color;
	m_speed = speed;
	m_dirVector = direction;
}

Actor::Actor(float x, float y, float size, Vector4f color, float speed, float vectorX, float vectorY) {
	m_pos.x = x;
	m_pos.y = y;
	m_size = size;
	m_color = color;
	m_speed = speed;

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
}
Actor::Actor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY) {
	m_pos.x = x;
	m_pos.y = y;
	m_size = size;
	m_color.x = colorR;
	m_color.y = colorG;
	m_color.z = colorB;
	m_color.a = colorAlpha;

	m_speed = speed;

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
}


Actor::~Actor()
{
	Object::~Object();
}

void Actor::Move(Direction dir) {
	if (dir == Direction::Up) {
		SetPos(0, m_speed);
	}
	else if (dir == Direction::Down) {
		SetPos(0, -m_speed);
	}
	else if (dir == Direction::Left) {
		SetPos(-m_speed , 0);
	}
	else if (dir == Direction::Right) {
		SetPos(m_speed, 0);
	}
}

void Actor::Move() {
	m_pos.x = m_pos.x + m_dirVector.x * m_speed;
	m_pos.y = m_pos.y + m_dirVector.y * m_speed;
}

void Actor::SetSpeed(float speed) {
	m_speed = speed;
}

