#include "stdafx.h"
#include "town_SceneT.h"


HRESULT town_SceneT::init(void)
{
	_player = new yerinaT;
	_eMG = new RBenemyManager;
	_map = new town_MAP;
	_ui = new UIT;

	SAVEDATA->setCurrentStage(TOWN);

	// 플레이어 초기화
	_player->init();
	if (SAVEDATA->getPreviousStage() == STAGE1)
	{
		_player->setX(1280*4-30);
		_player->setY(720 - 64 * 4);
	}
	else if (SAVEDATA->getX()[TOWN] <= 0 && SAVEDATA->getY()[TOWN] <= 0 || SAVEDATA->getPreviousStage() == STAGEBOSS1)
	{
		_player->setX(30);
		_player->setY(720-64*4);
	}
	_player->setCurHp(SAVEDATA->getHp());
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());

	//리본위치설정
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());
	_player->getRibbon()->setCurMp(SAVEDATA->getMp());

	_map->init();
	_eMG->load(TOWN); // 맵로드가 아니라 에너미 정보이다!
	_eMG->init();
	_ui->init();

	//상호참조
	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("타운하늘", "resource/mapBG/타운하늘.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운뒷산", "resource/mapBG/타운뒷산.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운앞산", "resource/mapBG/타운앞산.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운동산", "resource/mapBG/타운동산.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운뒷깃발", "resource/mapBG/타운뒷깃발.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운뒷상가", "resource/mapBG/타운뒷상가.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("타운앞깃발", "resource/mapBG/타운앞깃발.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("물결조각", "resource/mapBG/물결조각.bmp", 26, 130, true, MAGENTA);

	// 물결 초기화
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			_river[50 * j + i].x = (50 * j + i) * 25;
			_river[50 * j + i].y = 630;
			_river[50 * j + i].speed = 2.f;
			_river[50 * j + i].angle = PI / 2;
			_river[50 * j + i].gravity = 0.f;
			_river[50 * j + i].image = IMAGEMANAGER->findImage("물결조각");
			_river[50 * j + i].isUp = false;
			_river[50 * j + i].isActive = false;
		}
	}

	index = 0;
	count = 0;

	SOUNDMANAGER->play("타운씬브금", SAVEDATA->getBgmSound());

	return S_OK;
}

void town_SceneT::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);
}

void town_SceneT::update(void)
{
	count++;

	_player->update(_map);
	_map->update();
	_eMG->update(_map);
	_ui->update();

	CAMERAMANAGER->bgCameraUpdate("플레이어카메라", _player->getX(), _player->getY(), 1280 * 4, 720);

	if (_player->getX() > 1280*4-20)
	{
		SAVEDATA->setPreviousStage(TOWN);
		SAVEDATA->setHp(_player->getCurHp());
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());
		//SCENEMANAGER->loadScene("스테이지1-1");// 임시변경
		SCENEMANAGER->loadScene("스테이지1-보스");
		SOUNDMANAGER->stop("타운씬브금");
	}

	if (_player->getX() < 20)
	{
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());
		SAVEDATA->setPreviousStage(TOWN);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("스테이지2-1");
		SOUNDMANAGER->stop("타운씬브금");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

	this->riverMove();
}

void town_SceneT::render(void)
{

	IMAGEMANAGER->loopRender("타운하늘", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left* 0.1, 0);
	IMAGEMANAGER->loopRender("타운뒷산", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.12, 0);
	IMAGEMANAGER->loopRender("타운앞산", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.16, 0);
	IMAGEMANAGER->loopRender("타운동산", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.22, 0);
	IMAGEMANAGER->loopRender("타운뒷깃발", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.25, 0);
	IMAGEMANAGER->loopRender("타운뒷상가", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.3, 0);
	IMAGEMANAGER->loopRender("타운앞깃발", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left*0.4, 0);

	_map->render();
	_player->render();
	_eMG->render(_map);
	
	for (int i = 0; i < RIVERS; i++)
	{
		IMAGEMANAGER->render("물결조각", getMemDC(), _river[i].rc.left, _river[i].rc.top);
	}

	_ui->render();
}

void town_SceneT::riverMove()
{

	for (int i = 0; i < RIVERS; i++)
	{
		//if (count % 2 == 0)
		{
			if (_river[i].isActive) continue;

			_river[i].isActive = true;
			_river[i].isUp = true;
			break;
		}

	}

	for (int i = 0; i < RIVERS; i++)
	{
		if (_river[i].y <= 630 - 10.f)
		{
			if (_river[i].isUp)
			{
				_river[i].isUp = false;
			}
		}
		if (_river[i].y >= 630 + 10.f)
		{
			if (!_river[i].isUp)
			{
				_river[i].isUp = true;
			}
		}

		if (_river[i].isActive)
		{
			if (count % 2 == 0)
			{
				if (_river[i].isUp)
				{
					_river[i].y -= 0.5f;
				}
				else
				{
					_river[i].y += 0.5f;
				}
			}

		}

		_river[i].rc = RectMake(_river[i].x, _river[i].y, 25, 110);
	}
}
