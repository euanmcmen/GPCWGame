#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one

//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cLaser.h"
#include "cPlanet.h"

//#include "tardisWarsGame.h"

//Forward declare methods.
void SpawnEnemy(cModelLoader* enemyLoader,int type, glm::vec3 scale);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	//The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails
        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	// Create Texture maps
	cTexture playerTexture;
	playerTexture.createTexture("Models/tardis.tga");
	cTexture standardEnemyTexture;
	standardEnemyTexture.createTexture("Models/SpaceShip/sh3.jpg");
	cTexture altEnemyTexture;
	altEnemyTexture.createTexture("Models/dalek/dalek.jpg");
	cTexture planetTexture;
	planetTexture.createTexture("Models/Jupiter/Jupiter.png");
	cTexture starTexture;
	starTexture.createTexture("Images/star.png");

	// the starfield
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);

	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 2, -100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// Create close third person camera.
	cCamera ctpvCamera;
	ctpvCamera.setTheCameraPos(glm::vec3(0.0f, 1.0f, 20.0f));
	ctpvCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, -60.0f));
	ctpvCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	ctpvCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	ctpvCamera.setTheProjectionMatrix(75.0f, ctpvCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	ctpvCamera.update();

	// Create far third person camera.
	cCamera ftpvCamera;
	ftpvCamera.setTheCameraPos(glm::vec3(0.0f, 3.0f, 40.0f));
	ftpvCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, -60.0f));
	ftpvCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	ftpvCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	ftpvCamera.setTheProjectionMatrix(75.0f, ftpvCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	ftpvCamera.update();

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Models
	cModelLoader playerModel;
	playerModel.loadModel("Models/tardis1314.obj", playerTexture); // Player

	cModelLoader standardEnemyModel;
	standardEnemyModel.loadModel("Models/SpaceShip/Sample_Ship.obj", standardEnemyTexture); // Enemy
	
	//cModelLoader altEnemyModel;
	//altEnemyModel.loadModel("Models/tardis1314.obj", playerTexture); // Enemy #2

	cModelLoader planetModel;
	planetModel.loadModel("Models/Jupiter/Jupiter.obj", planetTexture);

	//Set enemy spawn values.
	float enemySpawnInterval = 2.0f;
	float enemySpawnAt = 1.0f;
	int enemyIndex = 0;
	int collisionIndex = 0;

	//Set up player.
	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 0.0f, glm::vec3(0,0,0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(playerModel.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);

	//Set up jupiter.
	cPlanet jupiter;
	jupiter.initialise(glm::vec3(0, 0, 100), 0.0f, glm::vec3(0, 0, 0), glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), 0.0f, true);
	jupiter.setMdlDimensions(planetModel.getModelDimensions());

	float runTime = 0.0f;
	string outputMsg;
	string playerDestroyedMessage;

	//Play background music.
	//theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);

   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);

		//Load identity matrix.
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Select the main camera based on index.
		if (cameraIndex == 0)
			glLoadMatrixf((GLfloat*)&ctpvCamera.getTheViewMatrix());
		else if (cameraIndex == 1)
			glLoadMatrixf((GLfloat*)&ftpvCamera.getTheViewMatrix());

		theStarField.render(0.0f);
		sunMaterial.useMaterial();
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();

		//Render planet.
		planetModel.renderMdl(jupiter.getPosition(), jupiter.getRotation(), jupiter.getAxis(), jupiter.getScale());
		jupiter.update(elapsedTime);

		//If the elapsed time is larger than the enemyspawnat value, spawn an enemy.
		if (runTime > enemySpawnAt)
		{
			//Spawn an enemy.
			//Use & to pass a pointer to the value, rather than the value itself.
			SpawnEnemy(&standardEnemyModel, 0, glm::vec3(5,5,5));

			//Increment enemy spawn index.
			enemyIndex++;

			//If enemy index is divisable by 5, spawn an alt enemy.
			if (enemyIndex % 5 == 0)
				SpawnEnemy(&playerModel, 1, glm::vec3(1, 1, 1));

			//Increase enemySpawnAt
			enemySpawnAt += enemySpawnInterval;
		}

		//Iterate over each enemy.
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				//if the enemy is active, update and render it.
				if ((*enemyIterator)->getType() == 0)
				{
					standardEnemyModel.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getAxis(), (*enemyIterator)->getScale());
					(*enemyIterator)->update(elapsedTime);
				}
				else if ((*enemyIterator)->getType() == 1)
				{
					playerModel.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getAxis(), (*enemyIterator)->getScale());
					(*enemyIterator)->update(elapsedTime);
				}

				//Check if player is colliding with the player.
				//if (thePlayer.SphereSphereCollision((*enemyIterator)->getPosition(), (*enemyIterator)->getMdlRadius())  && !isPlayerHit)
				//{
				//	//Set player hit
				//	isPlayerHit = true;
				//}

				//If the enemy goes into the killzone, set it to inactive.
				if ((*enemyIterator)->isInKillzone())
				{
					//Disable the enemy so it isn't rendererd or updated.
					(*enemyIterator)->setIsActive(false);
				}
			}
			else
			{
				//enemyIterator = theEnemy.erase(enemyIterator);
			}
		}

		//Update the player if it hasn't been hit.
		if (!isPlayerHit)
		{
			playerModel.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getAxis(), thePlayer.getScale());
			thePlayer.update(elapsedTime);
		}
		else
		{
			//Set destroyed message.
			playerDestroyedMessage = "Player destroyed.  Press Return to restart.";

			//Delete all enemies.
			theEnemy.clear();

			//Check for return key press.
			thePlayer.checkForRestart();
		}

		//If the restart button is pressed, spawn the enemies again.
		if (isRestarting)
		{
			//Set the player hit status to false.
			isPlayerHit = false;

			//Clear the destroyed message.
			playerDestroyedMessage = "";

			//Set the next enemy spawn to be <interval> seconds after elapsed time.
			enemySpawnAt = enemySpawnInterval;

			//reset the counter.
			runTime = 0;
			
			//Unset the flag.
			isRestarting = false;
		}
		
		//Iterate for each laser.
		//This will probably be removed as shooting will not exist in this game.
		//for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
		//{
		//	if ((*laserIterartor)->isActive())
		//	{
		//		planetModel.renderMdl((*laserIterartor)->getPosition(), (*laserIterartor)->getRotation(), (*laserIterartor)->getAxis(), (*laserIterartor)->getScale());
		//		(*laserIterartor)->update(elapsedTime);
		//	}
		//}

		//outputMsg = to_string(collisionIndex);
		//outputMsg = to_string(theEnemy.size()); // convert float to string		
		outputMsg = to_string(floorf(runTime));
		
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);
		theFontMgr->getFont("Space")->printText("Asteroid Avoider", FTPoint(10, 35, 0.0f), colour3f(0.0f,255.0f,0.0f));
		theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(windowWidth/1.2f, 35, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("Space")->printText(playerDestroyedMessage.c_str(), FTPoint((windowWidth/10), windowHeight/2, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		glPopMatrix();

		pgmWNDMgr->swapBuffers();

		if (!isPlayerHit)
			runTime += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

void SpawnEnemy(cModelLoader* enemyLoader, int type, glm::vec3 scale)
{
	//Create new enemy.
	theEnemy.push_back(new cEnemy);

	//Get the reference of this new enemy.  It'll be at the back of the vector.
	theEnemy.back()->spawn(scale);
	theEnemy.back()->setMdlDimensions(enemyLoader->getModelDimensions());
	theEnemy.back()->setType(type);
	
	return;
}