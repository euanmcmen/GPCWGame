#include "cEnemy.h"
#include "tardisWarsGame.h"

cEnemy::cEnemy() : cModel()
{
	
}

void cEnemy::spawn()
{
	cModel::m_mdlPosition.x = (ENEMY_MAX_X - ENEMY_MIN_X)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_X;
	cModel::m_mdlPosition.y = (ENEMY_MAX_Y - ENEMY_MIN_Y)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_Y;
	cModel::m_mdlPosition.z = 50.0f;
	cModel::m_mdlRotation = 0.0f; //No rotations!
	cModel::m_axis = glm::vec3(0, 0, 0);
	cModel::setScale(glm::vec3(5, 5, 5));
	cModel::m_mdlSpeed = 20.0f;
	cModel::m_IsActive = true;
}

void cEnemy::update(float elapsedTime)
{
	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z -= cModel::m_mdlSpeed * elapsedTime;

	////Check for collision
	//if (isActive() && !isPlayerHit)
	//{
	//	Check if player is colliding with the enemy.
	//	if (thePlayer.SphereSphereCollision(getPosition(), getMdlRadius()))
	//	{
	//		Disable player.
	//		isPlayerHit = true;

	//		Disable this enemy.
	//		enemyIterator = theEnemy.erase(enemyIterator);
	//		(*enemyIterator)->setIsActive(false);
	//	}
	//}
}

bool cEnemy::isInKillzone()
{
	return cModel::m_mdlPosition.z < ENEMY_KILLZONE_Z;
}

cEnemy::~cEnemy()
{

}

