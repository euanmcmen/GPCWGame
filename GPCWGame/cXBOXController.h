#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

#include <Windows.h>
#include <XInput.h>

class cXBOXController
{
private:
	XINPUT_STATE controllerState;
	int controllerNum;
public:
	cXBOXController();
	XINPUT_STATE GetState();
	bool IsConnected();

};

#endif