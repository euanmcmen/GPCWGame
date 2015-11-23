#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		//If the player is within the max bounds, then move right.
		if (m_mdlPosition.x < PLAYER_MAX_X)
			translationX = 1;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		//If the player is within the min bounds, then move right.
		if (m_mdlPosition.x > PLAYER_MIN_X)
			translationX = -1;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		translationY = 1;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		translationY = -1;
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		
		//glm::vec3 mdlLaserDirection;
		//mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
		//mdlLaserDirection.y = 0.0f;
		//mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
		//mdlLaserDirection *= -1;

		//// Add new bullet sprite to the vector array
		//theTardisLasers.push_back(new cLaser);
		//int numLasers = theTardisLasers.size() - 1;
		//theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
		//theTardisLasers[numLasers]->setRotation(0.0f);
		//theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
		//theTardisLasers[numLasers]->setSpeed(5.0f);
		//theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
		//theTardisLasers[numLasers]->setIsActive(true);
		////theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
		//theTardisLasers[numLasers]->update(elapsedTime);
		//// play the firing sound
		//m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	//for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	//{
	//	(*laserIterartor)->update(elapsedTime);
	//	for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
	//	{
	//		if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
	//		{
	//			// if a collision set the bullet and spaceship to false
	//			(*enemyIterator)->setIsActive(false);
	//			(*laserIterartor)->setIsActive(false);
	//			// play the explosion sound.
	//			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
	//		}
	//	}
	//}

	//vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	//while (laserIterartor != theTardisLasers.end())
	//{
	//	if ((*laserIterartor)->isActive() == false)
	//	{
	//		laserIterartor = theTardisLasers.erase(laserIterartor);
	//	}
	//	else
	//	{
	//		++laserIterartor;
	//	}
	//}

	//vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();
	//while (enemyIterartor != theEnemy.end())
	//{
	//	if ((*enemyIterartor)->isActive() == false)
	//	{
	//		enemyIterartor = theEnemy.erase(enemyIterartor);
	//	}
	//	else
	//	{
	//		++enemyIterartor;
	//	}
	//}

	vector<cEnemy*>::iterator enemyIterator = theEnemy.begin();
	while (enemyIterator != theEnemy.end())
	{
		//Check if player is colliding with the enemy.
		if (SphereSphereCollision((*enemyIterator)->getPosition(), (*enemyIterator)->getMdlRadius()))
		{
			//Disable player.
			playerHit = true;

			//Disable this enemy.
			enemyIterator = theEnemy.erase(enemyIterator);
		}
		else
		{
			++enemyIterator;
		}
	}

	// Find out what direction we should be thrusting.
	//Create our velocity vector.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = translationX;
	mdlVelocityAdd.y = translationY;
	mdlVelocityAdd.z = 0.0f;

	cModel::m_mdlDirection += mdlVelocityAdd;

	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	cModel::m_mdlDirection *= 0.5f;

	translationX = 0;
	translationY = 0;
}

cPlayer::~cPlayer()
{

}