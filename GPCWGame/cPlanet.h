#ifndef PLANET_H
#define PLANET_H

#include "cModel.h"
#include "GameConstants.h"

class cPlanet :	public cModel
{
	public:
	cPlanet();
	virtual void update(float elapsedTime);
	~cPlanet();
};

#endif