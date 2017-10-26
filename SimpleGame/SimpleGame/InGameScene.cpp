#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
	myRenderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);
	myRenderer->IsInitialized();

}

InGameScene::~InGameScene()
{
	delete myRenderer;
	m_actorArr.~vector();
}

void InGameScene::Create() {

}

void InGameScene::Update(DWORD elapsedTime) {

	for (int i = 0; i < m_sceneObjectNum; i++) {
		m_actorArr[i].Update(elapsedTime);
	}
	
	Collision();
	LifeCheck();
}

void InGameScene::Draw() {
	for (auto i : m_actorArr) {
		i.Draw(*myRenderer);
	}
}

void InGameScene::KeyProc(unsigned char key, int specKey) {

}

void InGameScene::MouseProc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		AddObject(x, y);
	}
}

void InGameScene::AddObject(int x, int y){
	if (m_sceneObjectNum < MAX_OBJECTS_COUNT) {
		m_actorArr.emplace_back((float)x, (float)y, 10, 1, 1, 1, 1, 0.3f, ((float)(rand() % 200) - 100) / 100 , ((float)(rand() % 200) -100) / 100);

		m_sceneObjectNum++;
	}
}

void InGameScene::LifeCheck() {

		for (int i = 0; i < m_sceneObjectNum; i++) {
			if (m_actorArr[i].GetLife() <= 0) {
				m_actorArr.erase(m_actorArr.begin() + i);
				m_sceneObjectNum--;
			}
		}
		
	}

void InGameScene::Collision() {
	float nowX, nowY, nowSize;
	float newX, newY, newSize;
	float disXY;
	bool isColide = true;

	for (int i = 0; i < m_sceneObjectNum; i++) {
		m_actorArr[i].SetColor(1, 1, 1, 1);
	}
	for (int i = 0; i < m_sceneObjectNum - 1; i++) {
		nowX = m_actorArr[i].GetPos().x;
		nowY = m_actorArr[i].GetPos().y;
		nowSize = m_actorArr[i].GetSize() / 2;

		for (int j = i + 1; j < m_sceneObjectNum; j++) {
			newX = m_actorArr[j].GetPos().x;
			newY = m_actorArr[j].GetPos().y;
			newSize = m_actorArr[j].GetSize() / 2;

			if (nowX - nowSize > newX + newSize) {
				isColide = false;
			}
			else if (nowX + nowSize < newX - newSize) {
				isColide = false;
			}
			else if (nowY - nowSize > newY + newSize) {
				isColide = false;
			}
			else if (nowY + nowSize < newY - newSize) {
				isColide = false;
			}
			else {
				isColide = true;
				m_actorArr[j].SetColor(1.0f, 0.0f, 0.0f, 1);
				m_actorArr[j].Damaged();
				break;
			}			
		}
		if (isColide) {
			m_actorArr[i].SetColor(1.0f, 0.0f, 0.0f, 1);
			m_actorArr[i].Damaged();
		}
	}
}