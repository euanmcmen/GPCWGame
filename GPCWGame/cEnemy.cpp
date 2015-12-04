#include "cEnemy.h"
#include "tardisWarsGame.h"

cEnemy::cEnemy() : cModel()
{
	
}

void cEnemy::initialise(glm::vec3 scale, int type)
{
	cModel::m_mdlPosition.x = (RIGHT_BOUND - LEFT_BOUND)*(double)rand() / (double)(RAND_MAX)+LEFT_BOUND;
	cModel::m_mdlPosition.y = (TOP_BOUND - BOTTOM_BOUND)*(double)rand() / (double)(RAND_MAX)+BOTTOM_BOUND;
	cModel::m_mdlPosition.z = -120.0f;
	cModel::m_mdlRotation = (360 - 0)*(double)rand() / (double)(RAND_MAX)+0;
	cModel::m_axis = glm::vec3(static_cast<float>(rand() % 2), static_cast<float>(rand() % 2), (rand() % 2));  //Get a random float between 0 and 1
	cModel::setScale(glm::vec3(scale.x, scale.y, scale.z));
	cModel::m_mdlSpeed = speed;
	cModel::m_IsActive = true;
	TYPE = type;
}


void cEnemy::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z += cModel::m_mdlSpeed * elapsedTime;
}

//Returns the enemy type. 
//Type = 0: standard enemy.
//Type = 1: alt enemy.
int cEnemy::getType()
{
	return TYPE;
}

void cEnemy::setType(int type)
{
	TYPE = type;
}

cEnemy::~cEnemy()
{

}

