/*
==================================================================================
GameConstants.cpp
==================================================================================
*/

#include "GameConstants.h"

//Game state.
bool isPlayerHit = false;
bool isRestarting = false;

//Camera index 0 = tpv, 1 = fpv.
int cameraIndex = 0; 

//Boolean to determine whether the sound toggle event has been handled.
bool soundEventHandled = true;

//Window borders.
const int TOP_BOUND = 7;
const int BOTTOM_BOUND = -7;
const int RIGHT_BOUND = 15;
const int LEFT_BOUND = -15;