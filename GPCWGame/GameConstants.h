#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS
//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "Asteroid Escape"

// Windows & OpenGL 
#include <stdlib.h>
#include <Windows.h>
#include "GL\glut.h"
#include <iostream>
#include <string>
#include <ctime>

// Image Texture loading library
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

// Model Loading Library
#include "glm-0.3.2\glm\glm.h"

// Font
#include "FTGL\ftgl.h"

// Audio
#include "OpenAL\al.h"
#include "OpenAL\alc.h"
#include "OpenAL\alut.h"

// Maths functions
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\geometric.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

// Classes
#include "cTexture.h"

//using statements
using namespace std;

struct lightColour4
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha
};

struct colour3f
{
	colour3f(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
};

struct mdlDimensions{
	float s_mdlWidth, s_mdlheight, s_mdldepth;
};

//Game stat values.
extern bool isPlayerHit;
extern bool isRestarting;

//Active Camera index.
extern int cameraIndex;

//Sound values.
extern bool soundEventHandled;
extern string soundText;

//Player energy.
extern int shipPower;

//Screen bounds.
extern const float RIGHT_BOUND;
extern const float LEFT_BOUND;
extern const float TOP_BOUND;
extern const float BOTTOM_BOUND;

#endif