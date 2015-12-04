#include "PlanetSphere.h"


PlanetSphere::PlanetSphere()
{

}

PlanetSphere::~PlanetSphere()
{

}


void PlanetSphere::create(glm::vec3 position)
{
	//Push a new matrix onto the stack.
	glPushMatrix();

	//Initialise planet.
	planet = cSphere(40, 40, 40);

	//Create Asteriod texture
	planetTexture.createTexture("Images/Jupiter.png");

	//Initialise planet
	planet.initialise(planetTexture.getTexture(), position, glm::vec3(0, 0, 0));
	
	//Prepare the planet.
	planet.prepare(0.0f);
	
	//Pop the matrix from the stack.
	glPopMatrix();
}

void PlanetSphere::render(float elapsedTime)
{
	//Push a new matrix onto the stack.
	glPushMatrix();

	//Set rotation angle 
	planet.setRotAngle(planet.getRotAngle() + (rotationSpeed*elapsedTime));

	//Render asteroid.
	planet.render(planet.getRotAngle());

	//Pop the matrix from the stack.
	glPopMatrix();
}