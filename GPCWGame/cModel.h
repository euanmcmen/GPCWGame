#ifndef _CMODEL_H
#define _CMODEL_H

#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "GameConstants.h"

class cModel
{
public:
	cModel();
	void setPosition(glm::vec3 mdlPosition);
	void setRotation(GLfloat mdlRotation);
	void setDirection(glm::vec3 mdlDirection);
	void setSpeed(float mdlSpeed);
	void setIsActive(bool mdlIsActive);
	void setMdlDimensions(mdlDimensions mdlDims);
	void setMdlRadius(float mdlRadius);
	void setScale(glm::vec3 mdlScale);
	void setTextureID(GLuint theTextureID);
	void setAxis(glm::vec3 axis);

	glm::vec3 getPosition();
	GLfloat getRotation();
	glm::vec3 getAxis();
	glm::vec3 getDirection();
	float getSpeed();
	bool isActive();
	mdlDimensions getMdlDimensions();
	float getMdlRadius();
	glm::vec3 getScale();

	//virtual void initialise() = 0; // Will be defined by the inheriting class.
	virtual void update(float elapsedTime) = 0;     // will be defined by inherting class
	bool SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius);
	bool isInKillzone();

	void attachInputMgr(cInputMgr* inputMgr);  // Attach the Input Manager
	void attachSoundMgr(cSoundMgr* soundMgr);  // Attach the Sound Manager

	~cModel();

private:
	//float lengthSQRD(glm::vec3 mdlLength);
	float squaredDistance(glm::vec3 otherLength);
	float largestDimension(float height, float width, float depth);
	float KILLZONE_Z = 20;

	GLuint m_TextureID;

protected:
	// Set the position of the model in world space, and set the rotation.
	glm::vec3 m_mdlPosition;
	GLfloat m_mdlRotation;
	glm::vec3 m_axis;
	glm::vec3 m_mdlScale;
	glm::vec3 m_mdlDirection;
	mdlDimensions m_Dimensions; // (width, height, depth)
	float m_mdlSpeed;
	bool m_IsActive;
	float m_mdlRadius;


	cInputMgr* m_InputMgr;
	cSoundMgr* m_SoundMgr;

};
#endif
