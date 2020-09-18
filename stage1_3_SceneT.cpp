#include "stdafx.h"
#include "stage1_3_SceneT.h"



HRESULT stage1_3_SceneT::init(void)
{
	_player = new yerinaT;
	_map = new stage1_3_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;

	SAVEDATA->setCurrentStage(STAGE4);

	_player->init();

	if (SAVEDATA->getPreviousStage() == STAGEBOSS1)
	{
		_player->setX(50); // ÀÓ½ÃÁöÁ¤
		_player->setY(720 * 4 - 200); // ÀÓ½ÃÁöÁ¤
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0 || SAVEDATA->getPreviousStage() == STAGE3)
	{
		_player->setX(50);
		_player->setY(720 * 4-64*4);
	}
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setCurHp(SAVEDATA->getHp());

	//¸®º»À§Ä¡¼³Á¤
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());

	_map->init();
	_eMG->load(STAGE4); // ¸Ê·Îµå°¡ ¾Æ´Ï¶ó ¿¡³Ê¹Ì Á¤º¸ÀÌ´Ù!
	_eMG->init();
	_ui->init();

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("½£¸ÊÇÏ´Ã", "resource/mapBG/½£¸ÊÇÏ´Ã.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊÇÏ´Ã2", "resource/mapBG/½£¸ÊÇÏ´Ã2.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊµÞ»ê", "resource/mapBG/½£¸ÊµÞ»ê.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊµÎ²¨¿î³ª¹«", "resource/mapBG/½£¸ÊµÎ²¨¿î³ª¹«.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊÁß°£³ª¹«", "resource/mapBG/½£¸ÊÁß°£³ª¹«.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Ê¾Ö±â³ª¹«", "resource/mapBG/½£¸Ê¾Ö±â³ª¹«.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«", "resource/mapBG/Å×½ºÆ®³ª¹«.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«2", "resource/mapBG/Å×½ºÆ®³ª¹«2.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«3", "resource/mapBG/Å×½ºÆ®³ª¹«3.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«4", "resource/mapBG/Å×½ºÆ®³ª¹«4.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«5", "resource/mapBG/Å×½ºÆ®³ª¹«5.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("Å×½ºÆ®³ª¹«6", "resource/mapBG/Å×½ºÆ®³ª¹«5.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊµÞÇ®", "resource/mapBG/½£¸ÊµÞÇ®.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Ê¾ÕÇ®", "resource/mapBG/½£¸Ê¾ÕÇ®.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸ÊÀÜµð", "resource/mapBG/½£¸ÊÀÜµð.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Ê¹è°æ", "resource/mapBG/½£¸Ê¹è°æ.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Ê¹è°æ2", "resource/mapBG/½£¸Ê¹è°æ2.bmp", 1280, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Êºû", "resource/mapBG/½£¸Êºû.bmp",2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("½£¸Êºû2", "resource/mapBG/½£¸Êºû2.bmp", 2560, 1440, true, MAGENTA);

	GDIPLUS->addFrameImage("Èú", "resource/effect/Èú.png", 0, 0, 10, 1);
	EFFECTMANAGER->addEffect_png("ÈúÀÌÆåÆ®", "Èú", 0.4, 2);

	alpha = count = 0;
	isAlpha = false;
	bgLoopCount = 0;
	return S_OK;
}

void stage1_3_SceneT::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);
}

void stage1_3_SceneT::update(void)
{
	_player->update(_map);
	_map->update();
	_eMG->update(_map);
	_ui->update();

	this->savePoint();

	CAMERAMANAGER->bgCameraUpdate("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó", _player->getX(), _player->getY(), 1280 * 2 , 2880);

	if (_player->getX() < 20)
	{
		SAVEDATA->setPreviousStage(STAGE4);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("½ºÅ×ÀÌÁö1-3");
	}

	if (_player->getX() > 1280*2 - 20)
	{
		SAVEDATA->setPreviousStage(STAGE4);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("½ºÅ×ÀÌÁö1-º¸½º");
		SOUNDMANAGER->stop("½ºÅ×ÀÌÁö1¾Àºê±Ý");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

	if (!isAlpha)
	{
		alpha--;
		if (alpha < 1)
		{
			isAlpha = true;
		}
	}
	else
	{
		alpha++;
		if (alpha > 250)
		{
			isAlpha = false;
		}
	}

	bgLoopCount -= 0.4;
}

void stage1_3_SceneT::render(void)
{

	IMAGEMANAGER->loopRender("½£¸ÊÇÏ´Ã2", getMemDC(), &RectMake(0,0,WINSIZEX,WINSIZEY), bgLoopCount, 0);// *0.05, 0);
	IMAGEMANAGER->render("½£¸ÊµÞ»ê", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.1, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("Å×½ºÆ®³ª¹«6", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left *0.17, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("Å×½ºÆ®³ª¹«", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left *0.2, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("Å×½ºÆ®³ª¹«4", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left *0.25, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("Å×½ºÆ®³ª¹«2", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left *0.34, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("½£¸ÊÀÜµð", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.5, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("½£¸ÊµÞÇ®", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.3, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("½£¸Ê¾ÕÇ®", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left * 0.27, CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top / 3, WINSIZEX, WINSIZEY);

	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();

	//char checkinggauge[128];
	//wsprintf(checkinggauge, "%d", _player->getHammer());
	//TextOut(getMemDC(), 900, 250, checkinggauge, strlen(checkinggauge));
}

void stage1_3_SceneT::savePoint()
{
	RECT _rct;
	if (IntersectRect(&_rct, &_player->getRc(), &_map->getSavePoint()))
	{
		if (_player->getCurHp() < _player->getMaxHp())
		{
			_player->setCurHp(_player->getCurHp() + 1);
			EFFECTMANAGER->play_png("ÈúÀÌÆåÆ®", _player->getX() - CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.left, _player->getY() - CAMERAMANAGER->getVCam("ÇÃ·¹ÀÌ¾îÄ«¸Þ¶ó")[0].rc.top);
			if (count % 10 == 0)
				SOUNDMANAGER->play("Ã¼·ÂÈ¸º¹", SAVEDATA->getEffSound());
		}
	}
}
