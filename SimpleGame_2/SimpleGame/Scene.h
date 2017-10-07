#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	void Create(Renderer&);
	void Update();
	void Draw();
	void KeyProc(unsigned char key, int specKey);
	void MouseProc(int button, int state, int x, int y);
};

