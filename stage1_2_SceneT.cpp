#include "stdafx.h"
#include "stage1_2_SceneT.h"


HRESULT stage1_2_SceneT::init(void)
{

	_player = new yerinaT;
	_map = new stage1_2_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;

	SAVEDATA->setCurrentStage(STAGE3);

	_player->init();


	if (SAVEDATA->getPreviousStage() == STAGE4)
	{
		_player->setX(1280*2-30);		
		_player->setY(500);
	}
	else if (SAVEDATA->getPreviousStage() == STAGE2)
	{
		_player->setX(SAVEDATA->getX()[STAGE2] - 1280 * 2);	
		_player->setY(0);
	}
	else if (SAVEDATA->getX()[STAGE3] <= 0 && SAVEDATA->getY()[STAGE3])
	{
		_player->setX(1000);	
		_player->setY(500);
	}
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setGravity(SAVEDATA->getGravity()[STAGE3]);
	_player->setState(FALL);
	_player->setCurHp(SAVEDATA->getHp());

	//¸®º»À§Ä¡¼³Á¤
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());

	_map->init();
	_eMG->load(STAGE3); // ¸Ê·Îµå°¡ ¾Æ´Ï¶ó ¿¡³Ê¹Ì Á¤º¸ÀÌ´Ù!
	_eMG->init();
	_ui->init();

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("Ç®¸ÊÇÏ´Ã", "resource/mapBG/Ç®¸ÊÇÏ´Ã.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸ÊµÞ»ê", "resource/mapBG/Ç®¸ÊµÞ»ê.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸Ê¾Õ»êµÞµ¿»ê", "resource/mapBG/Ç®¸Ê¾Õ»êµÞµ¿»ê.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸Ê¾Õµ¿»êµÞÀÜµð", "resource/mapBG/Ç®¸Ê¾Õµ¿»êµÞÀÜµð.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸Ê¾ÕÀÜµð", "resource/mapBG/Ç®¸Ê¾ÕÀÜµð.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸ÊµÞÃµÀåÇ®", "resource/mapBG/Ç®¸ÊµÞÃµÀåÇ®.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸ÊÁß°£ÃµÀåÇ®", "resource/mapBG/Ç®¸ÊÁß°£ÃµÀåÇ®.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ç®¸Ê¾ÕÃµÀåÇ®", "resource/mapBG/Ç®¸Ê¾ÕÃµÀåÇ®.bmp", 1280, 720, true, MAGENTA);

	return S_OK;
}

void stage1_2_SceneT::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);
}

void stage1_2_SceneT::update(void)
{
	_player->update(_map);
	_map->update();
	_eMG->update(_map);
	_ui->update();

	CAMERAMANAGER->bgCameraUpdate("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó", _player->getX(), _player->getY(), 1280 * 2, 720);

	if (_player->getY() < 0 && _player->getX() < 896)
	{

		SAVEDATA->setX(STAGE3, _player->getX());
		SAVEDATA->setGravity(STAGE3, _player->getGravity());
		SAVEDATA->setPreviousStage(STAGE3);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("½ºÅ×ÀÌÁö1-2");
	}

	if (_player->getX() > 1280*2 - 20)
	{

		SAVEDATA->setPreviousStage(STAGE3);
		SAVEDATA->setX(STAGE3, _player->getX());
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("½ºÅ×ÀÌÁö1-4");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}
}

void stage1_2_SceneT::render(void)
{

	IMAGEMANAGER->loopRender("Ç®¸ÊÇÏ´Ã", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.05, 0);
	IMAGEMANAGER->loopRender("Ç®¸ÊµÞ»ê", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.06, 0);
	IMAGEMANAGER->loopRender("Ç®¸Ê¾Õ»êµÞµ¿»ê", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.1, 0);
	IMAGEMANAGER->loopRender("Ç®¸Ê¾Õµ¿»êµÞÀÜµð", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.15, 0);
	IMAGEMANAGER->loopRender("Ç®¸Ê¾ÕÀÜµð", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.2, 0);
	IMAGEMANAGER->loopRender("Ç®¸ÊµÞÃµÀåÇ®", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.25, 0);
	IMAGEMANAGER->loopRender("Ç®¸ÊÁß°£ÃµÀåÇ®", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.3, 0);
	IMAGEMANAGER->loopRender("Ç®¸Ê¾ÕÃµÀåÇ®", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.4, 0);

	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();

}
