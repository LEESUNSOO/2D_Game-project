#include "stdafx.h"
#include "stage_FinalBoss_Scene.h"



HRESULT stage_FinalBoss_Scene::init(void)
{
	_player = new yerinaT;
	_map = new stage_FinalBoss_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	//_player->setStage1Map(_map);
	SAVEDATA->setCurrentStage(FINALBOSS);

	_player->init();

	if (SAVEDATA->getPreviousStage() == STAGE6)
	{
		_player->setX(1280 - 50); // �ӽ�����
		_player->setY(720 - 185); // �ӽ�����
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0)
	{
		_player->setX(1280 - 50);
		_player->setY(720 - 185);

	}

	_player->setCurHp(SAVEDATA->getHp());
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setDir(LEFT);
	//����
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());


	_map->init();
	_eMG->load(FINALBOSS); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();

	////_eMG->getRibbon()->getSunFlowerBullet()->setPlayerLink(_player);

	_eMG->getFinalBoss()->getFinalGuidedBullet()->setPlayerLink(_player);
	_eMG->getFinalBoss()->getFinalPolygonBullet()->setPlayerLink(_player);
	_eMG->getFinalBoss()->getFinalOctopusBullet()->setPlayerLink(_player);

	////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ��������� 

	_bgImage[0] = IMAGEMANAGER->addImage("�����������4", "resource/mapBG/�����������4.bmp", 1280, 720);
	_bgImage[1] = IMAGEMANAGER->addImage("�����������4", "resource/mapBG/�����������4.bmp", 1280, 720);
	_bgImage[2] = IMAGEMANAGER->addImage("�����������2", "resource/mapBG/�����������2.bmp", 1280, 720);
	_bgImage[3] = IMAGEMANAGER->addImage("�����������2", "resource/mapBG/�����������2.bmp", 1280, 720);
	_bgImage[4] = IMAGEMANAGER->addImage("�����������4", "resource/mapBG/�����������4.bmp", 1280, 720);
	_bgImage[5] = IMAGEMANAGER->addImage("�����������3", "resource/mapBG/�����������3.bmp", 1280, 720);
	_bgImage[6] = IMAGEMANAGER->addImage("�����������2", "resource/mapBG/�����������2.bmp", 1280, 720);
	_bgImage[7] = IMAGEMANAGER->addImage("�����������4", "resource/mapBG/�����������4.bmp", 1280, 720);

	//��ȭ
	IMAGEMANAGER->addImage("��ȭâ", "resource/conversation/��ȭâ.bmp", 1280, 240, true, MAGENTA);

	yerina._image[NORMAL] = IMAGEMANAGER->addImage("���������2", "resource/conversation/���������2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[SAD] = IMAGEMANAGER->addImage("����������2", "resource/conversation/����������2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[HAPPY] = IMAGEMANAGER->addImage("���������2", "resource/conversation/���������2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[ANGRY] = IMAGEMANAGER->addImage("������ȭ��2", "resource/conversation/������ȭ��2.bmp", 880, 1240, true, MAGENTA);

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ������ 

	irisu._image[NORMAL] = IMAGEMANAGER->addImage("�����������", "resource/conversation/�����������.bmp", 880, 1240, true, MAGENTA);
	irisu._image[SAD] = IMAGEMANAGER->addImage("������������", "resource/conversation/������������.bmp", 880, 1240, true, MAGENTA);
	irisu._image[HAPPY] = IMAGEMANAGER->addImage("�����������", "resource/conversation/�����������.bmp", 880, 1240, true, MAGENTA);
	irisu._image[ANGRY] = IMAGEMANAGER->addImage("��������ȭ��", "resource/conversation/��������ȭ��.bmp", 880, 1240, true, MAGENTA);

	yerina.emotion = SAD;
	irisu.emotion = SAD;

	yerina.x = 1280;
	yerina.y = 150;

	irisu.x = -242;
	irisu.y = 100;

	// �ؽ�Ʈ �ڷ� �ҷ����� 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ��������� 

	textInf = TXTDATA->loadTXT("txtdata/��ȭ/bossSceneConv3.txt");
	textInf2 = TXTDATA->loadTXT("txtdata/��ȭ/bossSceneConv4.txt");

	content = 0;
	textLength = 0;
	count = 0;
	isStartTalk = false;
	isEndTalk = false;

	SOUNDMANAGER->play("��������������", SAVEDATA->getBgmSound());


	return S_OK;
}

void stage_FinalBoss_Scene::release(void)
{
	SAFE_DELETE(_player);
	//SAFE_DELETE(_map);
	//SAFE_DELETE(_eMG);
	//SAFE_DELETE(_ui);

}

void stage_FinalBoss_Scene::update(void)
{
	count++;

	this->battleTalkScene();
	this->TalkerMove();


	_player->update(_map);
	_eMG->update(_map);
	_map->update();
	_ui->update();

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280, 720);

	//if (_player->getX() < 20)
	//{

	//	SAVEDATA->setPreviousStage(STAGE4);

	//	SCENEMANAGER->loadScene("��������1-3");

	//}

	//if (_player->getX() > 1280 * 2 - 20)
	//{
	//	SAVEDATA->setPreviousStage(STAGE4);

	//	SCENEMANAGER->loadScene("��������1-����");
	//}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

}

void stage_FinalBoss_Scene::render(void)
{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ��������� 

	_bgImage[_eMG->getFinalBoss()->getCurPhase()]->render(getMemDC());

	//if(_eMG->getRibbon()->getFinalSkill()[6])
		//IMAGEMANAGER->alphaRender("������2", getMemDC(), 255);



	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ��������� 



	if (isStartTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left - 300, yerina.rc.top - 300);
		irisu._image[irisu.emotion]->render(getMemDC(), irisu.rc.left - 400, irisu.rc.top - 270);
		IMAGEMANAGER->render("��ȭâ", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf);
	}
	else if (isEndTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left - 300, yerina.rc.top - 300);
		irisu._image[irisu.emotion]->render(getMemDC(), irisu.rc.left -400, irisu.rc.top -270);
		IMAGEMANAGER->render("��ȭâ", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf2);
	}

	///*char checkinggauge[128];
	//wsprintf(checkinggauge, "%d", gauge);
	//TextOut(getMemDC(), 900, 250, checkinggauge, strlen(checkinggauge));
	//*/
}



void stage_FinalBoss_Scene::battleTalkScene()
{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ����� 

	if (!_player->getIsStartBattle() && !_eMG->getFinalBoss()->getIsStartBattle())
	{
		RECT _rct;
		if (!IntersectRect(&_rct, &_player->getRc(), &_eMG->getFinalBoss()->getRect()))
		{
			_player->setState(MOVE);
			_eMG->getFinalBoss()->setState(IDLE);
			_player->setX(_player->getX() - 3);
			//_eMG->getFinalBoss()->setX(_eMG->getFinalBoss()->getPos().x + 2);

		}
		else
		{
			_player->setIsStartBattle(true);
			_eMG->getFinalBoss()->setIsStartBattle(true);
			_player->setState(IDLE);
			_eMG->getFinalBoss()->setState(IDLE);

			isStartTalk = true;
		}
	}



}

void stage_FinalBoss_Scene::TalkerMove()
{

	if (isStartTalk)
	{
		conversation.rc = RectMake(0, 720 - 240, WINSIZEX, 240);

		if (irisu.x < 200)
			irisu.x += 50;
		if (yerina.x > 1280 - 200 - 242)
			yerina.x -= 50;
		yerina.rc = RectMake(yerina.x, yerina.y, 242, 500);
		irisu.rc = RectMake(irisu.x, irisu.y, 242, 500);

	}
	if (isEndTalk)
	{
		conversation.rc = RectMake(0, 720 - 240, WINSIZEX, 240);

		if (irisu.x < 200)
			irisu.x += 50;
		if (yerina.x > 1280 - 200 - 242)
			yerina.x -= 50;
		yerina.rc = RectMake(yerina.x, yerina.y, 242, 500);
		irisu.rc = RectMake(irisu.x, irisu.y, 242, 500);
	}

	// �ι�° ��ȭ
	if (_eMG->getFinalBoss()->getIsDead())
	{
		isEndTalk = true;
		SOUNDMANAGER->stop("���������������");
	}


}
void stage_FinalBoss_Scene::contentOfconversation(vector<string> _temp)
{
	maxContent = _temp.size() - 1;

	// ���� ��� �ӵ�
	if (textLength < _temp[content].size() && count % 3 == 0)
		textLength++;

	// ��ȭ �� ���� ���
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (textLength < _temp[content].size())
			textLength = _temp[content].size();
		else if (textLength == _temp[content].size() && content == maxContent)
		{
			isStartTalk = false;
			_eMG->getFinalBoss()->setIsReady(false);
			content = 0;
		}
		else if (textLength == _temp[content].size())
		{
			textLength = 0;
			content++;
		}
		SOUNDMANAGER->play("��ȭ�ѱ��", SAVEDATA->getEffSound());

	}

	// ��ȭ ��ŵ
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (isStartTalk)
		{
			isStartTalk = false;
			content = 0;
			_eMG->getFinalBoss()->setIsReady(false);
			SOUNDMANAGER->stop("��������������");
			SOUNDMANAGER->play("���������������", SAVEDATA->getBgmSound());

		}
		else if (isEndTalk)
		{
			isEndTalk = false;
			//SAVEDATA->setIsClearStage1(true);
			SAVEDATA->setPreviousStage(FINALBOSS);
			_player->setIsStartBattle(false);
			SOUNDMANAGER->stop("��������������");
			SCENEMANAGER->loadScene("���̳�Ŭ����");
			//_eMG->getRibbon()->setIsDead(false);
			//�� ����~!
		}
	}

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���̳κ����� 

	// ������ȭ
	if (isStartTalk)
	{
		if (content == 5)
			irisu.emotion = ANGRY;
		else if (content == 6)
			yerina.emotion = ANGRY;
	}
	else if (isEndTalk)
	{
		if (content == 0)
			yerina.emotion = SAD;
		else if (content == 1)
			irisu.emotion = ANGRY;
		else if (content == 4)
			yerina.emotion = HAPPY;
		else if (content == 5)
			irisu.emotion = SAD;
		else if (content == 7)
			irisu.emotion = HAPPY;
	}


	if (isStartTalk || isEndTalk) // ��ȭ ����� �����°��� ���� ����
	{
		// ���� �޹��
		HFONT myFont2 = CreateFont(20, 10, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Ÿ����_�Ƿη� M");
		HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), myFont2);
		SetTextColor(getMemDC(), RGB(0, 0, 0));

		for (int i = 0; i < 3; i += 2)
		{
			for (int j = 0; j < 3; j += 2)
			{
				TextOut(getMemDC(), 300 - 1 + i, 550 - 1 + j, _temp[content].c_str(), textLength);
			}
		}

		SelectObject(getMemDC(), oldFont2);
		DeleteObject(myFont2);


		// ���� ����
		HFONT myFont = CreateFont(20, 10, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Ÿ����_�Ƿη� M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		//����� �۾� �� ��ȭ
		if (content % 2 == 1) // ����
			SetTextColor(getMemDC(), RGB(255, 180, 180));
		else // ������
			SetTextColor(getMemDC(), RGB(180, 180, 255));

		TextOut(getMemDC(), 300, 550, _temp[content].c_str(), textLength);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}

}
