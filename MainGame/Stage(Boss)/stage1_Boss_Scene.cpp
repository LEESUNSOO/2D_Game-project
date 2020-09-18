#include "stdafx.h"
#include "stage1_Boss_Scene.h"



HRESULT stage1_Boss_Scene::init(void)
{
	_player = new yerinaT;
	_map = new stage1_BOSS_MAPt;
	_eMG = new RBenemyManager;
	_ui = new UIT;

	_eMG->setPlayerLink(_player);
	_player->setEmgLink(_eMG);
	_ui->setPlayerLink(_player);
	_ui->setEnemyMGLink(_eMG);

	//_player->setStage1Map(_map);
	SAVEDATA->setCurrentStage(STAGEBOSS1);

	_player->init();

	if (SAVEDATA->getPreviousStage() == STAGE4)
	{
		_player->setX(50); // �ӽ�����
		_player->setY(720 - 64 *2 -10); // �ӽ�����
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0 )//|| SAVEDATA->getPreviousStage() == STAGE3)
	{
		_player->setX(50);
		//_player->setY(720 * 4 - 200);
		//_player->setY(720*3 + 465);
		//_player->setY(720 * 4-64*4);
		_player->setY(720 - 64 *2 - 10);

	}

	_player->setCurHp(SAVEDATA->getHp());

	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());


	_map->init();
	_eMG->load(STAGEBOSS1); // �ʷε尡 �ƴ϶� ���ʹ� �����̴�!
	_eMG->init();
	_ui->init();
	_eMG->getRibbon()->getSunFlowerBullet()->setPlayerLink(_player);

	count = 0;
	isStartTalk = false;
	isEndTalk = false;

	//IMAGEMANAGER->addImage("�����ϴ�", "resource/mapBG/�����ϴ�.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("������", "resource/mapBG/������.bmp", 1280, 720);
	IMAGEMANAGER->addImage("������2", "resource/mapBG/������2.bmp", 1280, 720);

	//IMAGEMANAGER->addImage("�׽�Ʈ", "resource/mapBG/�Ѿ�5.bmp", 200,20, true, MAGENTA);
	//IMAGEMANAGER->addImage("�׽�Ʈ2", "resource/mapBG/�Ѿ��̹����׽�Ʈ.bmp", 200, 20, true, MAGENTA);
	//GDIPLUS->addImage("�׽�Ʈ3", "resource/mapBG/�Ѿ�6.png");
	GDIPLUS->addImage("�׽�Ʈ3", "resource/mapBG/�Ѿ�7.png");

	//��ȭ
	IMAGEMANAGER->addImage("��ȭâ", "resource/conversation/��ȭâ.bmp", 1280, 240, true, MAGENTA);

	yerina._image[NORMAL] = IMAGEMANAGER->addImage("���������", "resource/conversation/YERINA���.bmp", 363, 900, true, MAGENTA);
	yerina._image[SAD] = IMAGEMANAGER->addImage("���������", "resource/conversation/YERINA���.bmp", 363, 900, true, MAGENTA);
	yerina._image[HAPPY] = IMAGEMANAGER->addImage("���������", "resource/conversation/YERINA���.bmp", 363, 900, true, MAGENTA);
	yerina._image[ANGRY] = IMAGEMANAGER->addImage("������ȭ��", "resource/conversation/YERINAȭ��.bmp", 363, 900, true, MAGENTA);

	
	ribbon._image[NORMAL] = IMAGEMANAGER->addImage("�������", "resource/conversation/RIBBON���.bmp", 363, 600, true, MAGENTA);
	ribbon._image[SAD] = IMAGEMANAGER->addImage("�������", "resource/conversation/RIBBON���.bmp", 363, 600, true, MAGENTA);
	ribbon._image[HAPPY] = IMAGEMANAGER->addImage("�������", "resource/conversation/RIBBON���.bmp", 363, 600, true, MAGENTA);
	ribbon._image[ANGRY] = IMAGEMANAGER->addImage("����ȭ��", "resource/conversation/RIBBONȭ��.bmp", 363, 600, true, MAGENTA);
	
	yerina.emotion = NORMAL;
	ribbon.emotion = SAD;

	yerina.x = -242;
	yerina.y = 100;

	ribbon.x = 1280;
	ribbon.y = 150;

	// �ؽ�Ʈ �ڷ� �ҷ�����
	textInf = TXTDATA->loadTXT("txtdata/��ȭ/bossSceneConv.txt");
	textInf2 = TXTDATA->loadTXT("txtdata/��ȭ/bossSceneConv2.txt");



	content = 0;

	textLength = 0;

	SOUNDMANAGER->play("��������������", SAVEDATA->getBgmSound());


	return S_OK;
}

void stage1_Boss_Scene::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_eMG);
	SAFE_DELETE(_ui);

}

void stage1_Boss_Scene::update(void)
{
	count++;

	this->battleTalkScene();
	this->TalkerMove();


	_player->update(_map);
	_eMG->update(_map);
	_map->update();
	_ui->update();

	CAMERAMANAGER->bgCameraUpdate("�÷��̾�ī�޶�", _player->getX(), _player->getY(), 1280, 720);


	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

}

void stage1_Boss_Scene::render(void)
{
	IMAGEMANAGER->render("������", getMemDC());

	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();



	if (isStartTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left, yerina.rc.top);
		ribbon._image[ribbon.emotion]->render(getMemDC(), ribbon.rc.left, ribbon.rc.top);
		IMAGEMANAGER->render("��ȭâ", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf);
	}
	else if (isEndTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left, yerina.rc.top);
		ribbon._image[ribbon.emotion]->render(getMemDC(), ribbon.rc.left, ribbon.rc.top);
		IMAGEMANAGER->render("��ȭâ", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf2);
	}

	/*char checkinggauge[128];
	wsprintf(checkinggauge, "%d", gauge);
	TextOut(getMemDC(), 900, 250, checkinggauge, strlen(checkinggauge));
	*/
}



void stage1_Boss_Scene::battleTalkScene()
{
	if (!_player->getIsStartBattle() && !_eMG->getRibbon()->getIsStartBattle())
	{
		RECT _rct;
		if (!IntersectRect(&_rct, &_player->getRc(), &_eMG->getRibbon()->getRect()))
		{
			_player->setState(MOVE);
			_player->setX(_player->getX() + 6);
			_eMG->getRibbon()->setX(_eMG->getRibbon()->getPos().x - 6);
		}
		else
		{
			_player->setIsStartBattle(true);
			_eMG->getRibbon()->setIsStartBattle(true);
			_player->setState(IDLE);
			isStartTalk = true;
		}
	}
}

void stage1_Boss_Scene::TalkerMove()
{
	if (isStartTalk)
	{
		conversation.rc = RectMake(0, 720 - 240, WINSIZEX, 240);
		
		if (yerina.x < 200)
			yerina.x += 50;
		if (ribbon.x > 1280-200-242)
			ribbon.x -= 50;
		yerina.rc = RectMake(yerina.x, yerina.y, 242, 500);
		ribbon.rc = RectMake(ribbon.x, ribbon.y, 242, 500);
	}
	if (isEndTalk)
	{
		conversation.rc = RectMake(0, 720 - 240, WINSIZEX, 240);

		if (yerina.x < 200)
			yerina.x += 50;
		if (ribbon.x > 1280 - 200 - 242)
			ribbon.x -= 50;
		yerina.rc = RectMake(yerina.x, yerina.y, 242, 500);
		ribbon.rc = RectMake(ribbon.x, ribbon.y, 242, 500);
	}

	// �ι�° ��ȭ
	if (_eMG->getRibbon()->getIsDead())
	{
		isEndTalk = true;
		SOUNDMANAGER->stop("���������������");

	}
	
}
void stage1_Boss_Scene::contentOfconversation(vector<string> _temp)
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
			_eMG->getRibbon()->setIsReady(false);
			SOUNDMANAGER->play("���������������", SAVEDATA->getBgmSound());

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
			_eMG->getRibbon()->setIsReady(false);
			SOUNDMANAGER->stop("��������������");
			SOUNDMANAGER->play("���������������", SAVEDATA->getBgmSound());

		}
		else if (isEndTalk)
		{
			isEndTalk = false;
			SAVEDATA->setIsClearStage1(true);
			SAVEDATA->setPreviousStage(STAGEBOSS1);
			_player->setIsStartBattle(false);
			SOUNDMANAGER->stop("��������������");
			SCENEMANAGER->loadScene("��������1-Ŭ����");
			//_eMG->getRibbon()->setIsDead(false);
			//�� ����~!
		}
	}


	// ������ȭ
	if (isStartTalk)
	{
		if (content == 2)
			yerina.emotion = HAPPY;
		else if (content == 3)
			ribbon.emotion = ANGRY;
		else if (content == 4)
			yerina.emotion = SAD;
		else if (content == 6)
			yerina.emotion = HAPPY;
		else if (content == 8)
			yerina.emotion = SAD;
	}
	else if (isEndTalk)
	{
		if (content == 0)
			yerina.emotion = SAD;
		else if (content == 1)
			ribbon.emotion = ANGRY;
		else if (content == 4)
			yerina.emotion = HAPPY;
		else if (content == 5)
			ribbon.emotion = SAD;
		else if (content == 7)
			ribbon.emotion = HAPPY;
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
