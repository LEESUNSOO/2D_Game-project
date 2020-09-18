#include "stdafx.h"
#include "enemyFactory.h"


RBenemy * enemyFactory::createEnemy(ENEMY_TYPE _enum)
{
	RBenemy* _enemy;

	switch (_enum)
	{
	case MUSHROOM:
		_enemy = new mushRoom;
		break;

	case PUPPY:
		_enemy = new puppy;

		break;

	case RABBIT:
		_enemy = new rabbit;

		break;

	case CHICK:
		_enemy = new chick;

		break;

	case CHIPMUNK:
		_enemy = new chipmunk;

		break;

	case BEE:
		_enemy = new bee;
		break;


	case FLOWER:
		_enemy = new flower;
		break;
	default:
		break;

	}


	_enemy->init();

	return _enemy;
}
