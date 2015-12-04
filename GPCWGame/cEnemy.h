#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "cModel.h"

class cEnemy : public cModel
{
public:
	cEnemy();

	void initialise(glm::vec3 scale, int type);
	virtual void update(float elapsedTime);
	int getType();
	void setType(int type);
	~cEnemy();
	

private:
	const float speed = 20.0f;
	int TYPE = 0;
};
#endif