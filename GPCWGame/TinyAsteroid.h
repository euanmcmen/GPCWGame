#pragma once
#include "cModel.h"
class TinyAsteroid : public cModel
{
	public:
	TinyAsteroid();
	void update(float elapsedTime);
	void initialise(glm::vec3 scale);
	~TinyAsteroid();
};

