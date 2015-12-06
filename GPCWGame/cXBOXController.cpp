#include "cXBOXController.h"

//Default constructor.
cXBOXController::cXBOXController()
{
	//Set the Controller Number to zero.
	controllerNum = 0;
}

//Returns the state of the controller.
XINPUT_STATE cXBOXController::GetState()
{
	//Zeroise the state
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	//Get the state
	XInputGetState(controllerNum, &controllerState);

	return controllerState;
}

bool cXBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(controllerNum, &controllerState);

	if (Result == ERROR_SUCCESS)
		return true;
	else
		return false;
}