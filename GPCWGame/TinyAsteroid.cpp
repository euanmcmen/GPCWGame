#include "TinyAsteroid.h"

//Constructor for a tiny asteroid.
TinyAsteroid::TinyAsteroid()
{

}

//Updates the tiny asteroid.
void TinyAsteroid::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z += cModel::m_mdlSpeed * elapsedTime;
}

//Initialises the tiny asteroid.
void TinyAsteroid::initialise(glm::vec3 scale)
{
	//This spawns a tiny asteroid at a random point within the screen bounds * 2.
	cModel::m_mdlPosition.x = ((RIGHT_BOUND * 2) - (LEFT_BOUND * 2))*(double)rand() / (double)(RAND_MAX)+(LEFT_BOUND * 2);
	cModel::m_mdlPosition.y = ((TOP_BOUND * 2) - (BOTTOM_BOUND * 2))*(double)rand() / (double)(RAND_MAX)+(BOTTOM_BOUND * 2);
	cModel::m_mdlPosition.z = -120.0f;
	cModel::m_mdlRotation = 0.0f; //No rotations for these.
	cModel::m_axis = glm::vec3(0, 0, 0);
	cModel::setScale(glm::vec3(scale.x, scale.y, scale.z));
	cModel::m_mdlSpeed = 75.0f;
	cModel::m_IsActive = true;
}

//Destructor for the tiny asteroid.
TinyAsteroid::~TinyAsteroid()
{
}
