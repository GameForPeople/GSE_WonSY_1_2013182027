#include "stdafx.h"
#include "Pawn.h"


Pawn::Pawn()
{
}


Pawn::~Pawn()
{
	Actor::~Actor();
}

Pawn::Pawn(const OBJECT_TYPE inputType, const float x, const float y) : Actor (inputType, x, y) {

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_speed = CHARACTER_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_speed = BUILDING_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_speed = BULLET_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_speed = ARROW_BASE_SPEED;
	}

	float vectorX = rand() % 100;
	float vectorY = rand() % 100;

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
}

Pawn::Pawn(OBJECT_TYPE inputType, float x, float y, float vectorX, float vectorY) : Actor(inputType, x, y) {

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_speed = CHARACTER_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_speed = BUILDING_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_speed = BULLET_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_speed = ARROW_BASE_SPEED;
	}

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
}

Pawn::Pawn(OBJECT_TYPE inputType, float x, float y, float vectorX, float vectorY, int inputOwner) : Actor(inputType, x, y) {

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_speed = CHARACTER_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_speed = BUILDING_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_speed = BULLET_BASE_SPEED;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_speed = ARROW_BASE_SPEED;
	}

	m_dirVector.CalCulNomalVector(vectorX, vectorY);
	m_owner = inputOwner;
}

void Pawn::Update(const DWORD elapsedTime) {
	Move(elapsedTime);
	LimitMove();
	//ObjectFunction(elapsedTime);
}

void Pawn::Draw(Renderer g_Renderer) {
	g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a);
}


void Pawn::Move(const Direction dir) {
	if (dir == Direction::Up) {
		SetPos(0, m_speed);
	}
	else if (dir == Direction::Down) {
		SetPos(0, -m_speed);
	}
	else if (dir == Direction::Left) {
		SetPos(-m_speed, 0);
	}
	else if (dir == Direction::Right) {
		SetPos(m_speed, 0);
	}
}

void Pawn::Move(const DWORD elapsedTime) {
	m_pos.x = m_pos.x + m_dirVector.x * m_speed / 100 * elapsedTime * 0.1f;
	m_pos.y = m_pos.y + m_dirVector.y * m_speed / 100 * elapsedTime * 0.1f;
	//std::cout << m_pos.x << " " << m_pos.y << " " << m_speed << " " << m_dirVector.x << "  "  << m_dirVector.y << " " << std::endl;
}

void Pawn::LimitMove() {
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

void Pawn::ObjectFunction(const DWORD elapsedTime) {
	m_objectTime += elapsedTime;
}


int Pawn::GetOwner() const {
	return m_owner;
}

void Pawn::SetSpeed(const float speed) {
	m_speed = speed;
}
