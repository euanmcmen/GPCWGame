/*
==================================================================================
AsteroidAvoiderGame.cpp
==================================================================================
*/

#include "AsteroidAvoiderGame.h"

//The collection of asterpids which the player should avoid.
vector<SpaceObject*> theAsteroids;

//Collection of thematically pleasing asteriods.
vector<SpaceObject*> theTinyAsteroids;

//Collection of batteries for the player to collect.
vector<SpaceObject*> theBatteries;