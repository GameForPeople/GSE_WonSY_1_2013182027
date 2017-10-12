#pragma once
#include "Scene.h"
class InGameScene :
	public Scene
{
public:
	InGameScene();
	~InGameScene();

	virtual void Create();
	virtual void Update();
	virtual void Draw();
	virtual void KeyProc(unsigned char key, int specKey);
	virtual void MouseProc(int button, int state, int x, int y);
};

