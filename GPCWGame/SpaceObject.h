#pragma once

#include "GameConstants.h"
#include "cModel.h"

class SpaceObject : public cModel
{
public:
	SpaceObject();

	void initialise(float spawnLocationScale, glm::vec3 modelScale, float speed, bool rotationEnabled);
	virtual void update(float elapsedTime);
	~SpaceObject();
};
