#pragma once
#include "gameNode.h"
#include "RBenemy.h"
#include "enemyFactory.h"
#include "stage_MAPt.h"
#include "RBboss.h"

class yerinaT;

class RBenemyManager : public gameNode
{
private:
	vector<RBenemy*> _vEnemy;
	vector<RBenemy*>::iterator _viEnemy;

	vector<string> _vEnemyInf;

	enemyFactory* _factory;

	tagPos _testPos[25];

	int _beAttactedNum;
	int _damsIndex[3];



	//boss
	ribbonBoss* _ribbonBoss;
	finalBoss* _finalBoss;
	//������ ��ȣ���� �Ѱ��ֱ�
	yerinaT* _player;

public:

	HRESULT init(void);
	void release(void);
	void update(stage_MAPt* _maps);
	void render(stage_MAPt* _maps);
	void enemyDirectionDecision();
	
	void playerAttactCollision();


	void load(int sceneNum);

	ribbonBoss* getRibbon() { return _ribbonBoss; }
	finalBoss* getFinalBoss() { return _finalBoss; }

	vector<RBenemy*> getVEnemy() { return _vEnemy; }

	void setPlayerLink(yerinaT* player) { _player = player; }


	RBenemyManager() {}
	~RBenemyManager() {}
};

