#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

//Initialise the player with many "zero" values as the player is pretty concrete.  
//It spawns in the same place at the same orientation etc.
void cPlayer::initialise()
{
	setPosition(glm::vec3(0,0,0));
	setRotation(0.0f);
	setAxis(glm::vec3(0, 0, 0));
	setScale(glm::vec3(1, 1, 1));
	setDirection(glm::vec3(0,0,0));
	setSpeed(5.0f);
	setIsActive(true);
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, 0, 0, 0);
	glTranslatef(mdlPos.x, mdlPos.y, mdlPos.z);
}

void cPlayer::update(float elapsedTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		//If the player is within the max bounds, then move right.
		if (m_mdlPosition.x <= RIGHT_BOUND)
			translationX = 1.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		//If the player is within the min bounds, then move right.
		if (m_mdlPosition.x >= LEFT_BOUND)
			translationX = -1.0f;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		if (m_mdlPosition.y <= TOP_BOUND)
			translationY = 1;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		if (m_mdlPosition.y >= BOTTOM_BOUND)
			translationY = -1;
	}
	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		if (cameraIndex == 0)
			cameraIndex = 1;
		else if (cameraIndex == 1)
			cameraIndex = 0;
	}

	//Create velocity vector.
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
	if (m_mdlPosition.x < LEFT_BOUND)
	{
		m_mdlPosition.x = LEFT_BOUND;
	}

	//Right bound.
	if (m_mdlPosition.x > RIGHT_BOUND)
	{
		m_mdlPosition.x = RIGHT_BOUND;
	}

	//Top bound.
	if (m_mdlPosition.y > TOP_BOUND)
	{
		m_mdlPosition.y = TOP_BOUND;
	}

	//Bottom bound.
	if (m_mdlPosition.y < BOTTOM_BOUND)
	{
		m_mdlPosition.y = BOTTOM_BOUND;
	}
}

cPlayer::~cPlayer()
{

}