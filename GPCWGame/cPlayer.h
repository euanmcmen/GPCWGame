#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "cModel.h"
#include "cInputMgr.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;

	//Player bounds within the screen.
	const float PLAYER_MAX_X = 7;
	const float PLAYER_MIN_X = -7;
	const float PLAYER_MAX_Y = 5;
	const float PLAYER_MIN_Y = -5;

	//Clamp
	void clampPosition();
public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	virtual void update(float elapsedTime);
	void checkForRestart();
	~cPlayer();
};
#endif