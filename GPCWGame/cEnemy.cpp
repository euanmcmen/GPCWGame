#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	
}

void cEnemy::spawn()
{
	//if (rand() % 2 == 0)
	//{
	//	cModel::m_mdlPosition.x = -PLAYFIELDX;
	//}
	//else
	//{
	//	cModel::m_mdlPosition.x = PLAYFIELDX;
	//}
	//cModel::m_mdlPosition.y = 0.0f;
	//cModel::m_mdlPosition.z = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	//cModel::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;
	//cModel::m_mdlDirection.x = -(float)glm::sin(cModel::m_mdlRotation);
	//cModel::m_mdlDirection.z = (float)glm::cos(cModel::m_mdlRotation);
	//cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;
	//cModel::m_IsActive = true;

	//if (rand() % 2 == 0)
	//{
	//	cModel::m_mdlPosition.x = NEGPLAYFIELDX;
	//}
	//else
	//{
	//	cModel::m_mdlPosition.x = PLAYFIELDX;
	//}

	cModel::m_mdlPosition.x = (ENEMY_MAX_X - ENEMY_MIN_X)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_X;
	cModel::m_mdlPosition.y = (ENEMY_MAX_Y - ENEMY_MIN_Y)*(double)rand() / (double)(RAND_MAX)+ENEMY_MIN_Y;
	cModel::m_mdlPosition.z = 50.0f;
	cModel::m_mdlRotation = 0; //No rotations!
	cModel::m_axis = glm::vec3(0, 1, 0);
	//cModel::m_mdlDirection.x = -(float)glm::sin(cModel::m_mdlRotation);
	//cModel::m_mdlDirection.z = (float)glm::cos(cModel::m_mdlRotation);
	cModel::m_mdlSpeed = 10.0f;
	cModel::m_IsActive = true;
}

void cEnemy::update(float elapsedTime)
{
	//cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	//if (cModel::m_mdlPosition.x > PLAYFIELDX)
	//	cModel::m_mdlPosition.x -= 2 * PLAYFIELDX;
	//if (cModel::m_mdlPosition.x < -PLAYFIELDX)
	//	cModel::m_mdlPosition.x += 2 * PLAYFIELDX;
	//if (cModel::m_mdlPosition.z > PLAYFIELDZ)
	//	cModel::m_mdlPosition.z -= 2 * PLAYFIELDZ;
	//if (cModel::m_mdlPosition.z < -PLAYFIELDZ)
	//	cModel::m_mdlPosition.z += 2 * PLAYFIELDZ;

	//Move model towards 0 on z axis.
	cModel::m_mdlPosition.z -= cModel::m_mdlSpeed * elapsedTime;
}

cEnemy::~cEnemy()
{

}

