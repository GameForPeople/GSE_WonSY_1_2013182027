#pragma once
#include "Scene.h"
#include "stdafx.h"
#include "Actor.h"
#include "Pawn.h"

#define MAX_OBJECTS_COUNT 100

class InGameScene :
	public Scene
{
protected:
	Renderer*				myRenderer;

	Sound*					m_sound;
	int						m_bgSound;
private:

	std::vector<Pawn>		m_pawnArr;
	int						m_ownerArrow;

	std::vector<Actor>		m_buildingArr;
	GLuint					m_buildingTextureArr[2];

	std::vector<Pawn>		m_bulletArr;

	std::vector<Pawn>		m_arrowArr;

	GLuint					m_backImg;
	
	GLuint					m_animImg[2];

	GLuint					m_paticleImg[2];

private:
	int						m_redAutoTime{ 0 };
	int						m_blueTime{ 0 };

	float					m_paticleTime{ 0 };
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
	void AddRedPawn();
	void AddBasePawn(const int x, const int y);
	void Collision();
	void RemoveZombie();	// object'life 0' is Zombie
};

