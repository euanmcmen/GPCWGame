#include "cModel.h"

cModel::cModel()
{
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = 0.0f;
	m_axis = glm::vec3(0, 0, 0);
	m_mdlDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlSpeed = 0.0f;
	m_IsActive = false;
	m_mdlScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	m_TextureID = 0;
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
	return m_mdlPosition + offset;
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

void cModel::initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 axis, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive)
{
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setAxis(axis);
	setScale(mdlScale);
	setDirection(mdlDirection);
	setSpeed(mdlSpeed);
	setIsActive(mdlIsActive);
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, axis.x, axis.y, axis.z);
	glTranslatef(mdlPos.x,mdlPos.y,mdlPos.z);
}

bool cModel::SphereSphereCollision(glm::vec3 otherPosition, float otherRadius)
{
	const float squaredSumRadius = pow((m_mdlRadius + otherRadius), 2);
	return (squaredSumRadius > squaredDistance(otherPosition));
}

void cModel::setOffset(glm::vec3 theoffset)
{
	offset = theoffset;
}

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
