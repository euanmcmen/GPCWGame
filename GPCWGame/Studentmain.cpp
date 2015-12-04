#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one

//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cShapes.h"
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
#include "PlanetSphere.h"
#include "Asteroid.h"

//Forward declare methods.
void SpawnEnemy(cModelLoader* enemyLoader, glm::vec3 scale, int type);
void SpawnAsteroid(cModelLoader* tinyAsteroidModel);

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

	// Create objects in game.
	//Player
	cTexture playerTexture;
	playerTexture.createTexture("Models/SmallShip/shipC.png");
	cModelLoader playerModel;
	playerModel.loadModel("Models/SmallShip/ship.obj", playerTexture);
	cPlayer thePlayer;
	thePlayer.initialise();
	thePlayer.setMdlDimensions(playerModel.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);

	//Enemy type 0
	cTexture standardEnemyTexture;
	standardEnemyTexture.createTexture("Models/Asteroid/asteroid.jpg");
	cModelLoader standardEnemyModel;
	standardEnemyModel.loadModel("Models/Asteroid/asteroid.obj", standardEnemyTexture);

	//Enemy type 1
	cTexture altEnemyTexture;
	altEnemyTexture.createTexture("Models/Satellite/texture.jpg");
	cModelLoader altEnemyModel;
	altEnemyModel.loadModel("Models/Satellite/Satellite.obj", altEnemyTexture);

	//Tiny asteroids
	cTexture tinyAsteroidTexture;
	tinyAsteroidTexture.createTexture("Models/TinyAsteroid/TinyAsteroid.tga");
	cModelLoader tinyAsteroidModel;
	tinyAsteroidModel.loadModel("Models/TinyAsteroid/TinyAsteroid.obj", tinyAsteroidTexture);

	//Jupiter
	PlanetSphere jupiter;
	jupiter.create(glm::vec3(-30, 30, -150));

	//Crete background star textures.
	cTexture starTexture;
	starTexture.createTexture("Images/star.png");
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(200.0f, 200.0f, 200.0f));

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
	LPCSTR gameFonts[1] = {"Fonts/digital-7.ttf"};

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/bgm.wav", "Audio/explosion.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Explosion", gameSounds[1]);

	// Create third person camera.
	cCamera tpvCamera;
	tpvCamera.setTheCameraPos(glm::vec3(0.0f, 1.0f, 20.0f));
	tpvCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, -60.0f));
	tpvCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	tpvCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	tpvCamera.setTheProjectionMatrix(75.0f, tpvCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	tpvCamera.update();

	// Create first person camera.
	cCamera fpvCamera;
	fpvCamera.setTheCameraPos(thePlayer.getPosition() + glm::vec3(0, 0, -2));
	fpvCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, -60.0f));
	fpvCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	fpvCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	fpvCamera.setTheProjectionMatrix(75.0f, fpvCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	fpvCamera.update();

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//Set enemy spawn values.
	float enemySpawnInterval = 0.4f;
	float enemySpawnAt = 1.0f;
	int enemyIndex = 0;
	int collisionIndex = 0;

	//Set tiny asteroid spawn values.
	float asteroidSpawnInterval = 0.1f;
	float asteroidSpawnAt = 0.0f;

	//Set the space unit countdown values.
	//Counts down in 100's.  Displayed to the player.
	int spaceUnits = 10000;  
	int spaceUnitsDecAt = 2;
	int spaceUnitsInterval = 1;
	int spaceUnitsDecrement = 100;

	//variable to control the spawning of the objects.  Not displayed to the player.
	float runTime = 0.0f;  
	
	//String messages to display to the player.
	string outputMsg;
	string spaceUnitsMsg;
	string gameOverMsg;

	//Play background music.
	theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);

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
			glLoadMatrixf((GLfloat*)&tpvCamera.getTheViewMatrix());
		else if (cameraIndex == 1)
			glLoadMatrixf((GLfloat*)&fpvCamera.getTheViewMatrix());

		theStarField.render(0.0f);
		jupiter.render(elapsedTime);
		sunMaterial.useMaterial();
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();

		//Update the game while the player has not been hit.
		if (!isPlayerHit)
		{

			//Update the player.
			playerModel.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getAxis(), thePlayer.getScale());
			thePlayer.update(elapsedTime);

			//If the elapsed time is larger than the enemyspawnat value, spawn an enemy.
			if (runTime > enemySpawnAt)
			{
				//Spawn an enemy.
				//Use & to pass a pointer to the value, rather than the value itself.
				SpawnEnemy(&standardEnemyModel, glm::vec3(2, 2, 2), 0);

				//Increment enemy spawn index.
				enemyIndex++;

				//If enemy index is divisable by 5, spawn an alt enemy.
				if (enemyIndex % 5 == 0)
					SpawnEnemy(&altEnemyModel, glm::vec3(1, 1, 1), 1);

				//Increase enemySpawnAt
				enemySpawnAt += enemySpawnInterval;
			}

			//If the elapsed time is larger than the asteroidspawnat value, spawn an asteroid.
			if (runTime > asteroidSpawnAt)
			{
				//Spawn asteroid
				SpawnAsteroid(&tinyAsteroidModel);

				//Increment asteridspawnat
				asteroidSpawnAt += asteroidSpawnInterval;
			}

			//If the elapsed time is divisable by 2, count down the space distance units.
			if (runTime > spaceUnitsDecAt && spaceUnits > 0)
			{
				//Decrement space units
				spaceUnits -= spaceUnitsDecrement;

				//Increase decat
				spaceUnitsDecAt += spaceUnitsInterval;
			}

			//Iterate over each enemy.
			for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
			{
				if ((*enemyIterator)->isActive())
				{
					//Render enemy based on type.
					if ((*enemyIterator)->getType() == 0)
						standardEnemyModel.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getAxis(), (*enemyIterator)->getScale());
					else if ((*enemyIterator)->getType() == 1)
						altEnemyModel.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getAxis(), (*enemyIterator)->getScale());						
					
					//Update the enemy.
					(*enemyIterator)->update(elapsedTime);

					//Check if player is colliding with the player.
					if (thePlayer.SphereSphereCollision((*enemyIterator)->getPosition(), (*enemyIterator)->getMdlRadius()) && !isPlayerHit)
					{
						//Set player hit
						isPlayerHit = true;
						theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
					}

					//If the enemy goes into the killzone, set it to inactive.
					if ((*enemyIterator)->isInKillzone())
					{
						//Disable the enemy so it isn't rendererd or updated.
						(*enemyIterator)->setIsActive(false);
					}
				}
			}

			//Iterate over each tiny asteroid.
			for (vector<Asteroid*>::iterator asteroidIterator = theTinyAsteroids.begin(); asteroidIterator != theTinyAsteroids.end(); ++asteroidIterator)
			{
				if ((*asteroidIterator)->isActive())
				{
					{
						tinyAsteroidModel.renderMdl((*asteroidIterator)->getPosition(), (*asteroidIterator)->getRotation(), (*asteroidIterator)->getAxis(), (*asteroidIterator)->getScale());
						(*asteroidIterator)->update(elapsedTime);
					}

					//If the enemy goes into the killzone, set it to inactive.
					if ((*asteroidIterator)->isInKillzone())
					{
						//Disable the enemy so it isn't rendererd or updated.
						(*asteroidIterator)->setIsActive(false);
					}
				}
			}

			//Check for victory condition.
			if (spaceUnits <= 0)
			{
				//Set victory message.
				gameOverMsg = "You have escaped the asteroid field!";

				//Delete all objects
				theEnemy.clear();
				theTinyAsteroids.clear();

				//Display victory text when the victory condition is met.
				glPushMatrix();
				theOGLWnd.setOrtho2D(windowWidth, windowHeight);
				theFontMgr->getFont("SevenSeg")->printText(gameOverMsg.c_str(), FTPoint((windowWidth / 3), windowHeight / 2, 0.0f), colour3f(0, 255.0f, 0)); // uses c_str to convert string to LPCSTR
				glPopMatrix();
			}
			else
			{
				//Display gameplay text if the victory condition isn't met.
				glPushMatrix();
				theOGLWnd.setOrtho2D(windowWidth, windowHeight);
				theFontMgr->getFont("SevenSeg")->printText("Avoid the asteroids and escape the asteroid field!", FTPoint(10, 35, 0.0f), colour3f(0, 0, 255.0f));
				theFontMgr->getFont("SevenSeg")->printText(("Distance remaining to exit: " + to_string(spaceUnits) + " space units.").c_str(), FTPoint(10, 70, 0.0f), colour3f(0, 0, 255.0f));
				glPopMatrix();
			}

			//Increment runtime
			runTime += elapsedTime;
		}
		
		//If the player is not not hit, so hit, then show game over.
		else
		{
			//Set destroyed message.
			gameOverMsg = "Player destroyed.  Press Return to restart.";

			//Stop the music.
			theSoundMgr->getSnd("Theme")->stopAudio();

			//Delete all objects
			theEnemy.clear();
			theTinyAsteroids.clear();

			//Check for return key press.
			thePlayer.checkForRestart();

			//Update strings.
			glPushMatrix();
			theOGLWnd.setOrtho2D(windowWidth, windowHeight);
			theFontMgr->getFont("SevenSeg")->printText(gameOverMsg.c_str(), FTPoint((windowWidth / 3), windowHeight / 2, 0.0f), colour3f(255.0f, 0, 0)); // uses c_str to convert string to LPCSTR
			glPopMatrix();
		}

		//If the restart button is pressed, spawn the enemies again.
		if (isRestarting)
		{
			//Set the player hit status to false.
			isPlayerHit = false;

			//Clear the destroyed message.
			gameOverMsg = "";

			//Initialise the spawnAt variables
			enemySpawnAt = enemySpawnInterval;
			asteroidSpawnAt = asteroidSpawnInterval;
			spaceUnitsDecAt = 2;

			//Reset counters
			enemyIndex = 0;
			spaceUnits = 10000;
			runTime = 0;
			
			//Play background music.
			theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);

			//Unset the flag.
			isRestarting = false;
		}

		//Update the fp camera position to the player's position.
		fpvCamera.setTheCameraPos(glm::vec3(thePlayer.getPosition().x, thePlayer.getPosition().y + 0.5f, 2.0f));
		fpvCamera.setTheCameraLookAt(glm::vec3(thePlayer.getPosition().x, thePlayer.getPosition().y, -60));
		fpvCamera.update();

		pgmWNDMgr->swapBuffers();

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

//Spawns an enemy which flys past the player - hopefully.
void SpawnEnemy(cModelLoader* enemyLoader, glm::vec3 scale, int type)
{
	//Create new enemy.
	theEnemy.push_back(new cEnemy);

	//Get the reference of this new enemy.  It'll be at the back of the vector.
	theEnemy.back()->initialise(scale, type);
	theEnemy.back()->setMdlDimensions(enemyLoader->getModelDimensions());

	return;
}

//Spawns a tiny asteroid which flys past the player.
void SpawnAsteroid(cModelLoader* tinyAsteroidModel)
{
	//Create new tiny asteroid.
	theTinyAsteroids.push_back(new Asteroid);

	//Get the reference of this new tiny asteroid.  It'll be at the back of the vector. 
	theTinyAsteroids.back()->initialise(glm::vec3(1, 1, 1));

	return;
}