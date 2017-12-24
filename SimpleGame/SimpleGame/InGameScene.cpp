#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
	myRenderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);
	myRenderer->IsInitialized();

	BuildObject();

	m_paticleTime = 0;
	m_globalPaticleTime = 0;

	std::cout << std::endl << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "  게임 소프트 웨어 공학 프로젝트 SimpleGame   :  2013182027 원성연" << std::endl;
	std::cout << "  렌더러가 터지는 문제 수정했습니다.." << std::endl;
	std::cout << "  글로벌 파티클이 아닌 객체별 파티클타임은 객체 내부에서 확인 가능합니다. 감사합니다." << std::endl;

	m_sound = new Sound();
	m_bgSound = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");

	m_sound->PlaySound(m_bgSound, false, 0.2f);
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
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, 130, 235, 0);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, 0, 290, 1);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::RED_TEAM, -130, 235, 2);

	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, 130, -110, 3);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, 0, -160, 4);
	m_buildingArr.emplace_back(OBJECT_TYPE::OBJECT_BUILDING, TEAM_TYPE::BLUE_TEAM, -130, -110, 5);

	//Red
	m_buildingTextureArr[0] = myRenderer->CreatePngTexture("./Resources/Textures/Building_1_BLUE.png");
	//Blue
	m_buildingTextureArr[1] = myRenderer->CreatePngTexture("./Resources/Textures/Building_2_RED.png");

	m_backImg = myRenderer->CreatePngTexture("./Resources/Textures/BackImg_5.png");
	
	m_animImg[0][0] = myRenderer->CreatePngTexture("./Resources/Textures/RedDog_1.png");
	m_animImg[0][1] = myRenderer->CreatePngTexture("./Resources/Textures/RedDog_2.png");
	m_animImg[0][2] = myRenderer->CreatePngTexture("./Resources/Textures/RedDog_3.png");

	m_animImg[1][0] = myRenderer->CreatePngTexture("./Resources/Textures/BlueDog_1.png");
	m_animImg[1][1] = myRenderer->CreatePngTexture("./Resources/Textures/BlueDog_2.png");
	m_animImg[1][2] = myRenderer->CreatePngTexture("./Resources/Textures/BlueDog_3.png");

	m_paticleImg[0] = myRenderer->CreatePngTexture("./Resources/Textures/Paticle_Red.png");
	m_paticleImg[1] = myRenderer->CreatePngTexture("./Resources/Textures/Paticle_Blue.png");

	m_globalPaticleImg[0] = myRenderer->CreatePngTexture("./Resources/Textures/Paticle_Snow.png");
	m_globalPaticleImg[1] = myRenderer->CreatePngTexture("./Resources/Textures/Paticle_Rain.png");

	m_endImg = myRenderer->CreatePngTexture("./Resources/Textures/GameEnd.png");

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
		m_bulletArr[i].UpdatePaticle(elapsedTime);
	}

	for (int i = 0; i < m_arrowArr.size(); i++) {
		m_arrowArr[i].Move(elapsedTime);
		m_arrowArr[i].OutMoveDeath();
		m_arrowArr[i].ObjectFunction(elapsedTime);
	}
	
	for (int i = 0; i < m_buildingArr.size(); i++) {
		if(m_buildingArr[i].GetLife())
			m_buildingArr[i].ObjectFunction(elapsedTime);
	}

	if (m_buildingArr[1].GetObejctTime() >= BULLET_RESPAWN_TIME) {
			m_bulletArr.emplace_back(OBJECT_TYPE::OBJECT_BULLET, m_buildingArr[1].GetTeam() ,m_buildingArr[1].GetPos().x, m_buildingArr[1].GetPos().y, rand() % 100 - 50, -25);
			m_buildingArr[1].SetObjectTime(0);
	}

	if (m_buildingArr[4].GetObejctTime() >= BULLET_RESPAWN_TIME) {
		m_bulletArr.emplace_back(OBJECT_TYPE::OBJECT_BULLET, m_buildingArr[4].GetTeam(), m_buildingArr[4].GetPos().x, m_buildingArr[4].GetPos().y, rand() % 100 - 50, 25);
		m_buildingArr[4].SetObjectTime(0);
	}
	
	if (m_pawnArr.size()) {
		for (int i = 0; i < m_pawnArr.size(); i++)
			if (m_pawnArr[i].GetObejctTime() >= ARROW_RESPAWN_TIME && m_pawnArr[i].m_weapon == WEAPON_TYPE::ARROW) {
				if (m_pawnArr[i].GetTeam() == TEAM_TYPE::BLUE_TEAM)
					m_arrowArr.emplace_back(OBJECT_TYPE::OBJECT_ARROW, m_pawnArr[i].GetTeam(), m_pawnArr[i].GetPos().x, m_pawnArr[i].GetPos().y, 0, 1, m_pawnArr[i].GetOwner());
				//m_arrowArr.emplace_back(OBJECT_TYPE::OBJECT_ARROW, m_pawnArr[i].GetTeam(), m_pawnArr[i].GetPos().x, m_pawnArr[i].GetPos().y, rand() % 100 - 50, rand() % 100 - 50, m_pawnArr[i].GetOwner());
				else if (m_pawnArr[i].GetTeam() == TEAM_TYPE::RED_TEAM)
					m_arrowArr.emplace_back(OBJECT_TYPE::OBJECT_ARROW, m_pawnArr[i].GetTeam(), m_pawnArr[i].GetPos().x, m_pawnArr[i].GetPos().y, 0, -1, m_pawnArr[i].GetOwner());
				//m_arrowArr.emplace_back(OBJECT_TYPE::OBJECT_ARROW, m_pawnArr[i].GetTeam(), m_pawnArr[i].GetPos().x, m_pawnArr[i].GetPos().y, rand() % 100 - 50, rand() % 100 - 50, m_pawnArr[i].GetOwner());

				m_pawnArr[i].SetObjectTime(0);
			}
	}

	AI();

	for (auto &i : m_pawnArr) {
		//235 -110

		if (i.GetPos().y >= 275) {
			if (i.GetTeam() == TEAM_TYPE::BLUE_TEAM) {
				if (i.GetPos().x >= 0) {
					i.SetDir(-1, 0);
				}
				else i.SetDir(1, 0);
			}
			else if (i.GetTeam() == TEAM_TYPE::RED_TEAM) {
				i.SetDir(0, -1);
			}
		}
		else if (i.GetPos().y <= -150) {
			if (i.GetTeam() == TEAM_TYPE::RED_TEAM) {
				if (i.GetPos().x >= 0) {
					i.SetDir(-1, 0);
				}
				else i.SetDir(1, 0);
			}
			else if (i.GetTeam() == TEAM_TYPE::BLUE_TEAM) {
				i.SetDir(0, 1);
			}
		}
	}

	AddRedPawn();
	Collision();
	RemoveZombie();

	if (m_buildingArr[1].GetLife() <= 0 || m_buildingArr[4].GetLife() <= 0)
		m_gameEnd = true;
	
	m_blueTime+= elapsedTime;
	if (m_blueTime >= 10000) m_blueTime = 10000;

	m_paticleTime += (float)(rand() % 100 / 100.0f);

	if (m_globalPaticle) {
		m_globalPaticleTime += (float)elapsedTime / 2000;

		if (m_globalPaticleTime >= 3) {
			m_globalPaticleTime = 0;
			m_globalPaticle = false;

			for (auto &i : m_pawnArr) {
				if (i.GetTeam() == TEAM_TYPE::RED_TEAM)
					i.SetSpeed(CHARACTER_BASE_SPEED);
			}
		}

	}
}

void InGameScene::Draw() {

	myRenderer->DrawTexturedRect(
		0,
		0,
		0,
		800,
		1,
		1,
		1,
		1,
		m_backImg,
		DRAW_LEVEL_BACK
	);


	for (auto i : m_pawnArr) {
		//i.Draw(*myRenderer);
		i.DrawLife(*myRenderer);
		if (i.GetTeam() == TEAM_TYPE::RED_TEAM) {
			if(i.m_weapon == WEAPON_TYPE::SWORD)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[0][0], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER );
			else if (i.m_weapon == WEAPON_TYPE::ARROW)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[0][1], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER);
			else if (i.m_weapon == WEAPON_TYPE::GUARD)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[0][2], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER);
		}
		else if (i.GetTeam() == TEAM_TYPE::BLUE_TEAM) {
			if (i.m_weapon == WEAPON_TYPE::SWORD)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[1][0], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER);
			else if (i.m_weapon == WEAPON_TYPE::ARROW)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[1][1], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER);
			else if (i.m_weapon == WEAPON_TYPE::GUARD)
				myRenderer->DrawTexturedRectSeq(i.GetPos().x, i.GetPos().y, 0, i.GetSize() + 10, 1, 1, 1, 1, m_animImg[1][2], i.GetAnimCount(), i.GetAnimDirection(), 3, 4, DRAW_LEVEL_CHARACTER);
		}
	}
	
	//for (auto i : m_buildingArr) {
	//	i.Draw(*myRenderer);
	//}
	//

	//if(m_buildingArr.size())
	//	myRenderer->DrawTexturedRect(
	//	m_buildingArr[0].GetPos().x,
	//	m_buildingArr[0].GetPos().y,
	//	0, 
	//	m_buildingArr[0].GetSize(),
	//	1, 
	//	1, 
	//	1, 
	//	1, 
	//	m_buildingTextureArr[0],
	//	DRAW_LEVEL_BUILDING
	//);

	for (auto i : m_buildingArr) {

		if (i.GetLife() > 0) {
			if (i.GetIndex() == 1 || i.GetIndex() == 4) {
				i.DrawLife(*myRenderer);
				continue;
			}
			else if (i.GetTeam() == TEAM_TYPE::RED_TEAM)
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
	}

	for (auto i : m_bulletArr) {
		//i.Draw(*myRenderer);
		if(i.GetTeam() == TEAM_TYPE::RED_TEAM)
			myRenderer->DrawParticle(i.GetPos().x, i.GetPos().y, 0, i.GetSize() - 70 , 1, 1, 1, 2 - i.GetPaticleTime() / 2, -i.GetDirVector().x * 2, -i.GetDirVector().y * 2, m_paticleImg[0], i.GetPaticleTime(), DRAW_LEVEL_PATICLE);
		else if (i.GetTeam() == TEAM_TYPE::BLUE_TEAM)
			myRenderer->DrawParticle(i.GetPos().x, i.GetPos().y, 0, i.GetSize() - 70 , 1, 1, 1, 2 - i.GetPaticleTime() / 2, -i.GetDirVector().x * 2, -i.GetDirVector().y * 2, m_paticleImg[1], i.GetPaticleTime(), DRAW_LEVEL_PATICLE);
	}

	for (auto i : m_arrowArr) {
		i.Draw(*myRenderer);
	}

	if(m_globalPaticle)
		myRenderer->DrawParticleClimate(0, 0, 0, 3, 1, 1, 1, 1, sin(m_globalPaticleTime), -0.5, m_globalPaticleImg[0], m_globalPaticleTime , DRAW_LEVEL_GLOBAL_PATICLE);

	if(m_gameEnd)
		myRenderer->DrawTexturedRect(0,0,0,500,1,1,1,1,m_endImg,DRAW_LEVEL_ENDUI);
	
	char blueTime[8]{};
	_itoa_s((int)m_blueTime / 1000, blueTime, 10);
	myRenderer->DrawText(-130, -380, GLUT_BITMAP_9_BY_15, 1, 1, 1, blueTime);

	for (int i = 0; i < m_blueTime / 1000; i++) {
		myRenderer->DrawSolidRectGauge(-130 + 30 + 36 * i, -380, 0, 36, 10, 0.9, 0.1, 0.9, 0.9, 1.0, DRAW_LEVEL_ENDUI);
		//myRenderer->DrawSolidRect(-130 + 18 + 36 * i, -380, 0, 36, 0.9, 0.2, 0.8, 1.0, DRAW_LEVEL_ENDUI);
	}
}

void InGameScene::KeyProc(const unsigned char key, const int specKey) {

}

void InGameScene::MouseProc(const int button, const int state, const int x, const int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		AddBasePawn(x, y);
		std::cout << "m_blueTime :  " << m_blueTime << "  xPos : " << x << "   yPos : " << y << std::endl;
	}
}

void InGameScene::AddRedPawn() {

	if (m_buildingArr[0].m_nextRespone == WEAPON_TYPE::ARROW) {
		if (m_buildingArr[0].GetObejctTime() >= CHARACTER_ARROW_COST * 2 && m_buildingArr[0].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::ARROW, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, 0, -1);
				m_buildingArr[0].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}
	else if (m_buildingArr[0].m_nextRespone == WEAPON_TYPE::SWORD) {
		if (m_buildingArr[0].GetObejctTime() >= CHARACTER_SWORD_COST * 2&& m_buildingArr[0].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::SWORD, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, 0, -1);
				m_buildingArr[0].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}
	else if (m_buildingArr[0].m_nextRespone == WEAPON_TYPE::GUARD) {
		if (m_buildingArr[0].GetObejctTime() >= CHARACTER_GUARD_COST * 2 && m_buildingArr[0].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::GUARD, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, 0, -1);
				m_buildingArr[0].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[0].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}

	if (m_buildingArr[2].m_nextRespone == WEAPON_TYPE::ARROW) {
		if (m_buildingArr[2].GetObejctTime() >= CHARACTER_ARROW_COST * 2 && m_buildingArr[2].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::ARROW, m_buildingArr[2].GetPos().x, m_buildingArr[2].GetPos().y, 0, -1);
				m_buildingArr[2].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}
	else if (m_buildingArr[2].m_nextRespone == WEAPON_TYPE::SWORD) {
		if (m_buildingArr[2].GetObejctTime() >= CHARACTER_SWORD_COST * 2 && m_buildingArr[2].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::SWORD, m_buildingArr[2].GetPos().x, m_buildingArr[2].GetPos().y, 0, -1);
				m_buildingArr[2].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}
	else if (m_buildingArr[2].m_nextRespone == WEAPON_TYPE::GUARD) {
		if (m_buildingArr[2].GetObejctTime() >= CHARACTER_GUARD_COST * 2 && m_buildingArr[2].GetLife() > 0) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;
				m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, WEAPON_TYPE::GUARD, m_buildingArr[2].GetPos().x, m_buildingArr[2].GetPos().y, 0, -1);
				m_buildingArr[2].SetObjectTime(0);
			}

			int buf = rand() % 3;
			if (buf == 0) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::SWORD;
			else if (buf == 1) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::ARROW;
			else if (buf == 2) m_buildingArr[2].m_nextRespone = WEAPON_TYPE::GUARD;
		}
	}

//
//	if (m_buildingArr[0].GetObejctTime() >= RED_AUTO_RESPAWN_TIME && m_buildingArr[0].GetLife() > 0){
//		if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
//			m_ownerArrow++;
//			m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, m_buildingArr[0].GetPos().x, m_buildingArr[0].GetPos().y, 0, -1, m_ownerArrow);
//			m_buildingArr[0].SetObjectTime(0);
//		}
//	}
//	else if (m_buildingArr[2].GetObejctTime() >= RED_AUTO_RESPAWN_TIME &&  m_buildingArr[2].GetLife() > 0) {
//		if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
//			m_ownerArrow++;
//			m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::RED_TEAM, m_buildingArr[2].GetPos().x, m_buildingArr[2].GetPos().y, 0, -1, m_ownerArrow);
//			m_buildingArr[2].SetObjectTime(0);
//		}
//	}
}

void InGameScene::AddBasePawn(const int x, const int y){
	if (m_blueTime >= BLUE_RESPAWN_LIMIT_TIME)
		m_blueTime = BLUE_RESPAWN_LIMIT_TIME;

	// -265, -350
	//
	//	- 132, -56
	//	- 36, 38
	//	55 134
	//	150 228

	if (y <= -260 && y >= -350) {
		if (x >= -130 && x <= -55) { m_nowWeaponType = WEAPON_TYPE::SWORD; }
		else if (x >= -40 && x <= 40) { m_nowWeaponType = WEAPON_TYPE::ARROW; }
		else if (x >= 55 && x <= 135) { m_nowWeaponType = WEAPON_TYPE::GUARD; }
		else if (x >= 150 && x <= 230) { if (m_blueTime >= 10000) {
			m_blueTime = 0; m_globalPaticle = true; 
			for (auto &i : m_pawnArr) {
				if (i.GetTeam() == TEAM_TYPE::RED_TEAM)
					i.SetSpeed(CHARACTER_BASE_SPEED / 5);
			}
		} }
	}
	else if (y > -230) {
		if (m_nowWeaponType == WEAPON_TYPE::SWORD && m_blueTime >= CHARACTER_SWORD_COST){
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;

				if (x > 0 && m_buildingArr[3].GetLife() > 0) 
						m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[3].GetPos().x, m_buildingArr[3].GetPos().y, 0, 1);
				
				else if (x < 0 && m_buildingArr[5].GetLife() > 0)
						m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[5].GetPos().x, m_buildingArr[5].GetPos().y, 0, 1);
				
				else return;
			}
			m_blueTime -= CHARACTER_SWORD_COST;
		}
		if (m_nowWeaponType == WEAPON_TYPE::ARROW && m_blueTime >= CHARACTER_ARROW_COST) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;

				if (x > 0 && m_buildingArr[3].GetLife() > 0)
					m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[3].GetPos().x, m_buildingArr[3].GetPos().y, 0, 1);

				else if (x < 0 && m_buildingArr[5].GetLife() > 0)
					m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[5].GetPos().x, m_buildingArr[5].GetPos().y, 0, 1);

				else return;
			}
			m_blueTime -= CHARACTER_ARROW_COST;
		}
		if (m_nowWeaponType == WEAPON_TYPE::GUARD && m_blueTime >= CHARACTER_GUARD_COST) {
			if (m_pawnArr.size() < MAX_OBJECTS_COUNT) {
				m_ownerArrow++;

				if (x > 0 && m_buildingArr[3].GetLife() > 0)
					m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[3].GetPos().x, m_buildingArr[3].GetPos().y, 0, 1);

				else if (x < 0 && m_buildingArr[5].GetLife() > 0)
					m_pawnArr.emplace_back(OBJECT_TYPE::OBJECT_CHARACTER, TEAM_TYPE::BLUE_TEAM, m_nowWeaponType, m_buildingArr[5].GetPos().x, m_buildingArr[5].GetPos().y, 0, 1);

				else return;
			}
			m_blueTime -= CHARACTER_GUARD_COST;
		}
	}
}

void InGameScene::RemoveZombie() {

		if(m_pawnArr.size())
			for (int i = 0; i < m_pawnArr.size(); i++) {
				if (m_pawnArr[i].GetLife() <= 0) {
					m_pawnArr.erase(m_pawnArr.begin() + i);
				}
			}

		//if (m_buildingArr.size())
		//for (int i = 0; i < m_buildingArr.size(); i++) {
		//	if (m_buildingArr[i].GetLife() <= 0) {
		//		m_buildingArr.erase(m_buildingArr.begin() + i);
		//	}
		//}

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
	//if (m_bulletArr.size()) {
	//	for (int i = 0; i < m_bulletArr.size(); i++) {
	//		nowX = m_bulletArr[i].GetPos().x;
	//		nowY = m_bulletArr[i].GetPos().y;
	//		nowSize = m_bulletArr[i].GetSize() / 2;

	//		for (int j = 0; j < m_buildingArr.size(); j++) {
	//			if (m_bulletArr[i].GetTeam() != m_buildingArr[j].GetTeam()) {
	//				newX = m_buildingArr[j].GetPos().x;
	//				newY = m_buildingArr[j].GetPos().y;
	//				newSize = m_buildingArr[j].GetSize() / 2;

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
	//					m_buildingArr[j].Damaged(m_bulletArr[i].GetLife());
	//					m_bulletArr[i].Damaged(-1);
	//					break;
	//				}
	//			}
	//		}

	//	}
	//}
#pragma endregion

#pragma region [TEAM::Player X Building]
	if (m_pawnArr.size() && m_buildingArr.size()) {
		for (int i = 0; i < m_pawnArr.size(); i++) {
			nowX = m_pawnArr[i].GetPos().x + 1000;
			nowY = m_pawnArr[i].GetPos().y + 1000;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_buildingArr.size(); j++) {
				if (m_buildingArr[j].GetLife() > 0) {
					if (m_buildingArr[j].GetTeam() != m_pawnArr[i].GetTeam()) {
						newX = m_buildingArr[j].GetPos().x + 1000;
						newY = m_buildingArr[j].GetPos().y + 1000;
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
	}
#pragma endregion

#pragma region [TEAM::Player X Arrow]
	if (m_pawnArr.size() && m_arrowArr.size()) {
		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x + 1000;
			nowY = m_pawnArr[i].GetPos().y + 1000;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_arrowArr.size(); j++) {
				if (m_arrowArr[j].GetTeam() != m_pawnArr[i].GetTeam()) {
					newX = m_arrowArr[j].GetPos().x + 1000;
					newY = m_arrowArr[j].GetPos().y + 1000;
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
			nowX = m_pawnArr[i].GetPos().x + 1000;
			nowY = m_pawnArr[i].GetPos().y + 1000;
			nowSize = m_pawnArr[i].GetSize() / 2;

			for (int j = 0; j < m_bulletArr.size(); j++) {
				if (m_pawnArr[i].GetTeam() != m_bulletArr[j].GetTeam()) {
					newX = m_bulletArr[j].GetPos().x + 1000;
					newY = m_bulletArr[j].GetPos().y + 1000;
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
	if (m_pawnArr.size()) {
	
		for (int i = 0; i < m_pawnArr.size() - 1; i++) {
			nowX = m_pawnArr[i].GetPos().x + 1000;
			nowY = m_pawnArr[i].GetPos().y + 1000;
			nowSize = m_pawnArr[i].GetSize() / 2;
	
			for (int j = i + 1; j < m_pawnArr.size(); j++) {
				if (m_pawnArr[i].GetTeam() != m_pawnArr[j].GetTeam()) {
					newX = m_pawnArr[j].GetPos().x + 1000;
					newY = m_pawnArr[j].GetPos().y + 1000;
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
						int lifeBuf = m_pawnArr[j].GetLife();
						m_pawnArr[j].Damaged(m_pawnArr[i].GetLife());
						m_pawnArr[i].Damaged(lifeBuf);
						break;
					}
				}
			}
		}
	}
#pragma endregion

#pragma region [TEAM::Building X Arrow]
 //  if (m_arrowArr.size() && m_arrowArr.size()) {

	//	for (int i = 0; i <m_arrowArr.size(); i++) {
	//		nowX = m_arrowArr[i].GetPos().x;
	//		nowY = m_arrowArr[i].GetPos().y;
	//		nowSize = m_arrowArr[i].GetSize() / 2;

	//		for (int j = 0; j < m_buildingArr.size(); j++) {
	//			if (m_arrowArr[i].GetTeam() != m_buildingArr[j].GetTeam()) {
	//				newX = m_buildingArr[j].GetPos().x;
	//				newY = m_buildingArr[j].GetPos().y;
	//				newSize = m_buildingArr[j].GetSize() / 2;

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
	//					m_buildingArr[j].Damaged(m_arrowArr[i].GetLife());
	//					m_arrowArr[i].Damaged(-1);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
#pragma endregion
}

void InGameScene::AI() {
	// 적용할 AI는 총 5가지 + 1 입니다. (코너에서 꺽는거는 Update에서 처리함)
	//AI
	//	- 1. 앞에 적이있고 일정거리에 가까우면 뒤로 움직일 수 있게하자!(궁수)
	//	-2. 적이 궁수가 없고, 우리팀에 내뒤에 궁수가 있으면 후퇴(전사, 방패)
	//	- 3. 적이 궁수가 없고, 우리팀에 내 앞에 궁수가 있으면 전진(전사, 방패)
	//	- 4. 적이 궁수가 있으면 전진(전사, 방패)
	//	- 5. 방패병이 있으면 뒤로(전사) --> 구현 X
	AI_1();
}

void InGameScene::AI_1() {
	if (m_pawnArr.size()) {
		for (int i = 0; i < m_pawnArr.size(); i++) {
			bool isStop = false;
			if (m_pawnArr[i].m_weapon == WEAPON_TYPE::ARROW) {
				if (m_pawnArr[i].GetTeam() == TEAM_TYPE::BLUE_TEAM) {
					for (int j = 0; j < m_pawnArr.size(); j++) {
						if (m_pawnArr[j].GetTeam() == TEAM_TYPE::RED_TEAM) {
							if (m_pawnArr[i].GetPos().x > 0 && m_pawnArr[j].GetPos().x > 0 || 
								m_pawnArr[i].GetPos().x < 0 && m_pawnArr[j].GetPos().x < 0 ) {
								if (sqrt((m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)
									* (m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)) <= 30) {
									m_pawnArr[i].SetDir(0, -1);
									m_pawnArr[i].SetSpeed(CHARACTER_BASE_SPEED);
									goto NEXT_PAWN_AI;
								}
								else if (sqrt((m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)
									* (m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)) <= 120) {
									m_pawnArr[i].SetSpeed(0);
									isStop = true;
								}
							}
						}
					}
				}
				else if (m_pawnArr[i].GetTeam() == TEAM_TYPE::RED_TEAM) {
					for (int j = 0; j < m_pawnArr.size(); j++) {
						if (m_pawnArr[j].GetTeam() == TEAM_TYPE::BLUE_TEAM) {
							if (m_pawnArr[i].GetPos().x > 0 && m_pawnArr[j].GetPos().x > 0 ||
								m_pawnArr[i].GetPos().x < 0 && m_pawnArr[j].GetPos().x < 0) {
								if (sqrt((m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)
									* (m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)) <= 30) {
									m_pawnArr[i].SetDir(0, 1);
									m_pawnArr[i].SetSpeed(CHARACTER_BASE_SPEED);
									goto NEXT_PAWN_AI;
								}
								else if (sqrt((m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)
									* (m_pawnArr[j].GetPos().y - m_pawnArr[i].GetPos().y)) <= 120) {
									m_pawnArr[i].SetSpeed(0);
									isStop = true;
								}
							}
						}
					}
				}
			}

			if (!isStop) {
				m_pawnArr[i].SetSpeed(CHARACTER_BASE_SPEED);

				if(m_pawnArr[i].GetTeam() == TEAM_TYPE::RED_TEAM)
					m_pawnArr[i].SetDir(0, -1);
				else if (m_pawnArr[i].GetTeam() == TEAM_TYPE::BLUE_TEAM)
					m_pawnArr[i].SetDir(0, 1);
				continue;
			}
			else if (isStop) {
				if (m_pawnArr[i].GetPos().y > 195) {
					if (m_pawnArr[i].GetTeam() == TEAM_TYPE::RED_TEAM) {
						m_pawnArr[i].SetDir(0, -1);
						m_pawnArr[i].SetSpeed(CHARACTER_BASE_SPEED);
					}
				}
				else if (m_pawnArr[i].GetPos().y < -70) {
					if (m_pawnArr[i].GetTeam() == TEAM_TYPE::BLUE_TEAM) {
						m_pawnArr[i].SetDir(0, 1);
						m_pawnArr[i].SetSpeed(CHARACTER_BASE_SPEED);
					}
				}
				continue;
			}

		NEXT_PAWN_AI: 

			if (m_pawnArr[i].GetPos().y > 195) {
				if (m_pawnArr[i].GetTeam() == TEAM_TYPE::RED_TEAM) {
					m_pawnArr[i].SetDir(0, -1);
					m_pawnArr[i].SetSpeed(0);
				}
			}
			else if (m_pawnArr[i].GetPos().y < -70) {
				if (m_pawnArr[i].GetTeam() == TEAM_TYPE::BLUE_TEAM) {
					m_pawnArr[i].SetDir(0, 1);
					m_pawnArr[i].SetSpeed(0);
				}
			}
			
			continue;
		}
	}
}
