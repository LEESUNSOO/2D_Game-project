#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "UIT.h"

class stage2_1_SceneT : public gameNode
{
private:
	yerinaT* _player;
	stage2_1_MAPt* _map;
	RBenemyManager* _eMG;
	UIT* _ui;

	float count;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void savePoint();

	stage2_1_SceneT() {}
	~stage2_1_SceneT() {}
};

