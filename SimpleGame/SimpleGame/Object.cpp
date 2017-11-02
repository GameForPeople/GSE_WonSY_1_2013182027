#include "stdafx.h"
#include "Object.h"

Object::Object()
{

}

Object::Object(OBJECT_TYPE inputType)
{
	m_type = inputType;
	if (inputType == OBJECT_TYPE::OBJECT_CHARACTER) {
		m_life = 10;
		m_size = 10;
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}	
	else 
		if (inputType == OBJECT_TYPE::OBJECT_BUILDING) {
		m_life = 500;
		m_size = 50;
		m_color = { 1.0f, 1.0f, 0.0f, 1.0f };
	}
	else 	
		if (inputType == OBJECT_TYPE::OBJECT_BULLET) {
			m_life = 20;
			m_size = 2;
			m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}
	else 	
		if (inputType == OBJECT_TYPE::OBJECT_ARROW) {
			m_life = 10;
			m_size = 2;
			m_color = { 0.0f, 1.0f, 0.0f, 1.0f };
	}

	m_objectTime = 0;
}

Object::~Object()
{
}

void Object::Draw(Renderer g_Renderer) {
	g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, 0, m_size, m_color.x, m_color.y, m_color.z, m_color.a);
}

void Object::SetColor(Vector4f& inputColor) {
	m_color = inputColor;
}

void Object::SetColor(float x, float y, float z, float alpha) {
	m_color.x = x;
	m_color.y = y;
	m_color.z = z;
	m_color.a = alpha;

}

void Object::SetPos(float x, float y) {
	m_pos.x += x;
	m_pos.y += y;
}

void Object::Update() {

}

void Object::Damaged() {
	m_life--;
}

void Object::Damaged(int inputDamage) {
	if (inputDamage == -1)
		m_life = 0;
	else 
		m_life -= inputDamage;
}