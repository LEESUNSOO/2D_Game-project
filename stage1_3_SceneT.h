#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "UIT.h"

class stage1_3_SceneT : public gameNode
{
	yerinaT* _player;
	stage1_3_MAPt* _map;
	RBenemyManager* _eMG;
	UIT* _ui;

	int alpha, count;
	bool isAlpha;
	float bgLoopCount;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void savePoint();

	stage1_3_SceneT(){}
	~stage1_3_SceneT(){}
};

