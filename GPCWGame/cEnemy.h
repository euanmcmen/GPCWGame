#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "cModel.h"

class cEnemy : public cModel
{
public:
	cEnemy();

	void spawn(glm::vec3 scale);
	virtual void update(float elapsedTime);
	bool cEnemy::isInKillzone();
	int getType();
	void setType(int type);
	~cEnemy();
	

private:
	const float m_EnemyMinSpeed = 3.0f;
	const float m_EnemyMaxSpeed = 10.0f;
	const float m_EnemySpeedAdjustment = 2.5f;

	//For some reason, the enemies spawn differently from the player.
	const float ENEMY_MAX_X = 14;
	const float ENEMY_MIN_X = 0;
	const float ENEMY_MAX_Y = 5;
	const float ENEMY_MIN_Y = -5;
	const float ENEMY_KILLZONE_Z = 20;
	int TYPE = 0;
};
#endif