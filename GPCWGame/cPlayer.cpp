#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

//Attaches the input manager for the player.
void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

//Initialise the player with many "zero" values as the player is pretty concrete.  
//It spawns in the same place at the same orientation etc.
void cPlayer::initialise()
{
	//Model position and initialisation
	setPosition(glm::vec3(0,0,0));
	setRotation(0.0f);
	setAxis(glm::vec3(0, 0, 0));
	setScale(glm::vec3(1, 1, 1));
	setDirection(glm::vec3(0,0,0));
	setSpeed(5.0f);
	setIsActive(true);
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, 0, 0, 0);
	glTranslatef(mdlPos.x, mdlPos.y, mdlPos.z);
}

void cPlayer::setUpXboxController()
{
	//Set up xbox controller
	controller = cXBOXController();
}

//Updates the player.
void cPlayer::update(float elapsedTime)
{
	if (shipPower > 0)
	{
		//Check for movement through arrow keys
		//Only allow movement if the player is within the bounds of the screen.
		if (m_InputMgr->isKeyDown(VK_RIGHT))
		{
			if (m_mdlPosition.x <= (RIGHT_BOUND - 7))
				translationX = 1.0f;
		}

		if (m_InputMgr->isKeyDown(VK_LEFT))
		{
			if (m_mdlPosition.x >= (LEFT_BOUND + 7))
				translationX = -1.0f;
		}

		if (m_InputMgr->isKeyDown(VK_UP))
		{
			if (m_mdlPosition.y <= (TOP_BOUND - 2))
				translationY = 1;
		}

		if (m_InputMgr->isKeyDown(VK_DOWN))
		{
			if (m_mdlPosition.y >= BOTTOM_BOUND + 2)
				translationY = -1;
		}
	}

	//Change the camera.
	if (m_InputMgr->isKeyDown(0x43))  //C Key
	{
		if (cameraIndex == 0)
			cameraIndex = 1;
		else if (cameraIndex == 1)
			cameraIndex = 0;
	}

	if (m_InputMgr->isKeyDown(0x4D) && soundEventHandled)  //M Key
	{
		//Toggle sound.
		if (shouldPlaySound)
		{
			shouldPlaySound = false;
			soundText = "Sound: [OFF]";
		}
		else if (!shouldPlaySound)
		{
			shouldPlaySound = true;
			soundText = "Sound: [ON]";
		}

		//Set the event handled to false so it can be picked up by the main file.
		soundEventHandled = false;
	}


	//Check for input from the controller.
	if (controller.IsConnected())
	{
		if (shipPower > 0)
		{
			if (controller.GetState().Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				if (m_mdlPosition.x <= (RIGHT_BOUND - 7))
					translationX = 0.5f;
			}

			if (controller.GetState().Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				if (m_mdlPosition.x >= (LEFT_BOUND + 7))
					translationX = -0.5f;
			}

			if (controller.GetState().Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				if (m_mdlPosition.y <= (TOP_BOUND - 2))
					translationY = 0.5f;
			}

			if (controller.GetState().Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				if (m_mdlPosition.y >= BOTTOM_BOUND + 2)
					translationY = -0.5f;
			}
		}

		//Change the camera with the controller.
		if (controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			cameraIndex = 0;
		if (controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			cameraIndex = 1;


		//Switch sound on
		if (controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (!shouldPlaySound)
			{
				shouldPlaySound = true;
				soundText = "Sound: [ON]";

				//Set the event handled to false so it can be picked up by the main file.
				soundEventHandled = false;
			}
		}

		//Switch sound off.
		if (controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (shouldPlaySound)
			{
				shouldPlaySound = false;
				soundText = "Sound: [OFF]";

				//Set the event handled to false so it can be picked up by the main file.
				soundEventHandled = false;
			}
		}
	}

	//Create velocity vector.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = translationX;
	mdlVelocityAdd.y = translationY;
	mdlVelocityAdd.z = 0.0f;

	cModel::m_mdlDirection += mdlVelocityAdd;
	cModel::m_mdlPosition += m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	cModel::m_mdlDirection *= 0.7f;

	translationX = 0;
	translationY = 0;
}

//Sets the restart flag when return key is pressed.
void cPlayer::checkForRestart()
{
	if (m_InputMgr->isKeyDown(VK_RETURN) || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{
		isRestarting = true;
	}	
}

//Returns whether or not the sound should be played.
bool cPlayer::checkIfShouldPlaySound()
{
	return shouldPlaySound;
}

//Returns true when the user presses the exit key. 
//This is called from and processed by the main file.
bool cPlayer::checkForExit()
{
	if (m_InputMgr->isKeyDown(VK_ESCAPE) || controller.GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
	{
		return true;
	}

	return false;
}

cPlayer::~cPlayer()
{

}