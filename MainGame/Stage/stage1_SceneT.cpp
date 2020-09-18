#include "stdafx.h"
#include "stage1_SceneT.h"



HRESULT stage1_SceneT::init(void)
{
	
	_player = new yerinaT;
	_map = new stage1_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;
	
	SAVEDATA->setCurrentStage(STAGE1);

	_player->init();

	if (SAVEDATA->getPreviousStage() == STAGE2)
	{
		_player->setX(1280 * 4 - 70);
		_player->setY(450);
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0 || SAVEDATA->getPreviousStage() == TOWN)
	{
		_player->setX(30);
		_player->setY(514);
	}
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setCurHp(SAVEDATA->getHp());

	//����
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());
	_player->getRibbon()->setCurMp(SAVEDATA->getMp());

	_map->init();
	_eMG->load(STAGE1); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʾ��ܵ�", "resource/mapBG/Ǯ�ʾ��ܵ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʵ�õ��Ǯ", "resource/mapBG/Ǯ�ʵ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ���߰�õ��Ǯ", "resource/mapBG/Ǯ���߰�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("Ǯ�ʾ�õ��Ǯ", "resource/mapBG/Ǯ�ʾ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);


	SOUNDMANAGER->play("��������1�����", SAVEDATA->getBgmSound());

	return S_OK;
}

void stage1_SceneT::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);
}

void stage1_SceneT::update(void)
{
	_player->update(_map);
	_map->update();
	_eMG->update(_map);
	_ui->update();

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280 * 4 - 64, 720);

	if (_player->getX() >= 1280 * 4 - 65)
	{
		SAVEDATA->setPreviousStage(STAGE1);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("��������1-2");
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());

	}

	if (_player->getX() < 20)
	{
		SAVEDATA->setPreviousStage(STAGE1);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("Ÿ��");
		SOUNDMANAGER->stop("��������1�����");
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());

	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}
}

void stage1_SceneT::render(void)
{

	IMAGEMANAGER->loopRender("Ǯ���ϴ�", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.05, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʵ޻�", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.06, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʾջ�޵���", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.1, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʾյ�����ܵ�", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.15, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʾ��ܵ�", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.2, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʵ�õ��Ǯ", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.25, 0);
	IMAGEMANAGER->loopRender("Ǯ���߰�õ��Ǯ", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.3, 0);
	IMAGEMANAGER->loopRender("Ǯ�ʾ�õ��Ǯ", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.4, 0);



	_map->render();	
	_eMG->render(_map);
	_player->render();
	_ui->render();
}
