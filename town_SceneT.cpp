#include "stdafx.h"
#include "town_SceneT.h"


HRESULT town_SceneT::init(void)
{
	_player = new yerinaT;
	_eMG = new RBenemyManager;
	_map = new town_MAP;
	_ui = new UIT;

	SAVEDATA->setCurrentStage(TOWN);

	// �÷��̾� �ʱ�ȭ
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

	//������ġ����
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());
	_player->getRibbon()->setCurMp(SAVEDATA->getMp());

	_map->init();
	_eMG->load(TOWN); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();

	//��ȣ����
	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("Ÿ���ϴ�", "resource/mapBG/Ÿ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ��޻�", "resource/mapBG/Ÿ��޻�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ��ջ�", "resource/mapBG/Ÿ��ջ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ���", "resource/mapBG/Ÿ���.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ��ޱ��", "resource/mapBG/Ÿ��ޱ��.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ��޻�", "resource/mapBG/Ÿ��޻�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ÿ��ձ��", "resource/mapBG/Ÿ��ձ��.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("��������", "resource/mapBG/��������.bmp", 26, 130, true, MAGENTA);

	// ���� �ʱ�ȭ
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			_river[50 * j + i].x = (50 * j + i) * 25;
			_river[50 * j + i].y = 630;
			_river[50 * j + i].speed = 2.f;
			_river[50 * j + i].angle = PI / 2;
			_river[50 * j + i].gravity = 0.f;
			_river[50 * j + i].image = IMAGEMANAGER->findImage("��������");
			_river[50 * j + i].isUp = false;
			_river[50 * j + i].isActive = false;
		}
	}

	index = 0;
	count = 0;

	SOUNDMANAGER->play("Ÿ������", SAVEDATA->getBgmSound());

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

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280 * 4, 720);

	if (_player->getX() > 1280*4-20)
	{
		SAVEDATA->setPreviousStage(TOWN);
		SAVEDATA->setHp(_player->getCurHp());
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());
		//SCENEMANAGER->loadScene("��������1-1");// �ӽú���
		SCENEMANAGER->loadScene("��������1-����");
		SOUNDMANAGER->stop("Ÿ������");
	}

	if (_player->getX() < 20)
	{
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());
		SAVEDATA->setPreviousStage(TOWN);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("��������2-1");
		SOUNDMANAGER->stop("Ÿ������");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

	this->riverMove();
}

void town_SceneT::render(void)
{

	IMAGEMANAGER->loopRender("Ÿ���ϴ�", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left* 0.1, 0);
	IMAGEMANAGER->loopRender("Ÿ��޻�", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.12, 0);
	IMAGEMANAGER->loopRender("Ÿ��ջ�", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.16, 0);
	IMAGEMANAGER->loopRender("Ÿ���", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.22, 0);
	IMAGEMANAGER->loopRender("Ÿ��ޱ��", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.25, 0);
	IMAGEMANAGER->loopRender("Ÿ��޻�", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.3, 0);
	IMAGEMANAGER->loopRender("Ÿ��ձ��", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left*0.4, 0);

	_map->render();
	_player->render();
	_eMG->render(_map);
	
	for (int i = 0; i < RIVERS; i++)
	{
		IMAGEMANAGER->render("��������", getMemDC(), _river[i].rc.left, _river[i].rc.top);
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
