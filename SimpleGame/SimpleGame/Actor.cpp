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

Actor::Actor(OBJECT_TYPE inputType, Pos2D pos, Pos2D direction) : Object(inputType) {
	m_pos = pos;

	m_dirVector = direction;

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_speed = 300;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_speed = 0;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_speed = 400;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_speed = 100;
	}

}

Actor::Actor(OBJECT_TYPE inputType, float x, float y, float vectorX, float vectorY) : Object(inputType) {
	m_pos.x = x;
	m_pos.y = y;

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_speed = 300;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_speed = 0;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_speed = 600;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_speed = 100;
	}

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
}

void Actor::SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY)  {
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

void Actor::Update(DWORD elapsedTime) {
	Move(elapsedTime);
	LimitMove();
	ObjectFunction(elapsedTime);
}
void Actor::ObjectFunction(DWORD elapsedTime) {
	m_objectTime += elapsedTime;
}

void Actor::Move(DWORD elapsedTime) {
	m_pos.x = m_pos.x + m_dirVector.x * m_speed / 100 * elapsedTime * 0.1f;
	m_pos.y = m_pos.y + m_dirVector.y * m_speed / 100 * elapsedTime * 0.1f;
	//std::cout << m_pos.x << " " << m_pos.y << " " << m_speed << " " << m_dirVector.x << "  "  << m_dirVector.y << " " << std::endl;
}

void Actor::SetSpeed(float speed) {
	m_speed = speed;
}

void Actor::Draw(Renderer g_Renderer) {
	g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a);


}


Pos2D Actor::GetPos() {
	return m_pos;
}

float Actor::GetSize() {
	return m_size;
}

void Actor::LimitMove() {
	if (m_pos.x < -250 || m_pos.x > 250) {
		m_dirVector.x *= -1;

		if (m_pos.x < -250) {
			m_pos.x = -250;
		}
		else if (m_pos.x > 250) {
			m_pos.x = 250;
		}
	}

	if (m_pos.y < -250 || m_pos.y > 250) {
		m_dirVector.y *= -1;

		if (m_pos.y < -250) {
			m_pos.y = -250;
		}
		else if (m_pos.y > 250) {
			m_pos.y = 250;
		}
	}
}

