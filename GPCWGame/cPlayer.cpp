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
		translationX = 1;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		translationX = -1;
	}

	//Create our velocity vector.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = translationX; 
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = 0.0f;

	cModel::m_mdlDirection += mdlVelocityAdd;

	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed *elapsedTime;
	cModel::m_mdlDirection *= 0.5f;

	translationX = 0;
}

cPlayer::~cPlayer()
{

}