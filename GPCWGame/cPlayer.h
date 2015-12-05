#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "AsteroidAvoiderGame.h"
#include "cModel.h"
#include "cInputMgr.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void initialise();
	virtual void update(float elapsedTime);
	void checkForRestart();
	~cPlayer();
};
#endif