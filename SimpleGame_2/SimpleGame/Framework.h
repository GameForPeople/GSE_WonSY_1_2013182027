#pragma once

#include "Renderer.h"

class Framework
{
private:
	Renderer *myRenderer;
public:
	Framework();
	~Framework();

	void Create(Renderer&);
	void Update();
	void Draw();
	void KeyProc(unsigned char key, int specKey);
	void MouseProc(int button, int state, int x, int y);
};

