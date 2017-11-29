#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
	myRenderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);
	myRenderer->IsInitialized();

	BuildObject();

	std::cout << std::endl << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "  게임 소프트 웨어 공학 프로젝트 SimpleGame   :  2013182027 원성연" << std::endl;
	std::cout << "빠른 실습 검사를 위해 오브젝트 리스폰 타임을 많이 감소시켰습니다." << std::endl;
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
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, 150, 200);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, 0, 200);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, -150, 200);

	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, 150, -200);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, 0, -200);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, -150, -200);

	//Red
	m_buildingTextureArr[0] = myRenderer->CreatePngTexture("./Resources/Textures/Building_1.png");
	//Blue
	m_buildingTextureArr[1] = myRenderer->CreatePngTexture("./Resources/Textures/Building_2.png");


	m_ownerArrow = 0;
}


void InGameScene::Update(const DWORD elapsedTime) {

	for (int i = 0; i < m_pawnArr.size(); i++) {
		m_pawnArr[i].Update(elapsedTime);
		m_pawnArr[i].ObjectFunction(elapsedTime);
	}
	
	for (int i = 0; i < m_bulletArr.size(); i++) {
		m_bulletArr[i].Move(elapsedTime);
		m_bulletArr[i].OutMoveDeath();
	}

	for (int i = 0; i < m_arrowArr.size(); i++) {
		m_arrowArr[i].Move(elapsedTime);
		m_arrowArr[i].OutMoveDeath();
	}
	
	for (int i = 0; i < m_buildingArr.size(); i++) {
		m_buildingArr[i].ObjectFunction(elapsedTime);
	}

	for (int i = 0; i < m_buildingArr.size(); i++)
		if (m_buildingArr[i].GetObejctTime() >= BULLET_RESPAWN_TIME) {
			m_bulletArr.emplace_back(OBJECT_TYPE::OBJECT_BULLET, m_buildingArr[i].GetTeam() ,m_buildingArr[i].GetPos().x, m_buildingArr[i].GetPos().y, rand() % 100 - 50, rand() % 100 - 50);
			m_buildingArr[i].SetObjectTime(0);
		}

	if (m_pawnArr.size())
		for(int i = 0; i < m_pawnArr.size(); i++)
		if (m_pawnArr[i].GetObejctTime() >= BULLET_RESPAWN_TIME) {
			m_arrowArr.emplace_back(OBJECT_TYPE::OBJECT_ARROW, m_pawnArr[i].GetTeam(), m_pawnArr[i].GetPos().x, m_pawnArr[i].GetPos().y, rand() % 100 - 50, rand() % 100 - 50, m_pawnArr[i].GetOwner());
			m_pawnArr[i].SetObjectTime(0);
		}

	Collision();
	RemoveZombie();
	
	AddRedPawn();

	m_redAutoTime++;
	m_blueTime++;
}

void InGameScene::Draw() {
	for (auto i : m_pawnArr) {
		i.Draw(*myRenderer);
	}

	//for (auto i : m_buildingArr) {
	//	i.Draw(*myRenderer);
	//}

	//if(m_buildingArr.size())
	//myRenderer->DrawTexturedRect(
	//	m_buildingArr[0].GetPos().x,
	//	m_buildingArr[0].GetPos().y,
	//	0, 
	//	m_buildingArr[0].GetSize(),
	//	1, 
	//	1, 
	//	1, 
	//	1, 
	//	m_buildingTextureArr[0]
	//);

	for (auto i : m_buildingArr) {
		if(i.GetTeam() == TEAM_TYPE::RED_TEAM)
			myRenderer->DrawTexturedRect(
				i.GetPos().x,
				i.GetPos().y,
				0, 
				i.GetSize(),
				1, 
				1, 
				1, 
				1, 
				m_buildingTextureArr[1],
				DRAW_LEVEL_BUILDING
			);
		else if (i.GetTeam() == TEAM_TYPE::BLUE_TEAM)
			myRenderer->DrawTexturedRect(
				i.GetPos().x,
				i.GetPos().y,
				0,
				i.GetSize(),
				1,
				1,
				1,
				1,
				m_buildingTextureArr[0],
				DRAW_LEVEL_BUILDING
			);

		i.DrawLife(*myRenderer);
	}



	for (auto i : m_bulletArr) {
		i.Draw(*myRenderer);
	}

	for (auto i : m_arrowArr) {
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


void InGameScene::AddRedPawn() {
	if (m_redAutoTime >= RED_AUTO_RESPAWN_TIME) {
		int x = rand() % CLIENT_WIDTH - CLIENT_WIDTH / 2;
		int y = rand() % (CLIENT_HEIGHT / 2);

		if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
			m_ownerArrow++;
			m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, (float)x, (float)y, ((float)(rand() % 200) - 100) / 100, ((float)(rand() % 200) - 100) / 100, m_ownerArrow);
		}
		m_redAutoTime = 0;
	}
}

void InGameScene::AddBasePawn(const int x, const int y){
	if (m_blueTime >= BLUE_RESPAWN_LIMIT_TIME && y < 0 ) {
		if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
			m_ownerArrow++;
			m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, (float)x, (float)y, ((float)(rand() % 200) - 100) / 100, ((float)(rand() % 200) - 100) / 100, m_ownerArrow);
		}
		m_blueTime = 0;
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

		if (m_arrowArr.size())
			for (int i = 0; i < m_arrowArr.size(); i++) {
				if (m_arrowArr[i].GetLife() <= 0) {
					m_arrowArr.erase(m_arrowArr.begin() + i);
				}
			}
	}

void InGameScene::Collision() {
	float nowX, nowY, nowSize;
	float newX, newY, newSize;
	float disXY;
	bool isColide = true;

#pragma region [TEAM::BUILDING X BULLET]
	if (m_bulletArr.size()) {
		for (int i = 0; i < m_bulletArr.size(); i++) {
			nowX = m_bulletArr[i].GetPos().x;
			nowY = m_bulletArr[i].GetPos().y;
			nowSize = m_bulletArr[i].GetSize() / 2;

			for (int j = 0; j < m_buildingArr.size(); j++) {
				if (m_bulletArr[i].GetTeam() != m_buildingArr[j].GetTeam()) {
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
						m_buildingArr[j].Damaged(m_bulletArr[i].GetLife());
						m_bulletArr[i].Damaged(-1);
						break;
					}
				}
			}

		}
	}
#pragma endregion


#pragma region [TEAM::Player X Building]
	if (m_pawnArr.size() && m_pawnArr.size()) {
		for (int i = 0; i < m_pawnArr.size(); i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_buildingArr.size(); j++) {
				if (m_buildingArr[j].GetTeam() != m_pawnArr[i].GetTeam()) {
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
						m_buildingArr[j].Damaged(m_pawnArr[i].GetLife());
						m_pawnArr[i].Damaged(-1);
						break;
					}
				}
			}
		}
	}
#pragma endregion


#pragma region [TEAM::Player X Arrow]
	if (m_pawnArr.size() && m_arrowArr.size()) {
		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_arrowArr.size(); j++) {
				if (m_arrowArr[j].GetTeam() != m_pawnArr[i].GetTeam()) {
					newX = m_arrowArr[j].GetPos().x;
					newY = m_arrowArr[j].GetPos().y;
					newSize = m_arrowArr[j].GetSize() / 2;

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
						m_pawnArr[i].Damaged(m_arrowArr[j].GetLife());
						m_arrowArr[j].Damaged(-1);
						break;
					}
				}
			}
		}
	}
#pragma endregion

#pragma region [TEAM::Player X Bullet]
	if (m_pawnArr.size() && m_bulletArr.size()) {
		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x;
			nowY = m_pawnArr[i].GetPos().y;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_bulletArr.size(); j++) {
				if (m_pawnArr[i].GetTeam() != m_bulletArr[j].GetTeam()) {
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
			}
		}
	}
#pragma endregion

#pragma region [TEAM::Player X Player]
	//if (m_pawnArr.size()) {
	//
	//	for (int i = 0; i < m_pawnArr.size() - 1; i++) {
	//		nowX = m_pawnArr[i].GetPos().x;
	//		nowY = m_pawnArr[i].GetPos().y;
	//		nowSize = m_pawnArr[i].GetSize() / 2;
	//
	//		for (int j = i + 1; j < m_pawnArr.size(); j++) {
	//			if (m_pawnArr[i].GetTeam() != m_pawnArr[j].GetTeam()) {
	//				newX = m_pawnArr[j].GetPos().x;
	//				newY = m_pawnArr[j].GetPos().y;
	//				newSize = m_pawnArr[j].GetSize() / 2;
	//
	//				if (nowX - nowSize > newX + newSize) {
	//					isColide = false;
	//				}
	//				else if (nowX + nowSize < newX - newSize) {
	//					isColide = false;
	//				}
	//				else if (nowY - nowSize > newY + newSize) {
	//					isColide = false;
	//				}
	//				else if (nowY + nowSize < newY - newSize) {
	//					isColide = false;
	//				}
	//				else {
	//					isColide = true;
	//					int lifeBuf = m_pawnArr[j].GetLife();
	//					m_pawnArr[j].Damaged(m_pawnArr[i].GetLife());
	//					m_pawnArr[i].Damaged(lifeBuf);
	//					break;
	//				}
	//			}
	//
	//		}
	//	}
	//}
#pragma endregion

#pragma region [TEAM::Building X Arrow]
	if (m_arrowArr.size() && m_arrowArr.size()) {

		for (int i = 0; i <m_arrowArr.size(); i++) {
			nowX = m_arrowArr[i].GetPos().x;
			nowY = m_arrowArr[i].GetPos().y;
			nowSize = m_arrowArr[i].GetSize() / 2;

			for (int j = 0; j < m_buildingArr.size(); j++) {
				if (m_arrowArr[i].GetTeam() != m_buildingArr[j].GetTeam()) {
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
						m_buildingArr[j].Damaged(m_arrowArr[i].GetLife());
						m_arrowArr[i].Damaged(-1);
						break;
					}
				}
			}
		}
	}
#pragma endregion

}