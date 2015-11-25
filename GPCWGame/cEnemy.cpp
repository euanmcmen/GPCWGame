#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	
}

void cEnemy::spawn()
{
	cModel::m_mdlPosition.x = (ENEMY_MAX_X - ENEMY_MIN_X)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_X;
	cModel::m_mdlPosition.y = (ENEMY_MAX_Y - ENEMY_MIN_Y)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_Y;
	cModel::m_mdlPosition.z = 50.0f;
	cModel::m_mdlRotation = 0; //No rotations!
	cModel::m_axis = glm::vec3(0, 1, 0);
	//cModel::m_mdlDirection.x = -(float)glm::sin(cModel::m_mdlRotation);
	//cModel::m_mdlDirection.z = (float)glm::cos(cModel::m_mdlRotation);
	cModel::m_mdlSpeed = 10.0f;
	cModel::m_IsActive = true;
}

void cEnemy::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z -= cModel::m_mdlSpeed * elapsedTime;
}

bool cEnemy::isInKillzone()
{
	return cModel::m_mdlPosition.z < ENEMY_KILLZONE_Z;
}

cEnemy::~cEnemy()
{

}

