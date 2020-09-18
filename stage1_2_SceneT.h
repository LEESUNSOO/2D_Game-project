#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "RBenemyManager.h"
#include "stage_MAPt.h"
#include "UIT.h"


class stage1_2_SceneT : public gameNode
{
private:


	yerinaT* _player;
	RBenemyManager* _eMG;
	stage1_2_MAPt* _map;
	UIT* _ui;



public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	stage1_2_SceneT() {}
	~stage1_2_SceneT() {}
};

