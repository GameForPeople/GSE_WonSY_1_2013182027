#include "stdafx.h"
#include "Framework.h"

Framework::Framework()
{
	m_sceneArr = new InGameScene();
}

Framework::~Framework()
{
	delete m_sceneArr;
}

void Framework::Create() {
	
}

void Framework::Update(const DWORD elapsedTime) {
	m_sceneArr->Update(elapsedTime);
}

void Framework::Draw() {
	m_sceneArr->Draw();
}

void Framework::KeyProc(const unsigned char key, const int specKey) {
	m_sceneArr->KeyProc(key, specKey);
}

void Framework::MouseProc(const int button, const int state, const int x, const int y) {
	m_sceneArr->MouseProc(button, state, x, y);
}
