#pragma once

#include "Scene.h"
#include "InGameScene.h"

class Framework
{
private:
	Scene *m_sceneArr;

public:
	Framework();
	~Framework();

	void Create();
	virtual void Update();
	void Draw();
	void KeyProc(unsigned char key, int specKey);
	void MouseProc(int button, int state, int x, int y);
};

