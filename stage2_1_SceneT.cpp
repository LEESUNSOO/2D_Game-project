#include "stdafx.h"
#include "stage2_1_SceneT.h"



HRESULT stage2_1_SceneT::init(void)
{

	_player = new yerinaT;
	_map = new stage2_1_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;

	SAVEDATA->setCurrentStage(STAGE6);

	_player->init();

	if (SAVEDATA->getPreviousStage() == TOWN)
	{
		_player->setX(1280- 70);
		_player->setY(720-135);
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0 )//|| SAVEDATA->getPreviousStage() == TOWN)
	{
		_player->setX(1280 - 70);
		_player->setY(720 - 135);
	}
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setCurHp(SAVEDATA->getHp());

	//����
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());
	_player->getRibbon()->setCurMp(SAVEDATA->getMp());

	_map->init();
	_eMG->load(STAGE6); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("�غ��ʹ��", "resource/mapBG/�غ��ʹ��.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("�غ��ʹٴ�", "resource/mapBG/�غ��ʹٴ�.bmp", 1280, 720, true, MAGENTA);
	IMAGEMANAGER->addImage("�غ��ʹ���", "resource/mapBG/�غ��ʹ���.bmp", 1280, 720, true, MAGENTA);

	GDIPLUS->addFrameImage("��", "resource/effect/��.png", 0, 0, 10, 1);
	EFFECTMANAGER->addEffect_png("������Ʈ", "��", 0.4, 2);

	count = 0;


	SOUNDMANAGER->play("��������2�����", SAVEDATA->getBgmSound());


	return S_OK;
}

void stage2_1_SceneT::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);
}

void stage2_1_SceneT::update(void)
{
	count++;

	_player->update(_map);
	_map->update();
	_eMG->update(_map);
	_ui->update();

	this->savePoint();

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280 , 720);

	if (_player->getX() >= 1280 - 65)
	{
		SAVEDATA->setPreviousStage(STAGE6);
		SAVEDATA->setHp(_player->getCurHp());
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());

		SCENEMANAGER->loadScene("Ÿ��");
		SOUNDMANAGER->stop("��������2�����");

	}

	if (_player->getX() < 20)
	{
		SAVEDATA->setPreviousStage(STAGE6);
		SAVEDATA->setHp(_player->getCurHp());
		SAVEDATA->setMp(_player->getRibbon()->getCurMp());

		SCENEMANAGER->loadScene("�����������̳κ���");
		SOUNDMANAGER->stop("��������2�����");

	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}
}

void stage2_1_SceneT::render(void)
{

	IMAGEMANAGER->render("�غ��ʹ��", getMemDC());
	IMAGEMANAGER->loopRender("�غ��ʹٴ�", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), count * 0.5, 0);

	_map->render();
	_eMG->render(_map);
	_player->render();
	_ui->render();

	IMAGEMANAGER->loopAlphaRender("�غ��ʹ���", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), -count * 0.5, 0,100);
	
}

void stage2_1_SceneT::savePoint()
{
	RECT _rct;
	if (IntersectRect(&_rct, &_player->getRc(), &_map->getSavePoint()))
	{
		if (_player->getCurHp() < _player->getMaxHp())
		{
			_player->setCurHp(_player->getCurHp() + 1);
			EFFECTMANAGER->play_png("������Ʈ", _player->getX() - CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left, _player->getY() - CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top);
			if ((int)count % 10 == 0)
				SOUNDMANAGER->play("ü��ȸ��", SAVEDATA->getEffSound());
		}
	}
}
