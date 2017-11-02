#pragma once
#include "Scene.h"
#include "stdafx.h"
#include "Actor.h"
#include "Pawn.h"

#define MAX_OBJECTS_COUNT 10

class InGameScene :
	public Scene
{
protected:
	Renderer*				myRenderer;

private:
	std::vector<Pawn>		m_pawnArr;

	std::vector<Actor>		m_buildingArr;

	std::vector<Pawn>		m_bulletArr;

public:
	InGameScene();
	virtual ~InGameScene();

public:
	virtual void Create();
	virtual void Update(const DWORD time);
	virtual void Draw();
	virtual void KeyProc(const unsigned char key, const int specKey);
	virtual void MouseProc(const int button, const int state, const int x, const int y);
	
public:
	void BuildObject();

public:
	void AddBasePawn(const int x, const int y);
	void Collision();
	void RemoveZombie();	// object'life 0' is Zombie
};

