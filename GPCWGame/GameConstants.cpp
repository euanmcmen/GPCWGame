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

//Camera text.
string soundText = "Sound: [ON]";

//Player energy.
int shipPower = 100;

//Window borders
//Set to float so they can be multiplied by a float.
const float TOP_BOUND = 7;
const float BOTTOM_BOUND = -7;
const float RIGHT_BOUND = 15;
const float LEFT_BOUND = -15;