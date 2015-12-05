/*
==================================================================================
GameConstants.cpp
==================================================================================
*/

#include "GameConstants.h"

//Game variables.

//Player translation
float translationX = 0;
float translationY = 0;

//Game state.
bool isPlayerHit = false;
bool isRestarting = false;

//Camera index 0 = tpv, 1 = fpv.
int cameraIndex = 0; 

//Window boarders.
const int TOP_BOUND = 7;
const int BOTTOM_BOUND = -7;
const int RIGHT_BOUND = 15;
const int LEFT_BOUND = -15;