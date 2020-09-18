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
		_player->setX(1280 - 50); // 임시지정
		_player->setY(720 - 185); // 임시지정
	}
	else if (SAVEDATA->getX()[STAGE1] <= 0 && SAVEDATA->getY()[STAGE1] <= 0)
	{
		_player->setX(1280 - 50);
		_player->setY(720 - 185);

	}

	_player->setCurHp(SAVEDATA->getHp());
	_player->setIsClearStage1(SAVEDATA->getIsClearStage1());
	_player->setDir(LEFT);
	//리본
	_player->getRibbon()->setX(_player->getX());
	_player->getRibbon()->setY(_player->getY());


	_map->init();
	_eMG->load(FINALBOSS); // 맵로드가 아니라 에너미 정보이다!
	_eMG->init();
	_ui->init();

	////_eMG->getRibbon()->getSunFlowerBullet()->setPlayerLink(_player);

	_eMG->getFinalBoss()->getFinalGuidedBullet()->setPlayerLink(_player);
	_eMG->getFinalBoss()->getFinalPolygonBullet()->setPlayerLink(_player);
	_eMG->getFinalBoss()->getFinalOctopusBullet()->setPlayerLink(_player);

	////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스맵으로 

	_bgImage[0] = IMAGEMANAGER->addImage("최종보스배경4", "resource/mapBG/최종보스배경4.bmp", 1280, 720);
	_bgImage[1] = IMAGEMANAGER->addImage("최종보스배경4", "resource/mapBG/최종보스배경4.bmp", 1280, 720);
	_bgImage[2] = IMAGEMANAGER->addImage("최종보스배경2", "resource/mapBG/최종보스배경2.bmp", 1280, 720);
	_bgImage[3] = IMAGEMANAGER->addImage("최종보스배경2", "resource/mapBG/최종보스배경2.bmp", 1280, 720);
	_bgImage[4] = IMAGEMANAGER->addImage("최종보스배경4", "resource/mapBG/최종보스배경4.bmp", 1280, 720);
	_bgImage[5] = IMAGEMANAGER->addImage("최종보스배경3", "resource/mapBG/최종보스배경3.bmp", 1280, 720);
	_bgImage[6] = IMAGEMANAGER->addImage("최종보스배경2", "resource/mapBG/최종보스배경2.bmp", 1280, 720);
	_bgImage[7] = IMAGEMANAGER->addImage("최종보스배경4", "resource/mapBG/최종보스배경4.bmp", 1280, 720);

	//대화
	IMAGEMANAGER->addImage("대화창", "resource/conversation/대화창.bmp", 1280, 240, true, MAGENTA);

	yerina._image[NORMAL] = IMAGEMANAGER->addImage("예리나평소2", "resource/conversation/예리나평소2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[SAD] = IMAGEMANAGER->addImage("예리나슬픔2", "resource/conversation/예리나슬픔2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[HAPPY] = IMAGEMANAGER->addImage("예리나기쁨2", "resource/conversation/예리나기쁨2.bmp", 880, 1240, true, MAGENTA);
	yerina._image[ANGRY] = IMAGEMANAGER->addImage("예리나화남2", "resource/conversation/예리나화남2.bmp", 880, 1240, true, MAGENTA);

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 보스로 

	irisu._image[NORMAL] = IMAGEMANAGER->addImage("최종보스평소", "resource/conversation/최종보스평소.bmp", 880, 1240, true, MAGENTA);
	irisu._image[SAD] = IMAGEMANAGER->addImage("최종보스슬픔", "resource/conversation/최종보스슬픔.bmp", 880, 1240, true, MAGENTA);
	irisu._image[HAPPY] = IMAGEMANAGER->addImage("최종보스기쁨", "resource/conversation/최종보스기쁨.bmp", 880, 1240, true, MAGENTA);
	irisu._image[ANGRY] = IMAGEMANAGER->addImage("최종보스화남", "resource/conversation/최종보스화남.bmp", 880, 1240, true, MAGENTA);

	yerina.emotion = SAD;
	irisu.emotion = SAD;

	yerina.x = 1280;
	yerina.y = 150;

	irisu.x = -242;
	irisu.y = 100;

	// 텍스트 자료 불러오기 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스맵으로 

	textInf = TXTDATA->loadTXT("txtdata/대화/bossSceneConv3.txt");
	textInf2 = TXTDATA->loadTXT("txtdata/대화/bossSceneConv4.txt");

	content = 0;
	textLength = 0;
	count = 0;
	isStartTalk = false;
	isEndTalk = false;

	SOUNDMANAGER->play("최종보스입장브금", SAVEDATA->getBgmSound());


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

	CAMERAMANAGER->bgCameraUpdate("플레이어카메라", _player->getX(), _player->getY(), 1280, 720);

	//if (_player->getX() < 20)
	//{

	//	SAVEDATA->setPreviousStage(STAGE4);

	//	SCENEMANAGER->loadScene("스테이지1-3");

	//}

	//if (_player->getX() > 1280 * 2 - 20)
	//{
	//	SAVEDATA->setPreviousStage(STAGE4);

	//	SCENEMANAGER->loadScene("스테이지1-보스");
	//}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		this->init();
	}

}

void stage_FinalBoss_Scene::render(void)
{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스맵으로 

	_bgImage[_eMG->getFinalBoss()->getCurPhase()]->render(getMemDC());

	//if(_eMG->getRibbon()->getFinalSkill()[6])
		//IMAGEMANAGER->alphaRender("보스맵2", getMemDC(), 255);



	_map->render();
	_player->render();
	_eMG->render(_map);
	_ui->render();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스맵으로 



	if (isStartTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left - 300, yerina.rc.top - 300);
		irisu._image[irisu.emotion]->render(getMemDC(), irisu.rc.left - 400, irisu.rc.top - 270);
		IMAGEMANAGER->render("대화창", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf);
	}
	else if (isEndTalk)
	{
		yerina._image[yerina.emotion]->render(getMemDC(), yerina.rc.left - 300, yerina.rc.top - 300);
		irisu._image[irisu.emotion]->render(getMemDC(), irisu.rc.left -400, irisu.rc.top -270);
		IMAGEMANAGER->render("대화창", getMemDC(), conversation.rc.left, conversation.rc.top);
		this->contentOfconversation(textInf2);
	}

	///*char checkinggauge[128];
	//wsprintf(checkinggauge, "%d", gauge);
	//TextOut(getMemDC(), 900, 250, checkinggauge, strlen(checkinggauge));
	//*/
}



void stage_FinalBoss_Scene::battleTalkScene()
{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스로 

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

	// 두번째 대화
	if (_eMG->getFinalBoss()->getIsDead())
	{
		isEndTalk = true;
		SOUNDMANAGER->stop("최종보스전투브금");
	}


}
void stage_FinalBoss_Scene::contentOfconversation(vector<string> _temp)
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
			_eMG->getFinalBoss()->setIsReady(false);
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
			_eMG->getFinalBoss()->setIsReady(false);
			SOUNDMANAGER->stop("최종보스입장브금");
			SOUNDMANAGER->play("최종보스전투브금", SAVEDATA->getBgmSound());

		}
		else if (isEndTalk)
		{
			isEndTalk = false;
			//SAVEDATA->setIsClearStage1(true);
			SAVEDATA->setPreviousStage(FINALBOSS);
			_player->setIsStartBattle(false);
			SOUNDMANAGER->stop("최종보스입장브금");
			SCENEMANAGER->loadScene("파이널클리어");
			//_eMG->getRibbon()->setIsDead(false);
			//씬 변경~!
		}
	}

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 파이널보스로 

	// 감정변화
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
