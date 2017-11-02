#pragma once
#include "Scene.h"
#include "stdafx.h"
#include "Actor.h"

#define MAX_OBJECTS_COUNT 10

class InGameScene :
	public Scene
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Create();
	virtual void Update(DWORD);
	virtual void Draw();
	virtual void KeyProc(unsigned char key, int specKey);
	virtual void MouseProc(int button, int state, int x, int y);

	virtual void AddObject(int x, int y);
	virtual void Collision();

	virtual void BuildObject();

	void LifeCheck();

protected:
	Renderer*				myRenderer;

private:
	std::vector<Actor>		m_actorArr;
	int						m_sceneObjectNum = 0;
	std::vector<Actor>		m_buildingArr;

	std::vector<Actor>		m_bulletArr;
};

