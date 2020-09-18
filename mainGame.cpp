#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	
	//앞으로 메인게임 클래스 안에서는 씬들만 관리한다
	//그리고 각각의 씬들이 메인게임 역할을 하면 된다

	/*씬추가*/
	//SCENEMANAGER->addScene("픽셀충돌", new pixelCollision);
	//SCENEMANAGER->addScene("테스트씬", new sceneTest);
	//SCENEMANAGER->addScene("ini", new iniTestScene);
	//SCENEMANAGER->addScene("로딩화면", new loadingScene);
	//SCENEMANAGER->addScene("사운드", new soundTestScene);
	//SCENEMANAGER->addScene("애니메이션", new aniTestScene);
	//SCENEMANAGER->addScene("이펙트", new effectTestScene);
	//SCENEMANAGER->addScene("로테이트", new rotateTestScene);
	//SCENEMANAGER->addScene("탱크게임", new tankGameScene);
	//SCENEMANAGER->addScene("맵툴", new maptoolScene);

	//라비리비
	SCENEMANAGER->addScene("로딩씬", new loadingScene1);
	SCENEMANAGER->addScene("시작씬", new startScene1);
	SCENEMANAGER->addScene("메인메뉴", new mainMenuScene);
	SCENEMANAGER->addScene("배경선택", new bgChoiceScene1);
	SCENEMANAGER->addScene("맵툴씬", new maptoolScene1);
	SCENEMANAGER->addScene("테스트스테이지", new stage1_MAPt);
	//SCENEMANAGER->addScene("에리나", new yerinaT);
	SCENEMANAGER->addScene("타운", new town_SceneT);
	SCENEMANAGER->addScene("스테이지1-1", new stage1_SceneT);
	SCENEMANAGER->addScene("스테이지1-2", new stage1_1_SceneT);
	SCENEMANAGER->addScene("스테이지1-3", new stage1_2_SceneT);
	SCENEMANAGER->addScene("스테이지1-4", new stage1_3_SceneT);
	SCENEMANAGER->addScene("스테이지1-보스", new stage1_Boss_Scene);
	SCENEMANAGER->addScene("스테이지1-클리어", new stage1_clear_Scene);
	SCENEMANAGER->addScene("스테이지2-1", new stage2_1_SceneT);
	SCENEMANAGER->addScene("스테이지파이널보스", new stage_FinalBoss_Scene);
	SCENEMANAGER->addScene("파이널클리어", new stage2_clear_Scene);



	/*현재씬 설정*/
	SCENEMANAGER->loadScene("로딩씬");

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트
	SOUNDMANAGER->update();

	//이펙트매니져 업데이트
	EFFECTMANAGER->update();




	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene("로딩씬");
		SOUNDMANAGER->stop("스타트씬브금");// , SAVEDATA->getBgmSound());

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene("스테이지1-1");
	}
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

	//이펙트매니져 렌더
	EFFECTMANAGER->render();

	//타임매니져 렌더
	TIMEMANAGER->render(getMemDC());



//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}
