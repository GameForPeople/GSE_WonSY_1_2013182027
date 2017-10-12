/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <vector>
#include "Framework.h"
#include "Actor.h"

Renderer *g_Renderer = NULL;
Framework *myFramework = NULL;

Actor simpleActor({ 10.0f, 10.0f }, 10.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.01f, { 1.0f, 0.0f });

std::vector<Actor> actorArr;

float x, y;

#pragma region [Core Functions]
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	myFramework->Draw();
	// Renderer Test
	simpleActor.Draw(*g_Renderer);

		for (auto i : actorArr ) {
			i.Draw(*g_Renderer);
		}

	glutSwapBuffers();
}

void Idle(void)
{
	myFramework->Update();
	simpleActor.Move();

	for (auto i : actorArr) {
		i.Move();
	}

	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	//GLUT_LEFT_BUTTON, GLUT_MDDLE_BUTTON, GLUT_RIGHT_BUTTON
	//GLUT_UP, GLUT_DOWN
	myFramework->MouseProc(button, state, x - 500, y );
	actorArr.emplace_back(x - 250, - y + 250, 10, 1, 0, 0, 1, 0.1, 1.0f, 0);
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}
#pragma endregion

int main(int argc, char **argv)
{
#pragma region [Init Project]
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	myFramework = new Framework();
	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	myFramework->Create(*g_Renderer);
#pragma endregion
#pragma region [Binding Function]
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
#pragma endregion

	glutMainLoop();

#pragma region [EXIT Program]
	delete g_Renderer;
    return 0;
#pragma endregion
}

