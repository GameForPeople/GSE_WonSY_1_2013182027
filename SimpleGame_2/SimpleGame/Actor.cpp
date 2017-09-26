#include "stdafx.h"
#include "Actor.h"


Actor::Actor()
{
	Object::Object();
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

void Actor::SetSpeed(float speed) {
	m_speed = speed;
}

