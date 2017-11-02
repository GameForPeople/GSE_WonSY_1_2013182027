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

#define CLIENT_WIDTH		500
#define CLIENT_HEIGHT		500

#define BULLET_RESPAWN_TIME 1000


enum class OBJECT_TYPE {
		OBJECT_BUILDING
	,	OBJECT_CHARACTER
	,	OBJECT_BULLET
	,	OBJECT_ARROW
};
