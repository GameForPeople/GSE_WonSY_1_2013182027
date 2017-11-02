#pragma once

#include "targetver.h"
#include "Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <vector>

#define CLIENT_WIDTH				500
#define CLIENT_HEIGHT				500

#define BULLET_RESPAWN_TIME			1000

#define CHARACTER_BASE_SPEED		300
#define CHARACTER_BASE_LIFE			50
#define CHARACTER_BASE_SIZE			10
#define CHARACTER_BASE_CLOLR		{ 1.0f, 1.0f, 1.0f, 1.0f }

#define BUILDING_BASE_SPEED			0
#define BUILDING_BASE_LIFE			500
#define BUILDING_BASE_SIZE			50
#define BUILDING_BASE_CLOLR			{ 1.0f, 1.0f, 0.0f, 1.0f }

#define BULLET_BASE_SPEED			400
#define BULLET_BASE_LIFE			20
#define BULLET_BASE_SIZE			2
#define BULLET_BASE_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }

#define ARROW_BASE_SPEED			100
#define ARROW_BASE_LIFE				10
#define ARROW_BASE_SIZE				2
#define ARROW_BASE_CLOLR			{ 0.0f, 1.0f, 0.0f, 1.0f }


enum class OBJECT_TYPE {
		OBJECT_BUILDING
	,	OBJECT_CHARACTER
	,	OBJECT_BULLET
	,	OBJECT_ARROW
};

