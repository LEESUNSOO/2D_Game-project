#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "UIT.h"

struct TAGBOX
{
	image* image;
	float x;
	float y;
	float speed;
	float gravity;
	float angle;
	RECT rc;
	bool isUp;
	bool isActive;

};

#define RIVERS 100
class town_SceneT : public gameNode
{
	yerinaT* _player;
	town_MAP* _map;
	RBenemyManager* _eMG;
	UIT* _ui;

	TAGBOX _river[RIVERS];
	

	int index;
	int count;


public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void riverMove();


	town_SceneT(){}
	~town_SceneT(){}
};

