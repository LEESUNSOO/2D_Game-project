#include "stdafx.h"
#include "UIT.h"
#include "yerinaT.h"
#include "RBenemyManager.h"

HRESULT UIT::init()
{
	ZeroMemory(&_playerBar, sizeof(BAR));
	ZeroMemory(&_playerHp, sizeof(BAR));
	ZeroMemory(&_ribbonBar, sizeof(BAR));
	ZeroMemory(&_BossBar, sizeof(BAR));
	ZeroMemory(&_yerinaRibbon, sizeof(BAR));
	ZeroMemory(&_minimap, sizeof(BAR));
	ZeroMemory(&_minimi, sizeof(BAR));
	ZeroMemory(&_playerSmallHp, sizeof(BAR));
	ZeroMemory(&_playerSmallEnergy, sizeof(BAR));
	ZeroMemory(&_ribbonSmallMp, sizeof(BAR));


	//플레이어체력바
	_playerBar.x = -300;
	_playerBar.y = 430;
	_playerBar._image[0] = IMAGEMANAGER->addImage("예리나체력뒷바", "resource/ui/예리나체력뒷바.bmp", 30, 180, true, MAGENTA);
	_playerBar._image[1] = IMAGEMANAGER->addImage("예리나체력앞바", "resource/ui/예리나체력앞바.bmp", 30, 180, true, MAGENTA);
	_playerBar._image[2] = IMAGEMANAGER->addImage("예리나체력바테두리", "resource/ui/예리나체력바테두리.bmp", 30, 180, true, MAGENTA);

	//플레이어체력
	_playerHp.x = 120;
	_playerHp.y = 570;
	_playerHp._image[0] = IMAGEMANAGER->addFrameImage("체력숫자", "resource/ui/체력숫자2.bmp", 250, 250, 10, 10);
	_playerHp._pngImage[0] = GDIPLUS->addFrameImage("체력숫자", "resource/ui/체력숫자4.png", 0, 0, 10, 10);
	_playerHp._Index[0] = 0;
	_playerHp._Index[1] = 1;
	_playerHp._Index[2] = 2;

	//리본체력바
	_ribbonBar.x = 20;
	_ribbonBar.y = 640;
	_ribbonBar._image[0] = IMAGEMANAGER->addImage("리본마나뒷바", "resource/ui/리본마나뒷바.bmp", 230, 30, true, MAGENTA);
	_ribbonBar._image[1] = IMAGEMANAGER->addImage("리본마나앞바", "resource/ui/리본마나앞바.bmp", 230, 30, true, MAGENTA);
	_ribbonBar._image[2] = IMAGEMANAGER->addImage("리본마나바테두리", "resource/ui/리본마나바테두리.bmp", 230, 30, true, MAGENTA);

	//리본/예리나 메인이미지
	_yerinaRibbon.x = 20;
	_yerinaRibbon.y = 670;
	_yerinaRibbon._image[0] = IMAGEMANAGER->addImage("ui주인공들", "resource/ui/ui주인공들.bmp", 186,100, true, MAGENTA);
	_yerinaRibbon._image[1] = IMAGEMANAGER->addImage("ui주인공들", "resource/ui/ui주인공들.bmp", 186,100, true, MAGENTA);
	_yerinaRibbon._image[2] = IMAGEMANAGER->addImage("ui주인공들", "resource/ui/ui주인공들.bmp", 186,100, true, MAGENTA);

	//보스체력바
	_BossBar.x = 1300;
	_BossBar.y = 665;
	_BossBar._image[0] = IMAGEMANAGER->addImage("보스체력뒷바", "resource/ui/보스체력뒷바.bmp", 500, 30, true, MAGENTA);
	_BossBar._image[1] = IMAGEMANAGER->addImage("보스체력앞바", "resource/ui/보스체력앞바.bmp", 500, 30, true, MAGENTA);
	_BossBar._image[2] = IMAGEMANAGER->addImage("보스체력바테두리", "resource/ui/보스체력바테두리.bmp", 500, 30, true, MAGENTA);


	//골드정보
	_goldInf.x = 1140;
	_goldInf.y = 595;
	_goldInf._image[0] = IMAGEMANAGER->addFrameImage("뎀스골드", "resource/ui/뎀스골드.bmp", 150, 168, 10, 8);
	_goldInf._Index[0] = 0;
	_goldInf._Index[1] = 1;
	_goldInf._Index[2] = 2;

	IMAGEMANAGER->addFrameImage("골드표시", "resource/ui/골드표시4.bmp", 15, 168, 1, 8);

	//미니맵
	_minimap.x = 1300;
	_minimap.y = 625;
	_minimap._image[0] = IMAGEMANAGER->addImage("미니맵배경", "resource/ui/맵배경.bmp", 135, 84, true, MAGENTA);
	_minimap._image[1] = IMAGEMANAGER->addImage("스테이지1맵", "resource/ui/스테이지1맵1.bmp", 400, 250, true, MAGENTA);
	_minimap._image[2] = IMAGEMANAGER->addImage("타운맵", "resource/ui/타운맵.bmp", 200, 125, true, MAGENTA);
	_minimap._image[3] = IMAGEMANAGER->addImage("해변맵", "resource/ui/해변맵.bmp", 125, 125, true, MAGENTA);

	//미니미
	_minimi.x = 1140;
	_minimi.y = 650;
	_minimi._image[0] = IMAGEMANAGER->addImage("미니미", "resource/ui/미니미.bmp", 25, 25, true, MAGENTA);
	_minimi._Index[0] = 50;
	_minimi._isActive = false;

	count = 0;
	//스몰 상태바
	_playerSmallHp._image[0] = IMAGEMANAGER->addImage("작은체력", "resource/ui/작은체력.bmp", 70, 9, true, MAGENTA);;
	_playerSmallHp._image[1] = IMAGEMANAGER->addImage("작은체력틀", "resource/ui/작은체력틀.bmp", 90, 14, true, MAGENTA);;

	_playerSmallEnergy._image[0] = IMAGEMANAGER->addImage("작은에너지", "resource/ui/작은에너지.bmp", 70, 9, true, MAGENTA);;
	_playerSmallEnergy._image[1] = IMAGEMANAGER->addImage("작은에너지틀", "resource/ui/작은에너지틀.bmp", 90, 14, true, MAGENTA);;

	_ribbonSmallMp._image[0] = IMAGEMANAGER->addImage("작은마나", "resource/ui/작은마나.bmp", 48, 6, true, MAGENTA);;
	_ribbonSmallMp._image[1] = IMAGEMANAGER->addImage("작은마나틀", "resource/ui/작은마나틀.bmp", 65, 10, true, MAGENTA);;


	return S_OK;
}

void UIT::release()
{
}

void UIT::update()
{
	count++;

	//플레이어관련 ui
	if (_playerBar.x < 40)
		_playerBar.x+=20;

	_playerBar.rc = RectMake(_playerBar.x, _playerBar.y, 30, 180);
	_playerHp.rc = RectMake(_playerBar.x + 70, _playerBar.y + 150, 30, 30);
	_yerinaRibbon.rc = RectMake(_playerBar.x - 30, _playerBar.y + 170, 170, 100);
	_ribbonBar.rc = RectMake(_yerinaRibbon.rc.right - 30, _yerinaRibbon.rc.bottom - 35, 230, 30);

	// 미니맵 ui + 골드
	if (_minimap.x > 1140)
		_minimap.x-=10;

	_minimap.rc = RectMake(_minimap.x, _minimap.y, 120, 76);
	_minimi.rc = RectMake(_minimap.x, _minimap.y + 25, 25, 25);
	_goldInf.rc = RectMake(_minimap.x, _minimap.y - 30, 15, 21);

	// 보스 ui
	if (_BossBar.x > 645)
		_BossBar.x -= 15;
	_BossBar.rc = RectMake(_BossBar.x, _BossBar.y, 400, 30);


	for (int i = 0; i < 3; i++)
	{
		if (count % 10 == 0)
		{
			_playerHp._Index[i]++;
			if (_playerHp._Index[i] > 10)
				_playerHp._Index[i] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count % 10 == 0)
		{
			_goldInf._Index[i]++;
			if (_goldInf._Index[i] > 10)
				_goldInf._Index[i] = 0;
		}
	}


	if (!_minimi._isActive)
	{
		_minimi._Index[0]+=4;
		if (_minimi._Index[0] > 185)
			_minimi._isActive = true;
	}
	else
	{
		_minimi._Index[0]-=2;
		if (_minimi._Index[0] < 25)
			_minimi._isActive = false;
	}


}							 

void UIT::render()
{
	//Rectangle(getMemDC(), _playerBar.rc);
	//Rectangle(getMemDC(), _ribbonBar.rc);
	//Rectangle(getMemDC(), _yerinaRibbon.rc);
	//Rectangle(getMemDC(), _minimap.rc);
	//Rectangle(getMemDC(), _minimi.rc);
	//Rectangle(getMemDC(), _goldInf.rc);


	_playerSmallHp._image[0]->render(getMemDC(), _player->getX() + 15 - 46 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getY() + 3 + 58 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 70 / _player->getMaxHp()  * _player->getCurHp(), 9);
	_playerSmallHp._image[1]->render(getMemDC(), _player->getX() - 46 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getY() + 58 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

	_playerSmallEnergy._image[0]->render(getMemDC(), _player->getX() + 15 - 46 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getY() + 15 + 3 + 58 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 70 / _player->getMaxEnergy()  * _player->getCurEnergy(), 9);
	_playerSmallEnergy._image[1]->render(getMemDC(), _player->getX() - 46 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getY() + 15 + 58 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);




	//에리나체력
	_playerBar._image[0]->render(getMemDC(), _playerBar.rc.left, _playerBar.rc.top);
	_playerBar._image[1]->render(getMemDC(), _playerBar.rc.left, _playerBar.rc.top + (180 / _player->getMaxHp() * (_player->getMaxHp() - _player->getCurHp())), 0, 180 / _player->getMaxHp() * (_player->getMaxHp() - _player->getCurHp()), 30, 180 / _player->getMaxHp() * _player->getCurHp());
	_playerBar._image[2]->render(getMemDC(), _playerBar.rc.left, _playerBar.rc.top);

	if (SAVEDATA->getIsClearStage1())
	{
		//리본마력
		_ribbonBar._image[0]->render(getMemDC(), _ribbonBar.rc.left, _ribbonBar.rc.top);
		_ribbonBar._image[1]->render(getMemDC(), _ribbonBar.rc.left, _ribbonBar.rc.top, 0, 0, 230 / _player->getRibbon()->getMaxMp()  * _player->getRibbon()->getCurMp(), 30);
		_ribbonBar._image[2]->render(getMemDC(), _ribbonBar.rc.left, _ribbonBar.rc.top);

		_ribbonSmallMp._image[0]->render(getMemDC(), _player->getRibbon()->getX() + 15 - 5 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getRibbon()->getY() + 3 - 15 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 48 / _player->getRibbon()->getMaxMp()  * _player->getRibbon()->getCurMp(), 6);
		_ribbonSmallMp._image[1]->render(getMemDC(), _player->getRibbon()->getX() - 5 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _player->getRibbon()->getY() - 15 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);


	}


	_yerinaRibbon._image[0]->render(getMemDC(), _yerinaRibbon.rc.left, _yerinaRibbon.rc.top);

	//스몰바





	if (SAVEDATA->getCurrentStage() == STAGEBOSS1)
	{
		//Rectangle(getMemDC(), _BossBar.rc);

		_BossBar._image[0]->render(getMemDC(), _BossBar.rc.left, _BossBar.rc.top);
		_BossBar._image[1]->render(getMemDC(), _BossBar.rc.left + (_eMG->getRibbon()->getMaxHp() - _eMG->getRibbon()->getCurHp())/1500*500 , _BossBar.rc.top, (_eMG->getRibbon()->getMaxHp() - _eMG->getRibbon()->getCurHp())/1500*500, 0, _eMG->getRibbon()->getCurHp() / 1500 * 500 , 30);
		_BossBar._image[2]->render(getMemDC(), _BossBar.rc.left, _BossBar.rc.top);
	}
	else if (SAVEDATA->getCurrentStage() == FINALBOSS)
	{
		_BossBar._image[0]->render(getMemDC(), _BossBar.rc.left, _BossBar.rc.top);
		_BossBar._image[1]->render(getMemDC(), _BossBar.rc.left + (_eMG->getFinalBoss()->getMaxHp() - _eMG->getFinalBoss()->getCurHp()) / 4000 * 500, _BossBar.rc.top, (_eMG->getFinalBoss()->getMaxHp() - _eMG->getFinalBoss()->getCurHp()) / 4000 * 500, 0, _eMG->getFinalBoss()->getCurHp() / 4000 * 500, 30);
		_BossBar._image[2]->render(getMemDC(), _BossBar.rc.left, _BossBar.rc.top);

	}

	
	this->playerHp();
	this->minimiSite();
	this->goldInformation();


	/*_playerHp._pngImage[0]->gdiFrameRender(getMemDC(), _playerHp.rc.left, _playerHp.rc.top, _player->getCurHp() / 100, _playerHp._hpIndex[0]);
	_playerHp._pngImage[0]->gdiFrameRender(getMemDC(), _playerHp.rc.left + 20, _playerHp.rc.top, _player->getCurHp() % 100 / 10, _playerHp._hpIndex[1]);
	_playerHp._pngImage[0]->gdiFrameRender(getMemDC(), _playerHp.rc.left + 40, _playerHp.rc.top, _player->getCurHp() % 10, _playerHp._hpIndex[2]);*/

}

void UIT::playerHp()
{
	if ((int)_player->getCurHp() >= 100)
		_playerHp._image[0]->frameRender(getMemDC(), _playerHp.rc.left, _playerHp.rc.top, (int)_player->getCurHp() / 100, _playerHp._Index[0]);
	if ((int)_player->getCurHp() >= 10)
		_playerHp._image[0]->frameRender(getMemDC(), _playerHp.rc.left + 20, _playerHp.rc.top, (int)_player->getCurHp() % 100 / 10, _playerHp._Index[1]);
	if ((int)_player->getCurHp() >= 1)
		_playerHp._image[0]->frameRender(getMemDC(), _playerHp.rc.left + 40, _playerHp.rc.top, (int)_player->getCurHp() % 10, _playerHp._Index[2]);

}

void UIT::minimiSite()
{
	//미니맵배경
	_minimap._image[0]->render(getMemDC(), _minimap.rc.left - 5, _minimap.rc.top - 5);
	switch (SAVEDATA->getCurrentStage())
	{
	case STAGE1:
		_minimap._image[1]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25, ((int)(_player->getY() / 720)) * 25 + 25 * 4, 125, 75);
		break;

	case STAGE2:
		_minimap._image[1]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25 + 25 * 4, ((int)(_player->getY() / 720)) * 25 + 25 * 4, 125, 75);
		break;

	case STAGE3:
		_minimap._image[1]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25 + 25 * 6, ((int)(_player->getY() / 720)) * 25 + 25 * 5, 125, 75);
		break;

	case STAGE4:
		_minimap._image[1]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25 + 25 * 8, ((int)(_player->getY() / 720)) * 25 + 25 * 2, 125, 75);
		break;

	case STAGEBOSS1:
		_minimap._image[1]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25 + 25 * 10, ((int)(_player->getY() / 720)) * 25 + 25 * 2, 125, 75);
		break;

	case TOWN:
		_minimap._image[2]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25, ((int)(_player->getY() / 720)) * 25 + 25 , 125, 75);
		break;

	case STAGE6:
		_minimap._image[3]->render(getMemDC(), _minimap.rc.left, _minimap.rc.top, ((int)(_player->getX() / 1280)) * 25, ((int)(_player->getY() / 720)) * 25 + 25, 125, 75);
		break;


	default:
		break;
	}

	//플레이어위치
	_minimi._image[0]->alphaRender(getMemDC(), _minimi.rc.left, _minimi.rc.top, _minimi._Index[0]);
}

void UIT::goldInformation()
{

	IMAGEMANAGER->frameRender("골드표시", getMemDC(), _goldInf.rc.left + 5 , _goldInf.rc.top, 0, _goldInf._Index[0]);

	if ((int)_player->getGold() >= 10000)
		_goldInf._image[0]->frameRender(getMemDC(), _goldInf.rc.left + 16*2, _goldInf.rc.top, (int)_player->getGold() / 10000, _goldInf._Index[0]);
	if ((int)_player->getGold() >= 1000)
		_goldInf._image[0]->frameRender(getMemDC(), _goldInf.rc.left + 16*3, _goldInf.rc.top, (int)_player->getGold() % 10000 / 1000, _goldInf._Index[1]);
	if ((int)_player->getGold() >= 100)												  
		_goldInf._image[0]->frameRender(getMemDC(), _goldInf.rc.left + 16*4, _goldInf.rc.top, (int)_player->getGold() % 1000 / 100, _goldInf._Index[2]);
	if ((int)_player->getGold() >= 10)												   
		_goldInf._image[0]->frameRender(getMemDC(), _goldInf.rc.left + 16*5, _goldInf.rc.top, (int)_player->getGold() % 100 / 10, _goldInf._Index[0]);
	if ((int)_player->getGold() >= 1)												   
		_goldInf._image[0]->frameRender(getMemDC(), _goldInf.rc.left + 16*6, _goldInf.rc.top, (int)_player->getGold() % 10, _goldInf._Index[1]);



}
