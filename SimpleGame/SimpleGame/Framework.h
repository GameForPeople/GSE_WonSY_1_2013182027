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
	virtual void Update(const DWORD);
	void Draw();
	void KeyProc(const unsigned char key, const int specKey);
	void MouseProc(const int button, const int state, const int x, const int y);
};

