#pragma once
#include "Object.h"

enum class Direction
{
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
	UpLeft = 5,
	UpRight,
	DownLeft,
	DownRight,
};

struct BoundingBox {

};

class Actor :
	public Object
{
private:
	float m_speed;
	
	Pos2D m_dirVector;
	Direction m_direction;


public:
	Actor();
	Actor(OBJECT_TYPE inputType, Pos2D pos, Pos2D direction);
	Actor(OBJECT_TYPE inputType, float x, float y, float vectorX, float vectorY);
	virtual ~Actor();
	
	virtual void SetActor(float x, float y, float size, float colorR, float colorG, float colorB, float colorAlpha, float speed, float vectorX, float vectorY);

	virtual void Update(DWORD elapsedTime);
	virtual void Move(Direction dir);
	virtual void Move(DWORD elapsedTime);

	virtual void Draw(Renderer);
	virtual int GetObejctTime() {
		return m_objectTime;
	}
	virtual void SetObjectTime(int inputTime) {
		m_objectTime = inputTime;
	}
	virtual void LimitMove();

	Pos2D GetPos();
	float GetSize();


	void SetSpeed(float);
	void ObjectFunction(DWORD elapsedTime);
};

