#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "AsteroidEscapeGame.h"
#include "cModel.h"
#include "cInputMgr.h"
#include "cXBOXController.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
	cXBOXController controller;
	float translationX = 0;
	float translationY = 0;
	bool cameraSwapEventHandled = false;
	bool shouldPlaySound = true;

public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void setUpXboxController();
	void initialise();
	virtual void update(float elapsedTime);
	void checkForRestart();
	bool checkIfShouldPlaySound();
	bool checkForExit();
	~cPlayer();
};
#endif