#include "stdafx.h"
#include "RBenemyManager.h"
#include "yerinaT.h"



HRESULT RBenemyManager::init(void)
{


	_factory = new enemyFactory;

	_beAttactedNum = 7;
	_damsIndex[0] = 0;
	_damsIndex[1] = 1;
	_damsIndex[2] = 2;

	IMAGEMANAGER->addFrameImage("뎀스", "resource/ui/뎀스골드.bmp", 150, 168, 10, 8);

	//this->load(); // 각 씬에서 로드해줌

	for (int i = 0; i < _vEnemyInf.size(); i += 3)
	{
		RBenemy* enemy = _factory->createEnemy((enum ENEMY_TYPE)atoi(_vEnemyInf[i].c_str()));
		_testPos[i].x = atoi(_vEnemyInf[i + 1].c_str());
		_testPos[i].y = atoi(_vEnemyInf[i + 2].c_str());
		enemy->setPosition(_testPos[i].x, _testPos[i].y);
		_vEnemy.push_back(enemy);
	}

	switch (SAVEDATA->getCurrentStage())
	{
	case STAGEBOSS1:
		_ribbonBoss = new ribbonBoss;
		_ribbonBoss->init();

		_ribbonBoss->setPlayerLink(_player);
		break;
	case FINALBOSS:
		_finalBoss = new finalBoss;
		_finalBoss->init();
		_finalBoss->setPlayerLink(_player);
		break;
	default:
		break;
	}


	//임시이펙트
	GDIPLUS->addFrameImage("타격1", "resource/effect/타격1.png", 0, 0, 9, 1);
	EFFECTMANAGER->addEffect_png("타격이펙트1", "타격1", 0.5f, 10);

	GDIPLUS->addFrameImage("타격2", "resource/effect/타격2.png", 0, 0, 9, 1);
	EFFECTMANAGER->addEffect_png("타격이펙트2", "타격2", 0.6f, 10);

	GDIPLUS->addFrameImage("타격3", "resource/effect/타격4.png", 0, 0, 5, 1);
	EFFECTMANAGER->addEffect_png("타격이펙트3", "타격3", 0.3f, 10);

	GDIPLUS->addFrameImage("타격5", "resource/effect/타격6.png", 0, 0, 10, 1);
	EFFECTMANAGER->addEffect_png("타격이펙트5", "타격5", 0.8f, 10);

	GDIPLUS->addFrameImage("돈획득", "resource/effect/돈획득.png", 0, 0, 6, 1);
	EFFECTMANAGER->addEffect_png("돈획득이펙트1", "돈획득", 0.3f, 10);

	GDIPLUS->addFrameImage("죽임1", "resource/effect/죽임1.png", 0, 0, 6, 1);
	EFFECTMANAGER->addEffect_png("죽임이펙트1", "죽임1", 0.25f, 10);

	GDIPLUS->addFrameImage("클리어", "resource/effect/클리어.png", 0, 0, 15, 1);
	EFFECTMANAGER->addEffect_png("클리어이펙트1", "클리어", 0.25f, 10);


	return S_OK;
}


void RBenemyManager::release(void)
{
	SAFE_DELETE(_factory);
}

void RBenemyManager::update(stage_MAPt* _maps)
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->update(_maps);
	}

	for (int i = 0; i < 3; i++)
	{
		_damsIndex[i]++;
		if (_damsIndex[i] > 10)
			_damsIndex[i] = 0;
	}

	this->enemyDirectionDecision();
	this->playerAttactCollision();

	switch (SAVEDATA->getCurrentStage())
	{
	case STAGEBOSS1:
		_ribbonBoss->update();
		break;
	case FINALBOSS:
		_finalBoss->update();
		break;

	default:
		break;
	}
}

void RBenemyManager::render(stage_MAPt* _maps)
{

	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getIsActive())
			_vEnemy[i]->getImage(_vEnemy[i]->getState())->frameRender(getMemDC(), _vEnemy[i]->getRealSizeRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getRealSizeRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getIndexX(), _vEnemy[i]->getindexY());
	
		if (_vEnemy[i]->getIsAttacted())
		{
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 100)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _vEnemy[i]->getDamsRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 1000 / 100, _damsIndex[0]);// _goldInf._Index[2]);
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 10)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _vEnemy[i]->getDamsRc().left + 16 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 100 / 10, _damsIndex[1]);
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 1)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _vEnemy[i]->getDamsRc().left + 16 * 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 10, _damsIndex[2]);	
		}
			
	}


	char checking[128];
	wsprintf(checking, "%d", _beAttactedNum);
	TextOut(getMemDC(), 600, 100, checking, strlen(checking));


	if (KEYMANAGER->isToggleKey('O'))
	{
		//for (int i = 0; i < _vEnemy.size(); ++i)
		//{
		//	for (int j = 0; j < 11; j++)
		//	{
		//		Rectangle(getMemDC(), _maps->getTiles()[_vEnemy[i]->getCollisionTile()[j]].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _maps->getTiles()[_vEnemy[i]->getCollisionTile()[j]].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _maps->getTiles()[_vEnemy[i]->getCollisionTile()[j]].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _maps->getTiles()[_vEnemy[i]->getCollisionTile()[j]].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
		//	}
		//}

		//for (int i = 0; i < _vEnemy.size(); ++i)
		//{
		//	Rectangle(getMemDC(), _vEnemy[i]->getBottomRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getBottomRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getBottomRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getBottomRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		//}

		//for (int i = 0; i < _vEnemy.size(); ++i)
		//{
		//	Rectangle(getMemDC(), _vEnemy[i]->getPixelRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getPixelRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getPixelRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getPixelRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		//}

		for (int i = 0; i < _vEnemy.size(); ++i)
		{
			Rectangle(getMemDC(), _vEnemy[i]->getRealSizeRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getRealSizeRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getRealSizeRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getRealSizeRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}

		for (int i = 0; i < _vEnemy.size(); ++i)
		{
			Rectangle(getMemDC(), _vEnemy[i]->getDamsRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getDamsRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getDamsRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
		//for (int i = 0; i < _vEnemy.size(); ++i)
		//{
		//	Rectangle(getMemDC(), _vEnemy[i]->getTileRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getTileRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getTileRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getTileRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		//}

		//for (int i = 0; i < _vEnemy.size(); ++i)
		//{
		//	Rectangle(getMemDC(), _vEnemy[i]->getTopRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getTopRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vEnemy[i]->getTopRc().right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[i]->getTopRc().bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		//}
	}

	switch (SAVEDATA->getCurrentStage())
	{
	case STAGEBOSS1:
		//Rectangle(getMemDC(), _ribbonBoss->getRect());
		//_ribbonBoss->getImage(_ribbonBoss->getState())->frameRender(getMemDC(), _ribbonBoss->getRect().left, _ribbonBoss->getRect().top, _ribbonBoss->getIndex(), _ribbonBoss->getDir());
		_ribbonBoss->getImage(_ribbonBoss->getState())->frameRender(getMemDC(), _ribbonBoss->getRect().left, _ribbonBoss->getRect().top, _ribbonBoss->getIndex(), _ribbonBoss->getDir());

		if (_ribbonBoss->getIsDead())
			break;
		// 따라가는 작은 블루 뷸렛
		for (int i = 0; i < _ribbonBoss->getRibbonBlueBullet()->getSmallBullet().size(); i++)
		{
			//Rectangle(getMemDC(), _blueBullet->getSmallBullet()[i].rc);
			_ribbonBoss->setBulletIndex(RND->getInt(3));

			_ribbonBoss->getRibbonBlueBullet()->getSmallBullet()[i]._bulletImg[_ribbonBoss->getBulletIndex()]->gdiRender(getMemDC(), _ribbonBoss->getRibbonBlueBullet()->getSmallBullet()[i].rc.left, _ribbonBoss->getRibbonBlueBullet()->getSmallBullet()[i].rc.top);

		}
		// 충돌을 일으키는 큰 블루 뷸렛
		for (int i = 0; i < _ribbonBoss->getRibbonBlueBullet()->getBigBullet().size(); i++)
		{
			_ribbonBoss->getRibbonBlueBullet()->getBigBullet()[i]._bulletImg[0]->gdiFrameRender(getMemDC(), _ribbonBoss->getRibbonBlueBullet()->getBigBullet()[i].rc.left, _ribbonBoss->getRibbonBlueBullet()->getBigBullet()[i].rc.top, _ribbonBoss->getRibbonBlueBullet()->getBigBullet()[i]._bulletImg[0]->getFrameX(), _ribbonBoss->getRibbonBlueBullet()->getBigBullet()[i]._bulletImg[0]->getFrameY());
		}
		//Rectangle(getMemDC(), _blueBullet->getBigBullet().rc);

		//블루레인
		for (int i = 0; i < _ribbonBoss->getRibbonBlueRain()->getBlueRain().size(); i++)
		{
			_ribbonBoss->getRibbonBlueRain()->getBlueRain()[i]._bulletImg[1]->gdiRender(getMemDC(), _ribbonBoss->getRibbonBlueRain()->getBlueRain()[i].rc.left, _ribbonBoss->getRibbonBlueRain()->getBlueRain()[i].rc.top);
		}
		for (int i = 0; i < _ribbonBoss->getRibbonBlueRain()->getBlueRain().size(); i++)
		{
			_ribbonBoss->getRibbonBlueRain()->getBlueRain()[i]._image->render(getMemDC(), _ribbonBoss->getRibbonBlueRain()->getBlueRain()[i].rc.left, _ribbonBoss->getRibbonBlueRain()->getBlueRain()[i].rc.top);
		}

		for (int i = 0; i < _ribbonBoss->getRibbonBlueRain()->getBlueRain().size(); i++)
		{
			//Rectangle(getMemDC(), _ribbonBoss->getRibbonBlueRain()->getBlueRain()[i].rc);
		}

		// 태양불꽃망토

		for (int i = 0; i < _ribbonBoss->getSunFlowerBullet()->getSun().size(); ++i)
		{
			for (int j = 0; j < _ribbonBoss->getSunFlowerBullet()->getSun()[i].size(); ++j)
			{
				if (_ribbonBoss->getSunFlowerBullet()->getSun()[i][j].isfire)
				{
					//Rectangle(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc);
					//_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);
					_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

					_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._image->render(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

				}
			}
		}

		//꽃잎
		for (int i = 0; i < _ribbonBoss->getSunFlowerBullet()->getFlower().size(); ++i)
		{
			for (int j = 0; j < _ribbonBoss->getSunFlowerBullet()->getFlower()[i].size(); ++j)
			{
				if (_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].isfire || _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].isActive_first)
				{
					//Rectangle(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc);
					_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.top);
					//_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

					//_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j]._image->render(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);
				}

			}
		}
		for (int i = 0; i < _ribbonBoss->getSunFlowerBullet()->getFlower().size(); ++i)
		{
			for (int j = 0; j < _ribbonBoss->getSunFlowerBullet()->getFlower()[i].size(); ++j)
			{
				if (_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].isfire || _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].isActive_first)
				{
					//Rectangle(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc);
					//_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.top);
					//_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

					_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j]._image->render(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

				}
			}
		}

		for (int i = 0; i < _ribbonBoss->getSpiderWebBullet()->getSpiderWeb().size(); ++i)
		{
			//for (int j = 0; j < _ribbonBoss->getSpiderWebBullet()->getSpider()[i].size(); ++j)
			{
				if (_ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].isfire || _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].isActive_first || _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].isActive_second)
				{
					//Rectangle(getMemDC(), _ribbonBoss->getSpiderWebBullet()->getSpider()[i][j].rc);
					//_ribbonBoss->getSunFlowerBullet()->getFlower()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getFlower()[i][j].rc.top);
					//_ribbonBoss->getSunFlowerBullet()->getSun()[i][j]._bulletImg[0]->gdiRender(getMemDC(), _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.left, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].rc.top);//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);
					//_ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._image->frameRender(getMemDC(), _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].rc.left, _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].rc.top, _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._image->getFrameX(), _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._image->getFrameY());//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);
					_ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._bulletImg[0]->gdiFrameRender(getMemDC(), _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].rc.left, _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i].rc.top, _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._bulletImg[0]->getFrameX(), _ribbonBoss->getSpiderWebBullet()->getSpiderWeb()[i]._bulletImg[0]->getFrameY());//, _ribbonBoss->getSunFlowerBullet()->getSun()[i][j].indexX, 0);

				}
			}

		}



		if (_ribbonBoss->getIsCharging()[0])
		{
			_ribbonBoss->getChargingIMG(0)->gdiFrameRender(getMemDC(), _ribbonBoss->getRect().left - 17, _ribbonBoss->getRect().top - 17, _ribbonBoss->getChargeIndex(), 0);
		}
		else if (_ribbonBoss->getIsCharging()[1])
		{
			_ribbonBoss->getChargingIMG(1)->gdiFrameRender(getMemDC(), _ribbonBoss->getRect().left - 17, _ribbonBoss->getRect().top - 17, _ribbonBoss->getChargeIndex(), 0);
		}
		else if (_ribbonBoss->getIsCharging()[2])
		{
			_ribbonBoss->getChargingIMG(2)->gdiFrameRender(getMemDC(), _ribbonBoss->getRect().left - 17, _ribbonBoss->getRect().top - 17, _ribbonBoss->getChargeIndex(), 0);
		}
		else if (_ribbonBoss->getIsCharging()[3])
		{
			_ribbonBoss->getChargingIMG(3)->gdiFrameRender(getMemDC(), _ribbonBoss->getRect().left - 17, _ribbonBoss->getRect().top - 17, _ribbonBoss->getChargeIndex(), 0);
		}

		//뎀스
		if (_ribbonBoss->getIsAttacted())
		{
			//if ((int)_player->getStrikingPower()[_beAttactedNum] >= 100)
				//IMAGEMANAGER->frameRender("뎀스", getMemDC(), _ribbonBoss->getDamsRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbonBoss->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 10000 / 1000, _damsIndex[2]);
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 100)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _ribbonBoss->getDamsRc().left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbonBoss->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 1000 / 100, _damsIndex[0]);
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 10)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _ribbonBoss->getDamsRc().left + 16 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbonBoss->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 100 / 10, _damsIndex[1]);
			if ((int)_player->getStrikingPower()[_beAttactedNum] >= 1)
				IMAGEMANAGER->frameRender("뎀스", getMemDC(), _ribbonBoss->getDamsRc().left + 16 * 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbonBoss->getDamsRc().top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, (int)_player->getStrikingPower()[_beAttactedNum] % 10, _damsIndex[2]);
		}

		break;

	case FINALBOSS:
		//채울것
		_finalBoss->getImage(_finalBoss->getState())->frameRender(getMemDC(), _finalBoss->getRect().left, _finalBoss->getRect().top, _finalBoss->getIndex(), _finalBoss->getDir());

		if (_finalBoss->getIsDead())
			break;
		for (int j = 0; j < _finalBoss->getFinalGuidedBullet()->getGuidedBullet().size(); ++j)
		{
			int randNum = RND->getInt(3);
			if (_finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j].isfire || _finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j].isActive_first)
			{
				_finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j]._bulletImg[randNum]->gdiRender(getMemDC(), _finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j].rc.left, _finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j].rc.top);
			}
		}

		for (int j = 0; j < _finalBoss->getFinalTornadoBullet()->getTornadoBullet().size(); ++j)
		{
			
			if (_finalBoss->getFinalTornadoBullet()->getTornadoBullet()[j].isfire )//|| _finalBoss->getFinalGuidedBullet()->getGuidedBullet()[j].isActive_first)
			{
				_finalBoss->getFinalTornadoBullet()->getTornadoBullet()[j]._bulletImg[(j / 20) % 3]->gdiRender(getMemDC(), _finalBoss->getFinalTornadoBullet()->getTornadoBullet()[j].rc.left, _finalBoss->getFinalTornadoBullet()->getTornadoBullet()[j].rc.top);
			}
		}


		for (int j = 0; j < _finalBoss->getFinalSnakeBullet()->getSnakebullet().size(); ++j)
		{

			if (_finalBoss->getFinalSnakeBullet()->getSnakebullet()[j].isfire || _finalBoss->getFinalSnakeBullet()->getSnakebullet()[j].isActive_first)
			{
				//Rectangle(getMemDC(), _finalBoss->getFinalSnakeBullet()->getSnakebullet()[j].rc);
				_finalBoss->getFinalSnakeBullet()->getSnakebullet()[j]._bulletImg[0]->gdiRender(getMemDC(), _finalBoss->getFinalSnakeBullet()->getSnakebullet()[j].rc.left, _finalBoss->getFinalSnakeBullet()->getSnakebullet()[j].rc.top);
			}
		}

		for (int j = 0; j < _finalBoss->getFinalPolygonBullet()->getPolygonBullet().size(); ++j)
		{

			if (_finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].isfire)//|| _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].isActive_first)
			{
				//Rectangle(getMemDC(), _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc);
				_finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j]._bulletImg[0]->gdiRender(getMemDC(), _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.left, _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.top);
			}
			if (_finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].isActive_first)
			{
				//Rectangle(getMemDC(), _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc);
				_finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j]._bulletImg[1]->gdiRender(getMemDC(), _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.left, _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.top);
				if (j > 63)
					_finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j]._bulletImg[2]->gdiRender(getMemDC(), _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.left, _finalBoss->getFinalPolygonBullet()->getPolygonBullet()[j].rc.top);
			}
		}

		for (int j = 0; j < _finalBoss->getFinalOctopusBullet()->getOctopusBullet().size(); ++j)
		{

			if (_finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].isfire || _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].isActive_first)
			{
				if (j < 48)
				{
					
					_finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j]._bulletImg[RND->getInt(3)]->gdiRender(getMemDC(), _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].rc.left, _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].rc.top);

				}
				else
					_finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j]._bulletImg[3]->gdiRender(getMemDC(), _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].rc.left, _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].rc.top);

				//Rectangle(getMemDC(), _finalBoss->getFinalOctopusBullet()->getOctopusBullet()[j].rc);
			}
		}


		for (int j = 0; j < _finalBoss->getFinalBallBullet()->getBallBullet().size(); ++j)
		{

			if (_finalBoss->getFinalBallBullet()->getBallBullet()[j].isfire || _finalBoss->getFinalBallBullet()->getBallBullet()[j].isActive_first)
			{
				//Rectangle(getMemDC(), _finalBoss->getFinalBallBullet()->getBallBullet()[j].rc);
				_finalBoss->getFinalBallBullet()->getBallBullet()[j]._bulletImg[0]->gdiRender(getMemDC(), _finalBoss->getFinalBallBullet()->getBallBullet()[j].rc.left, _finalBoss->getFinalBallBullet()->getBallBullet()[j].rc.top);
			}
		}


		break;

	default:
		break;
	}


	//char checkGRibbonHP[128];
	//sprintf(checkGRibbonHP, "%f", _ribbonBoss->getCurHP());
	//TextOut(getMemDC(), 900, 300, checkGRibbonHP, strlen(checkGRibbonHP));
}

void RBenemyManager::enemyDirectionDecision()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		//방향결정

		if (_vEnemy[i]->getPos().x > _player->getX() + 250)
		{
			_vEnemy[i]->setDirection(E_LEFT);
		}
		else if (_vEnemy[i]->getPos().x < _player->getX() - 250)
			_vEnemy[i]->setDirection(E_RIGHT);

		//각도결정
		float angle = getAngle(_vEnemy[i]->getPos().x, _vEnemy[i]->getPos().y, _player->getX(), _player->getY());

		if (_vEnemy[i]->getState() == E_JUMP)
			_vEnemy[i]->setAngle(angle);

		float distance = getDistance(_vEnemy[i]->getPos().x, _vEnemy[i]->getPos().y, _player->getX(), _player->getY());

		//추적결정
		if (distance < 800)
			_vEnemy[i]->setIsTrace(true);
		else
			_vEnemy[i]->setIsTrace(false);
	}

}

void RBenemyManager::playerAttactCollision()
{
	for (int i = 0; i < HAMMER_END; i++)
	{
		//일반몹
		for (int j = 0; j < _vEnemy.size(); j++)
		{
			RECT _rct;
			if (IntersectRect(&_rct, &_player->getAttactRc()[i], &_vEnemy[j]->getRealSizeRc()) && !_vEnemy[j]->getIsAttacted() && !_vEnemy[j]->getIsDead())
			{
				_vEnemy[j]->setState(E_BEATTACTED);
				_vEnemy[j]->setIsAttacted(true);
				_vEnemy[j]->setDontMove(true);
				_vEnemy[j]->setDamsX(_vEnemy[j]->getPos().x - 25);
				_vEnemy[j]->setDamsY(_vEnemy[j]->getPos().y - 60);
				_vEnemy[j]->setHp(_vEnemy[j]->getHp() - _player->getStrikingPower()[i]);
				SOUNDMANAGER->play("해머타격", SAVEDATA->getEffSound());
				switch (i)
				{
				case HAMMER1:
					EFFECTMANAGER->play_png("타격이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
					break;
				case HAMMER2:
					EFFECTMANAGER->play_png("타격이펙트2", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
					break;

				case HAMMER3:
					EFFECTMANAGER->play_png("타격이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
					break;

				case HAMMER4:
					EFFECTMANAGER->play_png("타격이펙트2", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
					break;

				case HAMMER5:
					EFFECTMANAGER->play_png("타격이펙트3", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
					break;
				case HAMMERUP:
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 30, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 30);
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 40);
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + 30, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 30);

					break;
				case HAMMERDOWN:
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 30, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 30);
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 40);
					EFFECTMANAGER->play_png("타격이펙트5", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + 30, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 30);

					break;
				default:
					break;
				}


				if (_vEnemy[j]->getHp() < 0)
				{
					_vEnemy[j]->setIsDead(true);
					_vEnemy[j]->setState(E_DEAD);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI/180*120) * (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 120) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left) * 1.2);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * 240) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 240) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.2);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * 360) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 360) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.2);
					EFFECTMANAGER->play_png("돈획득이펙트1", 1200,600);
					SOUNDMANAGER->play("골드", SAVEDATA->getEffSound());
					_player->setGold(_player->getGold() + 1000);
				}

				_beAttactedNum = i;
				if (_vEnemy[j]->getDirection() == LEFT)
				{
					_vEnemy[j]->setX(_vEnemy[j]->getPos().x + cosf(PI / 180 * 45) * 30);
				}
				else
				{
					_vEnemy[j]->setX(_vEnemy[j]->getPos().x + cosf(PI / 180 * 135) * 30);
				}
			}
		}

		//리본보스
		if (SAVEDATA->getCurrentStage() == STAGEBOSS1)
		{
			RECT _rct;

			if (IntersectRect(&_rct, &_player->getAttactRc()[i], &_ribbonBoss->getRect()) && !_ribbonBoss->getIsAttacted())
			{
				_ribbonBoss->setState(BEATTACTED);
				_ribbonBoss->setIsAttacted(true);
				_ribbonBoss->setDontMove(true);
				_ribbonBoss->setDamsX(_ribbonBoss->getPos().x - 25);
				_ribbonBoss->setDamsY(_ribbonBoss->getPos().y - 60);
				_ribbonBoss->setCurHp(_ribbonBoss->getCurHp() - _player->getStrikingPower()[i]);
				SOUNDMANAGER->play("해머타격", SAVEDATA->getEffSound());

				if (_ribbonBoss->getCurHp() < 0)
				{
					EFFECTMANAGER->play_png("클리어이펙트1", _ribbonBoss->getPos().x, _ribbonBoss->getPos().y -100);
					EFFECTMANAGER->play_png("클리어이펙트1", _ribbonBoss->getPos().x-100, _ribbonBoss->getPos().y + 200);
					EFFECTMANAGER->play_png("클리어이펙트1", _ribbonBoss->getPos().x+200, _ribbonBoss->getPos().y);

					SOUNDMANAGER->play("리본클리어", SAVEDATA->getEffSound());
					SOUNDMANAGER->play("리본보스입장브금", SAVEDATA->getBgmSound());
					_ribbonBoss->setIsDead(true);
					_ribbonBoss->setState(DEAD);
					if (_ribbonBoss->getDir() == LEFT)
						_ribbonBoss->setIndex(0);
					else
						_ribbonBoss->setIndex(8);
				}

				_beAttactedNum = i;
				if (_ribbonBoss->getDir() == LEFT)
				{
					_ribbonBoss->setX(_ribbonBoss->getPos().x + cosf(PI / 180 * 45) * 1);
				}
				else
				{
					_ribbonBoss->setX(_ribbonBoss->getPos().x + cosf(PI / 180 * 135) * 1);
				}
			}
		}

		//파이널보스
		if (SAVEDATA->getCurrentStage() == FINALBOSS)
		{
			RECT _rct;

			if (IntersectRect(&_rct, &_player->getAttactRc()[i], &_finalBoss->getRect()) && !_finalBoss->getIsAttacted())
			{
				_finalBoss->setState(BEATTACTED);
				_finalBoss->setIsAttacted(true);
				_finalBoss->setDontMove(true);
				_finalBoss->setDamsX(_finalBoss->getPos().x - 25);
				_finalBoss->setDamsY(_finalBoss->getPos().y - 60);
				_finalBoss->setCurHp(_finalBoss->getCurHp() - _player->getStrikingPower()[i]);

				if (_finalBoss->getCurHp() < 0)
				{
					SOUNDMANAGER->play("리본클리어", SAVEDATA->getEffSound());
					SOUNDMANAGER->play("최종보스입장브금", SAVEDATA->getBgmSound());

					_finalBoss->setIsDead(true);
					_finalBoss->setState(DEAD);
					if (_finalBoss->getDir() == LEFT)
						_finalBoss->setIndex(0);
					else
						_finalBoss->setIndex(8);
				}

				_beAttactedNum = i;
				if (_finalBoss->getDir() == LEFT)
				{
					_finalBoss->setX(_finalBoss->getPos().x + cosf(PI / 180 * 45) * 1);
				}
				else
				{
					_finalBoss->setX(_finalBoss->getPos().x + cosf(PI / 180 * 135) * 1);
				}
			}
		}
	}


	//리본스킬 & 일반몹
	for (int i = 0; i < _player->getRibbon()->getBullet()->getBigBullet().size(); ++i)
	{
		for (int j = 0; j < _vEnemy.size(); j++)
		{

			RECT _rct;
			if (IntersectRect(&_rct, &_player->getRibbon()->getBullet()->getBigBullet()[i].rc, &_vEnemy[j]->getRealSizeRc()) && !_vEnemy[j]->getIsAttacted() && !_vEnemy[j]->getIsDead())
			{
				_vEnemy[j]->setState(E_BEATTACTED);
				_vEnemy[j]->setIsAttacted(true);
				_vEnemy[j]->setDontMove(true);
				_vEnemy[j]->setDamsX(_vEnemy[j]->getPos().x - 25);
				_vEnemy[j]->setDamsY(_vEnemy[j]->getPos().y - 60);
				_vEnemy[j]->setHp(_vEnemy[j]->getHp() - _player->getRibbon()->getSkillPower());

				if (_vEnemy[j]->getHp() < 0)
				{
					_vEnemy[j]->setIsDead(true);
					_vEnemy[j]->setState(E_DEAD);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * 120) * (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 120) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left) * 1.2);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * 240) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 240) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.2);
					EFFECTMANAGER->play_png("죽임이펙트1", _vEnemy[j]->getPos().x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * 360) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.5, _vEnemy[j]->getPos().y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - sinf(PI / 180 * 360) *  (_vEnemy[j]->getRealSizeRc().right - _vEnemy[j]->getRealSizeRc().left)* 1.2);
					EFFECTMANAGER->play_png("돈획득이펙트1", 1200, 600);
					_player->setGold(_player->getGold() + 1000);

				}

				_beAttactedNum = 7;
				if (_vEnemy[j]->getDirection() == LEFT)
				{
					_vEnemy[j]->setX(_vEnemy[j]->getPos().x + cosf(PI / 180 * 45) * 30);
				}
				else
				{
					_vEnemy[j]->setX(_vEnemy[j]->getPos().x + cosf(PI / 180 * 135) * 30);
				}
			}


		}
	}

	//일반몹
	for (int j = 0; j < _vEnemy.size(); j++)
	{
		if (_vEnemy[j]->getIsAttacted())
		{
			_vEnemy[j]->setInvincibleStateCount(_vEnemy[j]->getInvincibleStateCount() + 1);
			if (_vEnemy[j]->getInvincibleStateCount() == 15)
			{

				_vEnemy[j]->setDontMove(false);
				_vEnemy[j]->setInvincibleStateCount(0);
				_vEnemy[j]->setIsAttacted(false); 
			}
		}
	}

	//리본보스
	if (SAVEDATA->getCurrentStage() == STAGEBOSS1)
	{
		if (_ribbonBoss->getIsAttacted())
		{
			_ribbonBoss->setInvincibleStateCount(_ribbonBoss->getInvincibleStateCount() + 1);
			if (_ribbonBoss->getInvincibleStateCount() == 20)
			{
				_ribbonBoss->setDontMove(false); 
				_ribbonBoss->setInvincibleStateCount(0);
				_ribbonBoss->setIsAttacted(false); 
			}
		}

	}

	//파이널보스
	if (SAVEDATA->getCurrentStage() == FINALBOSS)
	{
		if (_finalBoss->getIsAttacted())
		{
			_finalBoss->setInvincibleStateCount(_finalBoss->getInvincibleStateCount() + 1);
			if (_finalBoss->getInvincibleStateCount() == 20)
			{
				_finalBoss->setDontMove(false);
				_finalBoss->setInvincibleStateCount(0);
				_finalBoss->setIsAttacted(false);
			}
		}

	}

}

void RBenemyManager::load(int sceneNum)
{
	string strEnemy;
	strEnemy = "enemyInf" + to_string(sceneNum + 1) + ".txt";

	_vEnemyInf = TXTDATA->loadTXT(strEnemy.c_str());

}
