#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
	myRenderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);
	myRenderer->IsInitialized();

	BuildObject();
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
	
	for (int i = 0; i < m_bulletArr.size(); i++) {
		m_bulletArr[i].Move(elapsedTime);
		m_bulletArr[i].LimitMove();
	}
	
	for (int i = 0; i < m_buildingArr.size(); i++) {
		m_buildingArr[i].ObjectFunction(elapsedTime);
	}

	if (m_buildingArr[0].GetObejctTime() >= BULLET_RESPAWN_TIME) {
			m_bulletArr.emplace_back(OBJECT_TYPE::OBJECT_BULLET, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, rand() % 100, rand() % 100);
			m_buildingArr[0].SetObjectTime(0);
	}

	Collision();
	LifeCheck();
	
	//if(m_sceneObjectNum)
	//std::cout << m_actorArr[0].GetLife() << std::endl;
}

void InGameScene::Draw() {
	for (auto i : m_actorArr) {
		i.Draw(*myRenderer);
	}

	for (auto i : m_buildingArr) {
		i.Draw(*myRenderer);
	}

	for (int i = 0; i < m_bulletArr.size(); i++) {
		m_bulletArr[i].Draw(*myRenderer);
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
		m_actorArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, (float)x, (float)y, ((float)(rand() % 200) - 100) / 100 , ((float)(rand() % 200) -100) / 100);

		m_sceneObjectNum++;
	}
}

void InGameScene::BuildObject() {
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, 0, 0, 0, 0);
}

void InGameScene::LifeCheck() {

		for (int i = 0; i < m_sceneObjectNum; i++) {
			if (m_actorArr[i].GetLife() <= 0) {
				m_actorArr.erase(m_actorArr.begin() + i);
				m_sceneObjectNum--;
			}
		}

		for (int i = 0; i < m_buildingArr.size(); i++) {
			if (m_buildingArr[i].GetLife() <= 0) {
				m_buildingArr.erase(m_buildingArr.begin() + i);
			}
		}

		for (int i = 0; i < m_bulletArr.size(); i++) {
			if (m_bulletArr[i].GetLife() <= 0) {
				m_bulletArr.erase(m_bulletArr.begin() + i);
			}
		}
	}

void InGameScene::Collision() {
	float nowX, nowY, nowSize;
	float newX, newY, newSize;
	float disXY;
	bool isColide = true;

#pragma region [Player X Player]
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
				break;
			}			
		}

		if (isColide) {
			m_actorArr[i].SetColor(1.0f, 0.0f, 0.0f, 1);
		}
	}
#pragma endregion

#pragma region [Player X Bullet]

	for (int i = 0; i < m_sceneObjectNum - 1; i++) {
		nowX = m_actorArr[i].GetPos().x;
		nowY = m_actorArr[i].GetPos().y;
		nowSize = m_actorArr[i].GetSize() / 2;

		for (int j = 0; j <  m_bulletArr.size(); j++) {
			newX = m_bulletArr[j].GetPos().x;
			newY = m_bulletArr[j].GetPos().y;
			newSize = m_bulletArr[j].GetSize() / 2;

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
				m_actorArr[i].Damaged(m_bulletArr[j].GetLife());
				m_bulletArr[j].Damaged(-1);
				break;
			}
		}

		if (isColide) {
			m_actorArr[i].SetColor(1.0f, 0.0f, 1.0f, 1);
		}
	}
#pragma endregion

#pragma region [Building X Player]
	for (int j = 0; j < m_buildingArr.size(); j++) {
		m_buildingArr[j].SetColor(1.0f, 1.0f, 0, 1.0f);
	}

	for (int i = 0; i < m_sceneObjectNum ; i++) {
		nowX = m_actorArr[i].GetPos().x;
		nowY = m_actorArr[i].GetPos().y;
		nowSize = m_actorArr[i].GetSize() / 2;

		for (int j = 0; j < m_buildingArr.size(); j++) {
			newX = m_buildingArr[j].GetPos().x;
			newY = m_buildingArr[j].GetPos().y;
			newSize = m_buildingArr[j].GetSize() / 2;

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
				m_buildingArr[j].SetColor(1.0f, 0.0f, 0.0f, 1);
				m_buildingArr[j].Damaged(m_actorArr[i].GetLife());
				m_actorArr[i].Damaged(-1);
				break;
			}
		}
	}
#pragma endregion
}