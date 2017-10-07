#include "stdafx.h"
#include "Framework.h"

Framework::Framework()
{
}

Framework::~Framework()
{
}

void Framework::Create(Renderer& paRenderer) {
	//myRenderer = new Renderer(500,500);
	myRenderer = &paRenderer;

}

void Framework::Update() {

}

void Framework::Draw() {

}

void Framework::KeyProc(unsigned char key, int specKey) {

}

void Framework::MouseProc(int button, int state, int x, int y) {

}
