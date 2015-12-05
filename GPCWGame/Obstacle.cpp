#include "Obstacle.h"
#include "AsteroidAvoiderGame.h"

//Constructor of obstacle.
Obstacle::Obstacle() : cModel()
{
	
}

//Initialises an obstacle
void Obstacle::initialise(glm::vec3 scale, int type)
{
	//This spawns an obstacle at a random point within the bounds of the screen, with a z value of -120.
	cModel::m_mdlPosition.x = (RIGHT_BOUND - LEFT_BOUND)*(double)rand() / (double)(RAND_MAX)+LEFT_BOUND;
	cModel::m_mdlPosition.y = (TOP_BOUND - BOTTOM_BOUND)*(double)rand() / (double)(RAND_MAX)+BOTTOM_BOUND;
	cModel::m_mdlPosition.z = -120.0f;
	cModel::m_mdlRotation = (360 - 0)*(double)rand() / (double)(RAND_MAX);  //Generate a random number between 0 and 360.
	cModel::m_axis = glm::vec3(static_cast<float>(rand() % 2), static_cast<float>(rand() % 2), (rand() % 2));  //Get a random float between 0 and 1
	cModel::setScale(glm::vec3(scale.x, scale.y, scale.z));
	cModel::m_mdlSpeed = speed;
	cModel::m_IsActive = true;
	TYPE = type;
}


void Obstacle::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z += cModel::m_mdlSpeed * elapsedTime;
}

//Returns the obstacle type. 
//Type = 0: obstacle enemy.
//Type = 1: alt obstacle.
int Obstacle::getType()
{
	return TYPE;
}

//Sets the obstacle type.
void Obstacle::setType(int type)
{
	TYPE = type;
}

Obstacle::~Obstacle()
{

}

