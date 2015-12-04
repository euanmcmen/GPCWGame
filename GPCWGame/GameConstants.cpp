/*
==================================================================================
GameConstants.cpp
==================================================================================
*/

#include "GameConstants.h"

//Game variables.
int drawMode = 0;
float rotationAngle = 0;
float translationX = 0;
float translationY = 0;
bool isPlayerHit = false;
bool isRestarting = false;
int cameraIndex = 0;  //Camera index 0 = close, 1 = far.
const int TOP_BOUND = 7;
const int BOTTOM_BOUND = -7;
const int RIGHT_BOUND = 15;
const int LEFT_BOUND = -15;
bool fire = false;
