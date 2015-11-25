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
		if (m_mdlPosition.x <= PLAYER_MAX_X)
			translationX = 1.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		//If the player is within the min bounds, then move right.
		if (m_mdlPosition.x >= PLAYER_MIN_X)
			translationX = -1.0f;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		if (m_mdlPosition.y <= PLAYER_MAX_X)
			translationY = 1;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		if (m_mdlPosition.y >= PLAYER_MIN_Y)
			translationY = -1;
	}

	//if (m_InputMgr->isKeyDown(VK_SPACE))
	//{

	//	//// Add new bullet sprite to the vector array
	//	//theTardisLasers.push_back(new cLaser);
	//	//int numLasers = theTardisLasers.size() - 1;
	//	//theTardisLasers[numLasers]->setDirection(glm::vec3(0,0,0));
	//	//theTardisLasers[numLasers]->setRotation(0.0f);
	//	//theTardisLasers[numLasers]->setAxis(glm::vec3(0, 0, 0));
	//	//theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
	//	//theTardisLasers[numLasers]->setSpeed(5.0f);
	//	//theTardisLasers[numLasers]->setPosition(this->getPosition() + glm::vec3(0,0,2));
	//	//theTardisLasers[numLasers]->setIsActive(true);
	//	////theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
	//	//theTardisLasers[numLasers]->update(elapsedTime);
	//	//// play the firing sound
	//	////m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	//}

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

	//vector<cEnemy*>::iterator enemyIterator = theEnemy.begin();
	//while (enemyIterator != theEnemy.end())
	//{
	//	if ((*enemyIterator)->isActive())
	//	{
	//		//Check if player is colliding with the enemy.
	//		if (SphereSphereCollision((*enemyIterator)->getPosition(), (*enemyIterator)->getMdlRadius()))
	//		{
	//			//Disable player.
	//			isPlayerHit = true;

	//			//Disable this enemy.
	//			//enemyIterator = theEnemy.erase(enemyIterator);
	//			//(*enemyIterator)->setIsActive(false);
	//			
	//		}
	//		else
	//		{
	//			++enemyIterator;
	//		}
	//	}
	//}

	// Find out what direction we should be thrusting.
	//Create our velocity vector.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = translationX;
	mdlVelocityAdd.y = translationY;
	mdlVelocityAdd.z = 0.0f;

	cModel::m_mdlDirection += mdlVelocityAdd;

	cModel::m_mdlPosition += m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	cModel::m_mdlDirection *= 0.7f;


	//Clamp position.
	clampPosition();

	translationX = 0;
	translationY = 0;
}

void cPlayer::checkForRestart()
{
	if (m_InputMgr->isKeyDown(VK_RETURN))
	{
		isRestarting = true;
	}	
}

void cPlayer::clampPosition()
{
	//Left bound.
	if (m_mdlPosition.x < PLAYER_MIN_X)
	{
		m_mdlPosition.x = PLAYER_MIN_X;
	}

	//Right bound.
	if (m_mdlPosition.x > PLAYER_MAX_X)
	{
		m_mdlPosition.x = PLAYER_MAX_X;
	}

	//Top bound.
	if (m_mdlPosition.y > PLAYER_MAX_Y)
	{
		m_mdlPosition.y = PLAYER_MAX_Y;
	}

	//Bottom bound.
	if (m_mdlPosition.y < PLAYER_MIN_Y)
	{
		m_mdlPosition.y = PLAYER_MIN_Y;
	}
}

cPlayer::~cPlayer()
{

}