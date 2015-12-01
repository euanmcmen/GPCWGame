#include "Asteroid.h"


Asteroid::Asteroid()
{

}

void Asteroid::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z += cModel::m_mdlSpeed * elapsedTime;
}

void Asteroid::initialise(glm::vec3 scale)
{
	cModel::m_mdlPosition.x = ((RIGHT_BOUND * 2) - (LEFT_BOUND * 2))*(double)rand() / (double)(RAND_MAX)+(LEFT_BOUND * 2);
	cModel::m_mdlPosition.y = ((TOP_BOUND * 2) - (BOTTOM_BOUND * 2))*(double)rand() / (double)(RAND_MAX)+(BOTTOM_BOUND * 2);
	cModel::m_mdlPosition.z = -100.0f;
	cModel::m_mdlRotation = 0.0f; //No rotations!
	cModel::m_axis = glm::vec3(0, 0, 0);
	cModel::setScale(glm::vec3(scale.x, scale.y, scale.z));
	cModel::m_mdlSpeed = 50.0f;
	cModel::m_IsActive = true;
}

Asteroid::~Asteroid()
{
}
