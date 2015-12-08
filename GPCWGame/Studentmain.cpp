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
#include "SpaceObject.h"
#include "PlanetSphere.h"

//Forward declare methods.
void SpawnAsteroid(cModelLoader* asteroidLoader);
void SpawnTinyAsteroid(cModelLoader* tinyAsteroidModel);
void SpawnBattery(cModelLoader* batteryModel);

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

    //Attach our OpenGL window to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	//Attach the keyboard manager
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
	thePlayer.setUpXboxController();

	//Asteroid model
	cTexture asteroidTexture;
	asteroidTexture.createTexture("Models/Asteroid/asteroid.jpg");
	cModelLoader asteroidModel;
	asteroidModel.loadModel("Models/Asteroid/asteroid.obj", asteroidTexture);

	//Battery model
	cTexture batteryTexture;
	batteryTexture.createTexture("Models/PowerPickup/Texture2.jpg");
	cModelLoader batteryModel;
	batteryModel.loadModel("Models/PowerPickup/PowerPickup.obj", batteryTexture);

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

	theFontMgr->addFont("SevenSeg", gameFonts[0], 28);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/bgm.wav", "Audio/explosion.wav", "Audio/powerup.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Explosion", gameSounds[1]);
	theSoundMgr->add("Powerup", gameSounds[2]);

	//Play background music.
	theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);

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
	fpvCamera.setTheCameraPos(thePlayer.getPosition());
	fpvCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, -60.0f));
	fpvCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	fpvCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	fpvCamera.setTheProjectionMatrix(75.0f, fpvCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	fpvCamera.update();

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//Set Obstacle spawn values.
	float asteroidSpawnInterval = 0.4f;
	float asteroidSpawnAt = 1.0f;

	//Set Obstacle spawn values.
	int batterySpawnInterval = 5;
	int batterySpawnAt = 5;

	//Set tiny asteroid spawn values.
	float TinyAsteroidSpawnInterval = 0.1f;
	float TinyAsteroidSpawnAt = 0.0f;

	//Set the ship power decrement values
	//The ship power drecrements by 10 every 5 seconds, giving 50 seconds of power.
	int powerDecAt = 5;
	int powerDecInterval = 5;
	int powerDecAmount = 10;

	//Set the space unit countdown values.
	//SpaceUnits counts down in steps of 100, and is Displayed to the player.
	//The game is designed to last 100 seconds.
	int spaceUnits = 10000;  
	int spaceUnitsDecAt = 1;
	int spaceUnitsInterval = 1;
	int spaceUnitsDecAmount = 100;

	//variable to control the spawning of the objects.  Not displayed to the player.
	float runTime = 0.0f;  

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

		//Render background scene components.
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

			//If the runtime is larger than the asteroid spawn at value, spawn an Asteroid.
			if (runTime > asteroidSpawnAt)
			{
				//Spawn an Obstacle.
				//Use & to pass a pointer to the value, rather than the value itself.
				SpawnAsteroid(&asteroidModel);

				//Increase obstacleSpawnAt
				asteroidSpawnAt += asteroidSpawnInterval;
			}

			//If runtime is larger than the battery spawn value, spawn battery.
			if (runTime > batterySpawnAt)
			{
				//Spawn a battery.
				SpawnBattery(&batteryModel);

				//Increase battery spawn at.
				batterySpawnAt += batterySpawnInterval;
			}

			//If the runtime is larger than the tiny asteroid spawn value, spawn a tiny asteroid.
			if (runTime > TinyAsteroidSpawnAt)
			{
				//Spawn asteroid
				SpawnTinyAsteroid(&tinyAsteroidModel);

				//Increment asteridspawnat
				TinyAsteroidSpawnAt += TinyAsteroidSpawnInterval;
			}

			//If the runtime is larger the decrement space units time, decrement space units.
			if (runTime > spaceUnitsDecAt && spaceUnits > 0)
			{
				//Decrement space units
				spaceUnits -= spaceUnitsDecAmount;

				//Increase space units dec at
				spaceUnitsDecAt += spaceUnitsInterval;
			}

			//If the runtime if larger than the power decrement at time, decrement the power.
			if (runTime > powerDecAt && shipPower > 0)
			{
				//Decrement power
				shipPower -= powerDecAmount;

				//Increase power dec at.
				powerDecAt += powerDecInterval;
			}

			//Iterate over each Asteroid.
			for (vector<SpaceObject*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
			{
				//If the Asteroid is active...
				if ((*asteroidIterator)->isActive())
				{
					//Update and render the asteroid..
					asteroidModel.renderMdl((*asteroidIterator)->getPosition(), (*asteroidIterator)->getRotation(), (*asteroidIterator)->getAxis(), (*asteroidIterator)->getScale());
					(*asteroidIterator)->update(elapsedTime);

					//Check if player is colliding with the Asteroid.
					if (thePlayer.SphereSphereCollision((*asteroidIterator)->getPosition(), (*asteroidIterator)->getMdlRadius()) && !isPlayerHit)
					{
						//Set player hit
						isPlayerHit = true;

						if (thePlayer.checkIfShouldPlaySound())
							theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
					}
				}
			}

			//Iterate over each battery.
			for (vector<SpaceObject*>::iterator batteryIter = theBatteries.begin(); batteryIter != theBatteries.end(); ++batteryIter)
			{
				if ((*batteryIter)->isActive())
				{
					batteryModel.renderMdl((*batteryIter)->getPosition(), (*batteryIter)->getRotation(), (*batteryIter)->getAxis(), (*batteryIter)->getScale());
					(*batteryIter)->update(elapsedTime);

					//Check if the player is colliding with the battery.
					if (thePlayer.SphereSphereCollision((*batteryIter)->getPosition(), (*batteryIter)->getMdlRadius()))
					{
						//Increase power.
						shipPower += 20;

						//Cap power at 100%.
						if (shipPower > 100)
							shipPower = 100;

						//Disable battery
						(*batteryIter)->setIsActive(false);

						//Play battery collect sound.
						if (thePlayer.checkIfShouldPlaySound())
							theSoundMgr->getSnd("Powerup")->playAudio(AL_TRUE);
					}
				}
			}

			//Iterate over each tiny asteroid.
			for (vector<SpaceObject*>::iterator tinyasteroidIterator = theTinyAsteroids.begin(); tinyasteroidIterator != theTinyAsteroids.end(); ++tinyasteroidIterator)
			{
				//If the asteroid is active..
				if ((*tinyasteroidIterator)->isActive())
				{
					{
						//Update and render.
						tinyAsteroidModel.renderMdl((*tinyasteroidIterator)->getPosition(), (*tinyasteroidIterator)->getRotation(), (*tinyasteroidIterator)->getAxis(), (*tinyasteroidIterator)->getScale());
						(*tinyasteroidIterator)->update(elapsedTime);
					}
				}
			}

			//Check for victory condition.
			if (spaceUnits <= 0)
			{
				//Delete all objects
				theAsteroids.clear();
				theTinyAsteroids.clear();
				theBatteries.clear();
			}

			//Update the fp camera position to the player's position.
			fpvCamera.setTheCameraPos(glm::vec3(thePlayer.getPosition()));
			fpvCamera.setTheCameraLookAt(glm::vec3(thePlayer.getPosition().x, thePlayer.getPosition().y, -60));
			fpvCamera.update();

			//Increment runtime
			runTime += elapsedTime;
		}
		
		//If the player is not not hit, so hit, then show game over.
		else
		{
			//Stop the music.
			theSoundMgr->getSnd("Theme")->stopAudio();

			//Delete all objects
			theAsteroids.clear();
			theTinyAsteroids.clear();
			theBatteries.clear();

			//Check for return key press.
			thePlayer.checkForRestart();
		}

		//If the restart button is pressed, spawn the objects again.
		if (isRestarting)
		{
			//Set the player hit status to false.
			isPlayerHit = false;

			//Initialise the spawnAt variables
			asteroidSpawnAt = asteroidSpawnInterval;
			TinyAsteroidSpawnAt = TinyAsteroidSpawnInterval;
			batterySpawnAt = batterySpawnInterval;
			spaceUnitsDecAt = spaceUnitsInterval;
			powerDecAt = powerDecInterval;

			//Reset counters
			spaceUnits = 10000;
			runTime = 0;
			shipPower = 100;
			
			//Play background music.
			if (thePlayer.checkIfShouldPlaySound())
			{
				theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
			}

			//Unset the flag.
			isRestarting = false;
		}

		//Display text.
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);

		//String messages to display to the player.
		string spaceUnitsMsg;
		string shipPowerMsg;
		string quitMsg = "Press Escape/Back to quit";
		string gameOverMsg = "Player destroyed.  Press Return/Start to restart.";
		string victoryText = "You have escaped the asteroid field!";

		//Set up text colours
		colour3f whiteTextColour = colour3f(255.0f, 255.0f, 255.0f);
		colour3f redTextColour = colour3f(255.0f, 0, 0);
		colour3f greenTextColour = colour3f(0, 255.0f, 0);

		//Set up text positions.
		FTPoint soundTextLine = FTPoint(windowWidth - 150, 40);
		FTPoint textLine1 = FTPoint(10, windowHeight-70);
		FTPoint textLine2 = FTPoint(10, windowHeight - 40);
		
		//Display sound text in its own area of the screen.
		theFontMgr->getFont("SevenSeg")->printText(soundText.c_str(), soundTextLine, whiteTextColour);

		//Display gameplay text if the victory condition isn't met.
		if (!isPlayerHit && spaceUnits>0)
		{
			//Display the distance to the end of the asteroid field.
			theFontMgr->getFont("SevenSeg")->printText(("Distance remaining to exit: " + to_string(spaceUnits) + " space units.").c_str(), textLine1, whiteTextColour);

			//Check if the ship has power.
			if (shipPower > 0)
				theFontMgr->getFont("SevenSeg")->printText(("Remaining ship power: " + to_string(shipPower) + "%").c_str(), textLine2, whiteTextColour);
			else 
				theFontMgr->getFont("SevenSeg")->printText("No power!  Controls offline.", textLine2, redTextColour);
		}

		//Display gameover message.
		if (isPlayerHit)
		{
			theFontMgr->getFont("SevenSeg")->printText(gameOverMsg.c_str(), textLine1, redTextColour); //Defeat text to be red.
			theFontMgr->getFont("SevenSeg")->printText(quitMsg.c_str(), textLine2, redTextColour); 
		}

		//If victory condition is met, display message.
		if (spaceUnits <= 0)
		{
			theFontMgr->getFont("SevenSeg")->printText(victoryText.c_str(), textLine1, greenTextColour); // Victory text to be green.
			theFontMgr->getFont("SevenSeg")->printText(quitMsg.c_str(), textLine2, greenTextColour);
		}
		glPopMatrix();

		//Check for sound toggle event.
		if (thePlayer.checkIfShouldPlaySound() && !soundEventHandled)
		{
			//Play the music.
			theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
			soundEventHandled = true;
		}
		else if (!thePlayer.checkIfShouldPlaySound() && !soundEventHandled)
		{
			//Stop the music.
			theSoundMgr->getSnd("Theme")->stopAudio();
			soundEventHandled = true;
		}

		//Check for window closing event.
		if (thePlayer.checkForExit())
		{
			DestroyWindow(pgmWNDMgr->getWNDHandle());
		}

		pgmWNDMgr->swapBuffers();

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

//Spawns an Obstacle which flys past the player - hopefully.
void SpawnAsteroid(cModelLoader* asteroidLoader)
{
	//Create new Asteroid.
	theAsteroids.push_back(new SpaceObject);

	//Get the reference of this new Asteroid.  It'll be at the back of the vector.
	theAsteroids.back()->initialise(1, glm::vec3(2, 2, 2), 20.0f, true);

	//Set the asteroid's collision sphere dimensions
	theAsteroids.back()->setMdlDimensions(asteroidLoader->getModelDimensions());

	return;
}

void SpawnBattery(cModelLoader* batteryLoader)
{
	//Create new battery.
	theBatteries.push_back(new SpaceObject);

	//Get the reference of this new battery.  It'll be at the back of the vector.
	theBatteries.back()->initialise(0.5f, glm::vec3(1, 1, 1), 20.0f, false);

	//Set the batteryLoader's collision sphere dimensions
	theAsteroids.back()->setMdlDimensions(batteryLoader->getModelDimensions());

	return;
}

//Spawns a tiny asteroid which flys past the player.
void SpawnTinyAsteroid(cModelLoader* tinyAsteroidModel)
{
	//Create new tiny asteroid.
	theTinyAsteroids.push_back(new SpaceObject);

	//Get the reference of this new tiny asteroid.  It'll be at the back of the vector. 
	theTinyAsteroids.back()->initialise(2, glm::vec3(1, 1, 1), 75.0f, false);

	return;
}