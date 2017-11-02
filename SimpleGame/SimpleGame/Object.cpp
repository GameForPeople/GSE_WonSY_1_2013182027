#include "stdafx.h"
#include "Object.h"

Object::Object(OBJECT_TYPE inputType, float posX, float posY)
{
	m_pos.x = posX;
	m_pos.y = posY;

	m_type = inputType;

	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
			m_life = CHARACTER_BASE_LIFE;
			m_size = CHARACTER_BASE_SIZE;
	}	
	else 
		if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
			m_life = BUILDING_BASE_LIFE;
			m_size = BUILDING_BASE_SIZE;
	}
	else 	
		if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
			m_life = BULLET_BASE_LIFE;
			m_size = BULLET_BASE_SIZE;
	}
	else 	
		if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
			m_life = ARROW_BASE_LIFE;
			m_size = ARROW_BASE_SIZE;
	}

	m_objectTime = 0;
}

void Object::Update() {

}

void Object::Damaged() {
	m_life--;
}

void Object::Damaged(const int inputDamage) {
	if (inputDamage == -1)
		m_life = 0;
	else 
		m_life -= inputDamage;
}

void Object::ObjectFunction(const DWORD elapsedTime) {
	m_objectTime += elapsedTime;
}



Pos2D Object::GetPos() const{
	return m_pos;
}

int Object::GetObejctTime() const {
	return m_objectTime;
}

int Object::GetLife() const { 
	return m_life; 
}

float Object::GetSize() const {
	return m_size;
}


void Object::SetPos(const float x, const float y) {
	m_pos.x += x;
	m_pos.y += y;
}

void Object::SetObjectTime(const int inputTime) {
	m_objectTime = inputTime;
}
