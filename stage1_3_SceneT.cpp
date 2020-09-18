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
		_player->setX(50); // �ӽ�����
		_player->setY(720 * 4 - 200); // �ӽ�����
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0 || SAVEDATA->getPreviousStage() == STAGE3)
	{
		_player->setX(50);
		_player->setY(720 * 4-64*4);
	}
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setCurHp(SAVEDATA->getHp());

	//������ġ����
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());

	_map->init();
	_eMG->load(STAGE4); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	IMAGEMANAGER->addImage("�����ϴ�", "resource/mapBG/�����ϴ�.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�����ϴ�2", "resource/mapBG/�����ϴ�2.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʵ޻�", "resource/mapBG/���ʵ޻�.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʵβ����", "resource/mapBG/���ʵβ����.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�����߰�����", "resource/mapBG/�����߰�����.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʾֱ⳪��", "resource/mapBG/���ʾֱ⳪��.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����", "resource/mapBG/�׽�Ʈ����.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����2", "resource/mapBG/�׽�Ʈ����2.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����3", "resource/mapBG/�׽�Ʈ����3.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����4", "resource/mapBG/�׽�Ʈ����4.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����5", "resource/mapBG/�׽�Ʈ����5.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�׽�Ʈ����6", "resource/mapBG/�׽�Ʈ����5.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʵ�Ǯ", "resource/mapBG/���ʵ�Ǯ.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʾ�Ǯ", "resource/mapBG/���ʾ�Ǯ.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("�����ܵ�", "resource/mapBG/�����ܵ�.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʹ��", "resource/mapBG/���ʹ��.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʹ��2", "resource/mapBG/���ʹ��2.bmp", 1280, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʺ�", "resource/mapBG/���ʺ�.bmp",2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("���ʺ�2", "resource/mapBG/���ʺ�2.bmp", 2560, 1440, true, MAGENTA);

	GDIPLUS->addFrameImage("��", "resource/effect/��.png", 0, 0, 10, 1);
	EFFECTMANAGER->addEffect_png("������Ʈ", "��", 0.4, 2);

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

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280 * 2 , 2880);

	if (_player->getX() < 20)
	{
		SAVEDATA->setPreviousStage(STAGE4);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("��������1-3");
	}

	if (_player->getX() > 1280*2 - 20)
	{
		SAVEDATA->setPreviousStage(STAGE4);
		SAVEDATA->setHp(_player->getCurHp());
		SCENEMANAGER->loadScene("��������1-����");
		SOUNDMANAGER->stop("��������1�����");
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

	IMAGEMANAGER->loopRender("�����ϴ�2", getMemDC(), &RectMake(0,0,WINSIZEX,WINSIZEY), bgLoopCount, 0);// *0.05, 0);
	IMAGEMANAGER->render("���ʵ޻�", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.1, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("�׽�Ʈ����6", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left *0.17, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("�׽�Ʈ����", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left *0.2, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("�׽�Ʈ����4", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left *0.25, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("�׽�Ʈ����2", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left *0.34, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("�����ܵ�", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.5, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("���ʵ�Ǯ", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.3, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("���ʾ�Ǯ", getMemDC(), 0, 0, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left * 0.27, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top / 3, WINSIZEX, WINSIZEY);

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
			EFFECTMANAGER->play_png("������Ʈ", _player->getX() - CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.left, _player->getY() - CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top);
			if (count % 10 == 0)
				SOUNDMANAGER->play("ü��ȸ��", SAVEDATA->getEffSound());
		}
	}
}
