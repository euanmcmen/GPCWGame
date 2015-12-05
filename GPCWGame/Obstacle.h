#pragma once

#include "GameConstants.h"
#include "cModel.h"

class Obstacle : public cModel
{
public:
	Obstacle();

	void initialise(glm::vec3 scale, int type);
	virtual void update(float elapsedTime);
	int getType();
	void setType(int type);
	~Obstacle();
	

private:
	const float speed = 20.0f;
	int TYPE = 0;
};
