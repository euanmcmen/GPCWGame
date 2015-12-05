#include "cModel.h"

//Constructor for model.
cModel::cModel()
{

}

// +++++++++++++++++++++++++++++++++++++++++++++
// Setters
// +++++++++++++++++++++++++++++++++++++++++++++

void cModel::setPosition(glm::vec3 mdlPosition)
{
	m_mdlPosition = m_mdlScale;
}

void cModel::setRotation(GLfloat mdlRotation)
{
	m_mdlRotation = mdlRotation;
}

void cModel::setAxis(glm::vec3 axis)
{
	m_axis = axis;
}

void cModel::setDirection(glm::vec3 mdlDirection)
{
	m_mdlDirection = mdlDirection;
}

void cModel::setSpeed(float mdlSpeed)
{
	m_mdlSpeed = mdlSpeed;
}

void cModel::setIsActive(bool mdlIsActive)
{
	m_IsActive = mdlIsActive;
}

//Set the model dimensions to the largest dimension of the model.
void cModel::setMdlDimensions(mdlDimensions mdlDims)
{
	m_Dimensions = mdlDims;
	m_mdlRadius = largestDimension(mdlDims.s_mdlheight, mdlDims.s_mdlWidth, mdlDims.s_mdldepth) / 2;
}

void cModel::setMdlRadius(float mdlRadius)
{
	m_mdlRadius = mdlRadius;
}

void cModel::setScale(glm::vec3 mdlScale)
{
	m_mdlScale = mdlScale;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Getters
// +++++++++++++++++++++++++++++++++++++++++++++

glm::vec3 cModel::getPosition()
{
	return m_mdlPosition;
}

GLfloat cModel::getRotation()
{
	return m_mdlRotation;
}

glm::vec3 cModel::getAxis()
{
	return m_axis;
}

glm::vec3 cModel::getDirection()
{
	return m_mdlDirection;
}

float cModel::getSpeed()
{
	return m_mdlSpeed;
}

bool cModel::isActive()
{
	return m_IsActive;
}

mdlDimensions cModel::getMdlDimensions()
{
	return m_Dimensions;
}

float cModel::getMdlRadius()
{
	return m_mdlRadius;
}

glm::vec3 cModel::getScale()
{
	return m_mdlScale;
}

void cModel::setTextureID(GLuint theTextureID)
{
	m_TextureID = theTextureID;
}

//Determines collision. 
//Uses squared values to avoid sqrt function.
bool cModel::SphereSphereCollision(glm::vec3 otherPosition, float otherRadius)
{
	const float squaredSumRadius = pow((m_mdlRadius + otherRadius), 2);
	return (squaredSumRadius > squaredDistance(otherPosition));
}

//Returns the squared distance between this object and the other object.
float cModel::squaredDistance(glm::vec3 otherPosition)
{

	return pow((otherPosition.x - m_mdlPosition.x), 2) + pow((otherPosition.y - m_mdlPosition.y), 2) + pow((otherPosition.z - m_mdlPosition.z), 2);
}

//Find the largest of the 3 dimensions.
float cModel::largestDimension(float height, float width, float depth)
{
	float currentMax = 0;
	
	//If the length is larger than current max, set currentMax to length.
	if (height > currentMax)
		currentMax = height;

	//Same for width.
	if (width > currentMax)
		currentMax = width;

	//And depth.
	if (depth > currentMax)
		currentMax = depth;

	//Return current.
	return currentMax;
}

//Check if model is out of render view, also known as the "killzone"
bool cModel::isInKillzone()
{
	return m_mdlPosition.z > KILLZONE_Z;
}

/*
=================================================================
Attach the input manager to the sprite
=================================================================
*/
void cModel::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}
/*
=================================================================
Attach the sound manager to the sprite
=================================================================
*/
void cModel::attachSoundMgr(cSoundMgr* soundMgr)
{
	m_SoundMgr = soundMgr;
}

cModel::~cModel()
{

}
