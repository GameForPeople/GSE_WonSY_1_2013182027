#include "stdafx.h"
#include "Actor.h"


Actor::Actor()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_size = 5;
	m_color.x = 1;
	m_color.y = 1;
	m_color.z = 1;
	m_color.a = 1;

	m_speed = 0.1;

	m_dirVector.CalCulNomalVector(0.5, 0.5);
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

void Actor::SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY) {
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

void Actor::Update() {
	this->Move();
	this->LimitMove();
}

void Actor::Move() {
	m_pos.x = m_pos.x + m_dirVector.x * m_speed;
	m_pos.y = m_pos.y + m_dirVector.y * m_speed;

	//std::cout << m_pos.x << " " << m_pos.y << " " << m_speed << " " << m_dirVector.x << "  "  << m_dirVector.y << " " << std::endl;
}

void Actor::SetSpeed(float speed) {
	m_speed = speed;
}

void Actor::LimitMove() {
	if (m_pos.x <= -250 || m_pos.x >= 250) {
		m_dirVector.x *= -1;
	}

	if (m_pos.y <= -250 || m_pos.y >= 250) {
		m_dirVector.y *= -1;
	}
}

