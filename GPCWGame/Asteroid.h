#pragma once
#include "cModel.h"
class Asteroid : public cModel
{
	public:
	Asteroid();
	void update(float elapsedTime);
	void initialise(glm::vec3 scale);
	~Asteroid();
};

