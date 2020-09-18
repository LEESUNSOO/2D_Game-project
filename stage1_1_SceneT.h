#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "RBenemyManager.h"
#include "stage_MAPt.h"
#include "UIT.h"

class stage1_1_SceneT : public gameNode
{
	yerinaT* _player;
	RBenemyManager* _eMG;
	stage1_1_MAPt* _map;
	UIT* _ui;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	stage1_1_SceneT(){}
	~stage1_1_SceneT(){}
};

