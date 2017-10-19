#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
	myRenderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);
	myRenderer->IsInitialized();


	m_testActor.SetActor((float)1, (float)1, 10, 1, 1, 1, 1, 0.3f, 1.0f, 1.0f);
}

InGameScene::~InGameScene()
{
	delete myRenderer;
}

void InGameScene::Create() {

}

void InGameScene::Update() {
	//for (auto i : actorArr) {
	//	i.Update();
	//}
	//
	for (int i = 0; i < m_sceneObjectNum; i++) {
		m_actorArr[i].Update();
	}
	m_testActor.Update();
}

void InGameScene::Draw() {
	for (auto i : m_actorArr) {
		i.Draw(*myRenderer);
	}

	m_testActor.Draw(*myRenderer);
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
		m_actorArr.emplace_back((float)x, (float)y, 10, 1, 1, 1, 1, 0.3f, 1.0f, 1.0f);
		//Actor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY);

		m_sceneObjectNum++;
	}
}
