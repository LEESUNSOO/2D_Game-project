#pragma once
#include "gameNode.h"
#include "enemy.h"



struct fPos
{
	float x;
	float y;
};


class enemyManager : public gameNode
{
private:


	vector<enemy*> _vEnemy;	// �Ϲ� ��

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	enemyManager() {}
	~enemyManager() {}
};

