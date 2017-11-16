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
#define CLIENT_HEIGHT				800

// 1000을 1초로 가정합니다

#define BULLET_RESPAWN_TIME			10000
#define ARROW_RESPAWN_TIME			3000

#define RED_AUTO_RESPAWN_TIME		5000
#define BLUE_RESPAWN_LIMIT_TIME		7000


#define CHARACTER_BASE_SPEED		300
#define CHARACTER_BASE_LIFE			50
#define CHARACTER_BASE_SIZE			10
#define CHARACTER_BASE_CLOLR		{ 1.0f, 1.0f, 1.0f, 1.0f }
#define CHARACTER_RED_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define CHARACTER_BLUE_CLOLR		{ 0.0f, 0.0f, 1.0f, 1.0f }


#define BUILDING_BASE_SPEED			0
#define BUILDING_BASE_LIFE			500
#define BUILDING_BASE_SIZE			80 //100 사이즈는 너무 커서 80으로했습니다.
#define BUILDING_BASE_CLOLR			{ 1.0f, 1.0f, 0.0f, 1.0f }

#define BULLET_BASE_SPEED			300 //600 
#define BULLET_BASE_LIFE			20
#define BULLET_BASE_SIZE			2
#define BULLET_BASE_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BULLET_RED_CLOLR			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BULLET_BLUE_CLOLR			{ 0.0f, 0.0f, 1.0f, 1.0f }


#define ARROW_BASE_SPEED			100
#define ARROW_BASE_LIFE				10
#define ARROW_BASE_SIZE				2
#define ARROW_BASE_CLOLR			{ 0.0f, 1.0f, 0.0f, 1.0f }
#define ARROW_RED_CLOLR				{ 0.5f, 0.2f, 0.7f, 1.0f }
#define ARROW_BLUE_CLOLR			{ 1.0f, 1.0f, 0.0f, 1.0f }


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

