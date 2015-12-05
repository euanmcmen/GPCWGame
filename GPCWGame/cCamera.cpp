/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"

//Blank constructor for the camera.
cCamera::cCamera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

//Parameterised constructor for the camera.
cCamera::cCamera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

//Destructor for the camera.
cCamera::~cCamera()
{
	
}

//Sets the camera viewport.
void cCamera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

//Returns the viewport.
const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;
}

//Sets the camera projection matrix.
void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

//Sets the camera position.
void cCamera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

//Returns the camera position.
glm::vec3 cCamera::getTheCameraPos()
{
	return m_cameraPos;
}

//Sets the camera up vector.
void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

//Returns the up vector.
glm::vec3 cCamera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

//Sets the camera look at.
void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

//Returns the camera look at.
glm::vec3 cCamera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

//Sets the camera direction.
void cCamera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

//Returns the camera direction.
glm::vec3 cCamera::getTheCameraDirection()
{
	return m_cameraDirection;
}

//Sets the camera strafe.
void cCamera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

//Returns the camera strafe.
glm::vec3 cCamera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

//Sets aspect ratio.
void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width/height;
}

//Returns aspect ratio
GLfloat cCamera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

//Returns projection matrix.
glm::mat4 cCamera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

//Returns view matrix.
glm::mat4 cCamera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

//Sets camera view matrix.
void cCamera::setCamViewMatrix()
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraLookAt, m_cameraUpVector);
}

//returns camera view matrix.
glm::mat4 cCamera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

//Updates the camera.
void cCamera::update()
{
	setTheCameraDirection();
	setTheCameraStrafe();
	setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 300.0f);
	setCamViewMatrix();
}
