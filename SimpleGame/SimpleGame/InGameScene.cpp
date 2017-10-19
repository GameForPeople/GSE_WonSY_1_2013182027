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
}

void InGameScene::Create() {

}

void InGameScene::Update() {
	for (auto i : actorArr) {
		i.Move();
	}
}

void InGameScene::Draw() {
	for (auto i : actorArr) {
		i.Draw(*myRenderer);
	}
}

void InGameScene::KeyProc(unsigned char key, int specKey) {

}

void InGameScene::MouseProc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		actorArr.emplace_back(x, y, 10, 1, 0, 0, 1, 0.5f, 1.0f, 0);
	}
}
