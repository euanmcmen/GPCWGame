#ifndef PLANETSPHERE_H
#define PLANETSPHERE_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include "GL\glut.h"
#include "cShapes.h"
#include "cSphere.h"
#include "cMaterial.h"


//This class spawns asteroids.  An asteroid, at the moment, is a moon.
class PlanetSphere : public cSphere
{
	public:
	PlanetSphere();
	void create(glm::vec3 position);
	void render(float elapsedTime);
	~PlanetSphere();

	private:
	glm::vec3 position;
	cTexture planetTexture;
	cMaterial planetMaterial;
	cSphere planet;
	float rotationSpeed = 2.0f;
};

#endif