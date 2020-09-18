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
		_player->setX(50); // 임시지정
		_player->setY(720 - 64 *2 -10); // 임시지정
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
	_eMG->load(STAGEBOSS1); // 맵로드가 아니라 에너미 정보이다!
	_eMG->init();
	_ui->init();
	_eMG->getRibbon()->getSunFlowerBullet()->setPlayerLink(_player);

	count = 0;
	isStartTalk = false;
	isEndTalk = false;

	//IMAGEMANAGER->addImage("숲맵하늘", "resource/mapBG/숲맵하늘.bmp", 2560, 1440, true, MAGENTA);
	IMAGEMANAGER->addImage("보스맵", "resource/mapBG/보스맵.bmp", 1280, 720);
	IMAGEMANAGER->addImage("보스맵2", "resource/mapBG/보스맵2.bmp", 1280, 720);

	//IMAGEMANAGER->addImage("테스트", "resource/mapBG/총알5.bmp", 200,20, true, MAGENTA);
	//IMAGEMANAGER->addImage("테스트2", "resource/mapBG/총알이미지테스트.bmp", 200, 20, true, MAGENTA);
	//GDIPLUS->addImage("테스트3", "resource/mapBG/총알6.png");
	GDIPLUS->addImage("테스트3", "resource/mapBG/총알7.png");

	//대화
	IMAGEMANAGER->addImage("대화창", "resource/conversation/대화창.bmp", 1280, 240, true, MAGENTA);

	yerina._image[NORMAL] = IMAGEMANAGER->addImage("에리나평소", "resource/conversation/YERINA평소.bmp", 363, 900, true, MAGENTA);
	yerina._image[SAD] = IMAGEMANAGER->addImage("에리나우울", "resource/conversation/YERINA우울.bmp", 363, 900, true, MAGENTA);
	yerina._image[HAPPY] = IMAGEMANAGER->addImage("에리나기쁨", "resource/conversation/YERINA기쁨.bmp", 363, 900, true, MAGENTA);
	yerina._image[ANGRY] = IMAGEMANAGER->addImage("에리나화남", "resource/conversation/YERINA화남.bmp", 363, 900, true, MAGENTA);

	
	ribbon._image[NORMAL] = IMAGEMANAGER->addImage("리본평소", "resource/conversation/RIBBON평소.bmp", 363, 600, true, MAGENTA);
	ribbon._image[SAD] = IMAGEMANAGER->addImage("리본우울", "resource/conversation/RIBBON우울.bmp", 363, 600, true, MAGENTA);
	ribbon._image[HAPPY] = IMAGEMANAGER->addImage("리본기쁨", "resource/conversation/RIBBON기쁨.bmp", 363, 600, true, MAGENTA);
	ribbon._image[ANGRY] = IMAGEMANAGER->addImage("리본화남", "resource/conversation/RIBBON화남.bmp", 363, 600, true, MAGENTA);
	
	yerina.emotion = NORMAL;
	ribbon.emotion = SAD;

	yerina.x = -242;
	yerina.y = 100;

	ribbon.x = 1280;
	ribbon.y = 150;

	// 텍스트 자료 불러오기
	textInf = TXTDATA->loadTXT("txtdata/대화/bossSceneConv.txt");
	textInf2 = TXTDATA->loadTXT("txtdata/대화/bossSceneConv2.txt");



	content = 0;

	textLength = 0;

	SOUNDMANAGER->play("리본보스입장브금", SAVEDATA->getBgmSound());


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

	CAMERAMANAGER->bgCameraUpdate("플레이어카메라", _player->getX(), _player->getY(), 1280, 720);


	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

}

void stage1_Boss_Scene::render(void)
{
	IMAGEMANAGER->render("보스맵", getMemDC());

	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();



	if (isStartTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left, yerina.rc.top);
		ribbon._image[ribbon.emotion]->render(getMemDC(), ribbon.rc.left, ribbon.rc.top);
		IMAGEMANAGER->render("대화창", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf);
	}
	else if (isEndTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left, yerina.rc.top);
		ribbon._image[ribbon.emotion]->render(getMemDC(), ribbon.rc.left, ribbon.rc.top);
		IMAGEMANAGER->render("대화창", getMemDC(), conversation.rc.left, conversation.rc.top);
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

	// 두번째 대화
	if (_eMG->getRibbon()->getIsDead())
	{
		isEndTalk = true;
		SOUNDMANAGER->stop("리본보스전투브금");

	}
	
}
void stage1_Boss_Scene::contentOfconversation(vector<string> _temp)
{
	maxContent = _temp.size() - 1;

	// 글자 출력 속도
	if (textLength < _temp[content].size() && count % 3 == 0)
		textLength++;

	
	// 대화 한 마디 출력
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (textLength < _temp[content].size())
			textLength = _temp[content].size();
		else if (textLength == _temp[content].size() && content == maxContent)
		{
			isStartTalk = false;
			_eMG->getRibbon()->setIsReady(false);
			SOUNDMANAGER->play("리본보스전투브금", SAVEDATA->getBgmSound());

			content = 0;
		}
		else if (textLength == _temp[content].size())
		{
			textLength = 0;
			content++;
		}
		SOUNDMANAGER->play("대화넘기기", SAVEDATA->getEffSound());

	}

	// 대화 스킵
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (isStartTalk)
		{
			isStartTalk = false;
			content = 0;
			_eMG->getRibbon()->setIsReady(false);
			SOUNDMANAGER->stop("리본보스입장브금");
			SOUNDMANAGER->play("리본보스전투브금", SAVEDATA->getBgmSound());

		}
		else if (isEndTalk)
		{
			isEndTalk = false;
			SAVEDATA->setIsClearStage1(true);
			SAVEDATA->setPreviousStage(STAGEBOSS1);
			_player->setIsStartBattle(false);
			SOUNDMANAGER->stop("리본보스입장브금");
			SCENEMANAGER->loadScene("스테이지1-클리어");
			//_eMG->getRibbon()->setIsDead(false);
			//씬 변경~!
		}
	}


	// 감정변화
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


	if (isStartTalk || isEndTalk) // 대화 종료시 터지는것을 막기 위해
	{
		// 글자 뒷배경
		HFONT myFont2 = CreateFont(20, 10, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "타이포_뽀로로 M");
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


		// 앞쪽 글자
		HFONT myFont = CreateFont(20, 10, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "타이포_뽀로로 M");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		//사람별 글씨 색 변화
		if (content % 2 == 1) // 리본
			SetTextColor(getMemDC(), RGB(255, 180, 180));
		else // 예리나
			SetTextColor(getMemDC(), RGB(180, 180, 255));

		TextOut(getMemDC(), 300, 550, _temp[content].c_str(), textLength);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}
	
}
