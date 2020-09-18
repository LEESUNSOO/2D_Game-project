#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "UIT.h"

class stage1_SceneT : public gameNode
{
private:
	yerinaT* _player;
	stage1_MAPt* _map;
	RBenemyManager* _eMG;
	UIT* _ui;

public:
	


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	stage1_SceneT() {}
	~stage1_SceneT() {}
};

