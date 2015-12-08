#include "SpaceObject.h"
#include "AsteroidAvoiderGame.h"

//Constructor of obstacle.
SpaceObject::SpaceObject() : cModel()
{
	
}

//Initialises an obstacle
void SpaceObject::initialise(float spawnLocationScale, glm::vec3 modelScale, float speed, bool rotationEnabled)
{
	//This spawns an obstacle at a random point within the bounds of the screen multiplied by the spawnlocationscale, with a z value of -120.
	cModel::m_mdlPosition.x = ((RIGHT_BOUND * spawnLocationScale) - (LEFT_BOUND * spawnLocationScale))*(double)rand() / (double)(RAND_MAX)+(LEFT_BOUND * spawnLocationScale);
	cModel::m_mdlPosition.y = ((TOP_BOUND * spawnLocationScale) - (BOTTOM_BOUND * spawnLocationScale))*(double)rand() / (double)(RAND_MAX)+(BOTTOM_BOUND * spawnLocationScale);
	cModel::m_mdlPosition.z = -120.0f;

	if (rotationEnabled)
	{

		//Generate a random number between 0 and 360 to assign to the rotation.
		cModel::m_mdlRotation = (360 - 0)*(double)rand() / (double)(RAND_MAX);

		//Get a random float between 0 and 1 to use as the axis.
		cModel::m_axis = glm::vec3(static_cast<float>(rand() % 2), static_cast<float>(rand() % 2), (rand() % 2));
	}
	else
	{
		//Set rotation to 0
		cModel::m_mdlRotation = 0;

		//Don't rotate on any axis.
		cModel::m_axis = glm::vec3(0,0,0);
	}

	//Set the object scale and speed.
	cModel::setScale(glm::vec3(modelScale.x, modelScale.y, modelScale.z));
	cModel::m_mdlSpeed = speed;

	//Activate the object.
	cModel::m_IsActive = true;
}


void SpaceObject::update(float elapsedTime)
{
	//Move object towards 0 on z axis.
	cModel::m_mdlPosition.z += cModel::m_mdlSpeed * elapsedTime;

	//Check if in killzone.
	if (isActive() && isInKillzone())
	{
		setIsActive(false);
	}
}

SpaceObject::~SpaceObject()
{

}

