#ifndef ASTEROID_H
#define ASTEROID_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include "GL\glut.h"
#include "cShapes.h"
#include "cSphere.h"
#include "cMaterial.h"


//This class spawns asteroids.  An asteroid, at the moment, is a moon.
class AsteroidSpawner
{
	public:
	AsteroidSpawner();
	void SpawnAsteroid(int ySpawn);

	private:
	glm::vec3 spawnPosition;
	GLdouble speed;

};

#endif