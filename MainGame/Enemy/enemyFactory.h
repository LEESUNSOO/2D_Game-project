#pragma once
#include "RBenemy.h"

class enemyFactory
{
public:

	RBenemy* createEnemy(ENEMY_TYPE _enum);

};

