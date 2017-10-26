#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_size = 3;
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
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

