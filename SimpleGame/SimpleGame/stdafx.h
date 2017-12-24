#pragma once

#include "targetver.h"
#include "Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Sound.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <vector>

#define CLIENT_WIDTH				500
#define CLIENT_HEIGHT				800

//빠른 실습 검사를 위해 1000을 2초로 가정합니다

#define BULLET_RESPAWN_TIME			5000
#define ARROW_RESPAWN_TIME			2000

#define RED_AUTO_RESPAWN_TIME		8000
#define BLUE_RESPAWN_LIMIT_TIME		10000


#define CHARACTER_BASE_SPEED		20
#define CHARACTER_BASE_LIFE			50

#define CHARACTER_SWORD_LIFE		50
#define CHARACTER_ARROW_LIFE		10
#define CHARACTER_GUARD_LIFE		120

#define CHARACTER_SWORD_COST		3000
#define CHARACTER_ARROW_COST		4000
#define CHARACTER_GUARD_COST		7000

#define CHARACTER_BASE_SIZE			20
#define CHARACTER_BASE_CLOLR		{ 1.0f, 1.0f, 1.0f, 1.0f }
#define CHARACTER_RED_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define CHARACTER_BLUE_CLOLR		{ 0.0f, 0.0f, 1.0f, 1.0f }


#define BUILDING_BASE_SPEED			0
#define BUILDING_BASE_LIFE			500
#define BUILDING_BASE_SIZE			70 //100 사이즈는 너무 커서 80으로했습니다. // 50
#define BUILDING_BASE_CLOLR			{ 1.0f, 1.0f, 0.0f, 1.0f }

#define BUILDING_RED_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BUILDING_BLUE_CLOLR			{ 0.0f, 0.0f, 1.0f, 1.0f }


#define BULLET_BASE_SPEED			100 //600 
#define BULLET_BASE_LIFE			100
#define BULLET_BASE_SIZE			80
#define BULLET_BASE_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BULLET_RED_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BULLET_BLUE_CLOLR			{ 0.0f, 0.0f, 1.0f, 1.0f }


#define ARROW_BASE_SPEED			120
#define ARROW_BASE_LIFE				10
#define ARROW_BASE_SIZE				10
#define ARROW_BASE_CLOLR			{ 0.0f, 1.0f, 0.0f, 1.0f }
#define ARROW_RED_CLOLR				{ 0.8f, 0.0f, 0.0f, 1.0f }
#define ARROW_BLUE_CLOLR			{ 0.0f, 0.0f, 0.8f, 1.0f }


#define DRAW_LEVEL_ENDUI			0.01f
#define DRAW_LEVEL_LIFE				0.05f
#define DRAW_LEVEL_BUILDING			0.1f
#define DRAW_LEVEL_CHARACTER		0.2f
#define DRAW_LEVEL_BULLET			0.3f
#define DRAW_LEVEL_ARROW			0.3f
#define DRAW_LEVEL_BACK				0.99f
#define DRAW_LEVEL_GLOBAL_PATICLE 	0.02f
#define DRAW_LEVEL_PATICLE			0.90f


enum class OBJECT_TYPE {
		OBJECT_BUILDING
	,	OBJECT_CHARACTER
	,	OBJECT_BULLET
	,	OBJECT_ARROW
};

enum class TEAM_TYPE {
		RED_TEAM
	,	BLUE_TEAM
};

enum class WEAPON_TYPE {
		SWORD
	,	ARROW
	,	GUARD
};
