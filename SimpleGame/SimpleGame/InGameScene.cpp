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
	m_pawnArr.~vector();
	m_buildingArr.~vector();
	m_bulletArr.~vector();
}

void InGameScene::Create() {

}

void InGameScene::BuildObject() {
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, 0, 0, 0, 0);
}



void InGameScene::Update(const DWORD elapsedTime) {

	for (int i = 0; i < m_pawnArr.size(); i++) {
		m_pawnArr[i].Update(elapsedTime);
	}

	//for (auto i : m_pawnArr)
	//	i.Update(elapsedTime);
	
	for (int i = 0; i < m_bulletArr.size(); i++) {
		m_bulletArr[i].Move(elapsedTime);
		m_bulletArr[i].LimitMove();
	}
	
	for (int i = 0; i < m_buildingArr.size(); i++) {
		m_buildingArr[i].ObjectFunction(elapsedTime);
	}

	if(m_buildingArr.size())
		if (m_buildingArr[0].GetObejctTime() >= BULLET_RESPAWN_TIME) {
			m_bulletArr.emplace_back(OBJECT_TYPE::OBJECT_BULLET, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, rand() % 100, rand() % 100);
			m_buildingArr[0].SetObjectTime(0);
		}

	Collision();
	RemoveZombie();
}

void InGameScene::Draw() {
	for (auto i : m_pawnArr) {
		i.Draw(*myRenderer);
	}

	for (auto i : m_buildingArr) {
		i.Draw(*myRenderer);
	}

	for (auto i : m_bulletArr) {
		i.Draw(*myRenderer);
	}
}



void InGameScene::KeyProc(const unsigned char key, const int specKey) {

}

void InGameScene::MouseProc(const int button, const int state, const int x, const int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		AddBasePawn(x, y);
	}
}




void InGameScene::AddBasePawn(const int x, const int y){
	if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
		m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, (float)x, (float)y, ((float)(rand() % 200) - 100) / 100 , ((float)(rand() % 200) -100) / 100);
	}
}

void InGameScene::RemoveZombie() {

		if(m_pawnArr.size())
			for (int i = 0; i < m_pawnArr.size(); i++) {
				if (m_pawnArr[i].GetLife() <= 0) {
					m_pawnArr.erase(m_pawnArr.begin() + i);
				}
			}

		if (m_buildingArr.size())
		for (int i = 0; i < m_buildingArr.size(); i++) {
			if (m_buildingArr[i].GetLife() <= 0) {
				m_buildingArr.erase(m_buildingArr.begin() + i);
			}
		}

		if (m_bulletArr.size())
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
	if (m_pawnArr.size()) {
		for (int i = 0; i < m_pawnArr.size(); i++) {
			m_pawnArr[i].SetColor(1, 1, 1, 1);
		}

		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = i + 1; j < m_pawnArr.size(); j++) {
				newX = m_pawnArr[j].GetPos().x;
				newY = m_pawnArr[j].GetPos().y;
				newSize = m_pawnArr[j].GetSize() / 2;

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
					m_pawnArr[j].SetColor(1.0f, 0.0f, 0.0f, 1);
					break;
				}
			}

			if (isColide) {
				m_pawnArr[i].SetColor(1.0f, 0.0f, 0.0f, 1);
			}
		}
	}
#pragma endregion

#pragma region [Player X Bullet]
	if (m_pawnArr.size() && m_bulletArr.size()) {
		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_bulletArr.size(); j++) {
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
					m_pawnArr[i].Damaged(m_bulletArr[j].GetLife());
					m_bulletArr[j].Damaged(-1);
					break;
				}
			}

			if (isColide) {
				m_pawnArr[i].SetColor(1.0f, 0.0f, 1.0f, 1);
			}
		}
	}
#pragma endregion

#pragma region [Playe X Building]
	if (m_pawnArr.size() && m_pawnArr.size()) {
		for (int j = 0; j < m_buildingArr.size(); j++) {
			m_buildingArr[j].SetColor(1.0f, 1.0f, 0, 1.0f);
		}

		for (int i = 0; i < m_pawnArr.size(); i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

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
					m_buildingArr[j].Damaged(m_pawnArr[i].GetLife());
					m_pawnArr[i].Damaged(-1);
					break;
				}
			}
		}
	}
#pragma endregion


}