#pragma once
#include "gameNode.h"
/*앞으로는 씬 헤더파일만 추가해준다*/
//#include "pixelCollision.h"
//#include "sceneTest.h"
//#include "loadingScene.h"
//#include "soundTestScene.h"
//#include "effectTestScene.h"
//#include "maptoolScene.h"

#include "loadingScene1.h"
#include "startScene1.h"
#include "mainMenuScene.h"
#include "bgChoiceScene1.h"
#include "mapToolScene1.h"
#include "stage_MAPt.h"
#include "yerinaT.h"
#include "town_SceneT.h"
#include "stage1_SceneT.h"
#include "stage1_1_SceneT.h"
#include "stage1_2_SceneT.h"
#include "stage1_3_SceneT.h"
#include "stage1_Boss_Scene.h"
#include "stage1_clear_Scene.h"
#include "stage2_1_SceneT.h"
#include "stage_FinalBoss_Scene.h"
#include "stage2_clear_Scene.h"
#include "RBenemyManager.h"

class mainGame : public gameNode
{
	yerinaT* _player;
	RBenemyManager* _eMG;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

