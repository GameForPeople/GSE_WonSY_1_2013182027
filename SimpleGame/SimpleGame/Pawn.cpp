#include "stdafx.h"
#include "Pawn.h"


Pawn::Pawn()
{
}

Pawn::~Pawn()
{
	Actor::~Actor();
}

Pawn::Pawn(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y) : Actor (inputType, team, x, y) {

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

	m_animCount = 0;
	m_animTimer = 0;
	m_paticleTime = 0;
}

Pawn::Pawn(OBJECT_TYPE inputType, const TEAM_TYPE team, float x, float y, float vectorX, float vectorY) : Actor(inputType, team, x, y) {

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
	m_animCount = 0 ;
	m_animTimer = 0 ;
	m_paticleTime = 0;
}

Pawn::Pawn(OBJECT_TYPE inputType, const TEAM_TYPE team, float x, float y, float vectorX, float vectorY, int inputOwner) : Actor(inputType, team, x, y) {

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

	m_animCount = 0;
	m_animTimer = 0;
	m_paticleTime = 0;
}

void Pawn::Update(const DWORD elapsedTime) {
	Move(elapsedTime);
	LimitMove();
	//ObjectFunction(elapsedTime);
	Animation();
}

void Pawn::UpdatePaticle(const DWORD elapsedTime) {
	m_paticleTime += (float)(elapsedTime / 2000.0f);
}

void Pawn::Animation() {
	m_animTimer++;
	if (m_animTimer >= 60) {
		m_animTimer = 0;

		m_animCount++;

		if (m_animCount >= 3) {
			m_animCount = 0;
		}
	}

	if (m_dirVector.x * m_dirVector.x >= m_dirVector.y * m_dirVector.y) {
		if (m_dirVector.x > 0)
			m_animDirection = 2;
		else
			m_animDirection = 1;
	}
	else {
		if (m_dirVector.y > 0)
			m_animDirection = 3;
		else
			m_animDirection = 0;
	}
}

//void Pawn::Draw(Renderer g_Renderer) {
//	if(m_type == OBJECT_TYPE::OBJECT_BUILDING)
//		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_BUILDING);
//	else if (m_type == OBJECT_TYPE::OBJECT_CHARACTER) {
//		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_CHARACTER);
//	}
//	else if (m_type == OBJECT_TYPE::OBJECT_ARROW)
//		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_ARROW);
//	else if (m_type == OBJECT_TYPE::OBJECT_BULLET)
//		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_BULLET);
//
//	DrawLife(g_Renderer);
//}

void Pawn::Draw(Renderer& g_Renderer) {
	if (m_type == OBJECT_TYPE::OBJECT_BUILDING)
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_BUILDING);
	else if (m_type == OBJECT_TYPE::OBJECT_CHARACTER) {
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_CHARACTER);
	}
	else if (m_type == OBJECT_TYPE::OBJECT_ARROW)
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_ARROW);
	else if (m_type == OBJECT_TYPE::OBJECT_BULLET)
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a, DRAW_LEVEL_BULLET);

	DrawLife(g_Renderer);
}

void Pawn::DrawLife(Renderer& g_Renderer) {

	if (m_type == OBJECT_TYPE::OBJECT_BUILDING)
		g_Renderer.DrawSolidRectGauge(m_pos.x, m_pos.y + m_size, 0, m_size, 5, m_color.x, m_color.y, m_color.z, m_color.a, (float)m_life / (float)BUILDING_BASE_LIFE, DRAW_LEVEL_BUILDING - 0.01f);
	else if (m_type == OBJECT_TYPE::OBJECT_CHARACTER)								 
		g_Renderer.DrawSolidRectGauge(m_pos.x , m_pos.y + m_size, 0, m_size, 5, m_color.x, m_color.y, m_color.z, m_color.a, (float)m_life / (float)CHARACTER_BASE_LIFE, DRAW_LEVEL_CHARACTER - 0.01f);
	//else if (m_type == OBJECT_TYPE::OBJECT_ARROW)									 
	//	g_Renderer.DrawSolidRectGauge(m_pos.x , m_pos.y + m_size, 0, m_size, 3, m_color.x, m_color.y, m_color.z, m_color.a, (float)m_life / (float)ARROW_BASE_LIFE, DRAW_LEVEL_LIFE);
	//else if (m_type == OBJECT_TYPE::OBJECT_BULLET)									 
	//	g_Renderer.DrawSolidRectGauge(m_pos.x , m_pos.y + m_size, 0, m_size, 3, m_color.x, m_color.y, m_color.z, m_color.a, (float)m_life / (float)BULLET_BASE_LIFE, DRAW_LEVEL_LIFE);
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

	if (m_pos.x < -CLIENT_WIDTH / 2 || m_pos.x >	CLIENT_WIDTH / 2) {
		m_dirVector.x *= -1;

		if (m_pos.x < -CLIENT_WIDTH / 2) {
			m_pos.x = -CLIENT_WIDTH / 2;
		}
		else if (m_pos.x >	CLIENT_WIDTH / 2) {
			m_pos.x = CLIENT_WIDTH / 2;
		}
	}

	if (m_pos.y < -CLIENT_HEIGHT / 2 || m_pos.y > 	CLIENT_HEIGHT / 2) {
		m_dirVector.y *= -1;

		if (m_pos.y < -CLIENT_HEIGHT / 2) {
			m_pos.y = -CLIENT_HEIGHT / 2;
		}
		else if (m_pos.y > 	CLIENT_HEIGHT / 2) {
			m_pos.y = CLIENT_HEIGHT / 2;
		}
	}
}

void Pawn::OutMoveDeath() {

	if (m_pos.x < -CLIENT_WIDTH / 2 || m_pos.x >	CLIENT_WIDTH / 2) {
		m_life = 0;
	}

	if (m_pos.y < -CLIENT_HEIGHT / 2 || m_pos.y > 	CLIENT_HEIGHT / 2) {
		m_life = 0;
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
