#include "stdafx.h"
#include "Actor.h"

Actor::~Actor()
{
	Object::~Object();
}

Actor::Actor(const OBJECT_TYPE inputType, const TEAM_TYPE team, const float x, const float y) : Object(inputType, team, x, y) {

	if (team == TEAM_TYPE::RED_TEAM) {
		if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
			m_color = CHARACTER_RED_CLOLR;
		}
		else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
			m_color = BUILDING_BASE_CLOLR;
		}
		else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
			m_color = BULLET_RED_CLOLR;
		}
		else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
			m_color = ARROW_RED_CLOLR;
		}
	}
	else if (team == TEAM_TYPE::BLUE_TEAM) {
			if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
				m_color = CHARACTER_BLUE_CLOLR;
			}
			else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
				m_color = BUILDING_BASE_CLOLR;
			}
			else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
				m_color = BULLET_BLUE_CLOLR;
			}
			else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
				m_color = ARROW_BLUE_CLOLR;
			}
		}
}

Actor::Actor(OBJECT_TYPE inputType, TEAM_TYPE team,  Pos2D pos, Pos2D direction) : Object(inputType, team, pos.x, pos.y) {
	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_color = CHARACTER_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_color = BUILDING_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_color = BULLET_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_color = ARROW_BASE_CLOLR;
	}
}

Actor::Actor(OBJECT_TYPE inputType, TEAM_TYPE team,  float x, float y, float vectorX, float vectorY) : Object(inputType, team, x, y) {
	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_color = CHARACTER_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_color = BUILDING_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
		m_color = BULLET_BASE_CLOLR;
	}
	else if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
		m_color = ARROW_BASE_CLOLR;
	}
}

//void Actor::SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY)  {
//	m_pos.x = x;
//	m_pos.y = y;
//	m_size = size;
//	m_color.x = colorR;
//	m_color.y = colorG;
//	m_color.z = colorB;
//	m_color.a = colorAlpha;
//
//	m_speed = speed;
//
//	m_dirVector.CalCulNomalVector(vectorX, vectorY);
//
//}

void Actor::Update(const DWORD elapsedTime) {
	ObjectFunction(elapsedTime);
}

void Actor::Draw(Renderer g_Renderer) {
	g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a);
}


void Actor::ObjectFunction(const DWORD elapsedTime) {
	m_objectTime += elapsedTime;
}


void Actor::SetColor(const Vector4f& inputColor) {
	m_color = inputColor;
}

void Actor::SetColor(const float red, const float green, const float blue, const float alpha) {
	m_color.x = red;
	m_color.y = green;
	m_color.z = blue;
	m_color.a = alpha;
}



