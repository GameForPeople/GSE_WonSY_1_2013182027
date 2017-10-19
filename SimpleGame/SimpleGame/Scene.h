#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Create();
	virtual void Update();
	virtual void Draw();
	virtual void KeyProc(unsigned char key, int specKey);
	virtual void MouseProc(int button, int state, int x, int y);
};

