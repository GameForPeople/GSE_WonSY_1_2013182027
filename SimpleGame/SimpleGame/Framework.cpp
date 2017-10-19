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

void Framework::Update() {
	m_sceneArr->Update();
}

void Framework::Draw() {
	m_sceneArr->Draw();
}

void Framework::KeyProc(unsigned char key, int specKey) {
	m_sceneArr->KeyProc(key, specKey);
}

void Framework::MouseProc(int button, int state, int x, int y) {
	m_sceneArr->MouseProc(button, state, x, y);
}
