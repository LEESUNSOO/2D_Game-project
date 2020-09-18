#include "stdafx.h"
#include "yerinaT.h"
#include "RBenemyManager.h"
//#include "stage1_MAPt.h"

HRESULT yerinaT::init(void)
{
	
	_keymg = new keyManager;

	
	// 상태
	_state = IDLE;
	_hammer = HAMMER1;
	_direction = RIGHT;
	_bodyIndex = _count = 0;
	_chargeCount = 40;

	ZeroMemory(&_yerina, sizeof(rabiribiPlayer));

	/*_yerina.x = 750;
	_yerina.y = 514;*/
	_yerina.maxHp = 500;
	_yerina.curHp = 148;
	_yerina.maxEnergy = 100;
	_yerina.curEnergy = 80;
	_yerina.gold = 11058;
	_yerina.oldX = _yerina.x;
	_yerina.oldY = _yerina.y;
	_yerina.angle = PI / 2;
	_yerina.speed = 4.5f;
	_yerina.jumpSpeed = YERINAJUMPSPEED;
	_yerina._isClimb = false;
	_yerina._isFall = false;
	_yerina._isHeadCollide = false;
	_yerina._isPushDownKey = false;
	_yerina._isPushUpkey = false;
	_yerina._isSlde = false;
	_yerina._isLRCollide = false;
	_yerina._isSpringJump = false;
	_yerina._isStartBattle = false;

	//리본데려오기
	_yerina.isClearStage1 = false; 


	//피격시
	_yerina._isAttacted = false;
	_yerina._dontMove = false;
	_yerina.invincibleStateCount = 0;
	_yerina.invincibleAlpha = 0;

	//잔상렉트
	for (int i = 0; i < AFTERIMAGES; i++)
	{
		_yerina.afterImageRc[i].radius = 200;
		_yerina.afterImageRc[i].speed = 8.5f;// -0.3f*i;
		_yerina.afterImageRc[i].angle = (i == 0) ? RND->getFloat(2 * PI) : _yerina.afterImageRc[i - 1].angle;
		_yerina.afterImageRc[i].x = _yerina.x;
		_yerina.afterImageRc[i].y = _yerina.y;
		_yerina.afterImageRc[i].alpha = 255 - 25 * i;

		_yerina.afterImageRc[i].isActive = false;

	}

	//커맨드
	_yerina.commandNum = 0;
	_yerina.commandCount = 0;
	_yerina.isActiveCommand = false;
	_yerina.isCommanding = false;
	_yerina._isAttactDown = false;
	_yerina._isAttactUp = false;
	_yerina.strikingPower[HAMMER1] = 20;
	_yerina.strikingPower[HAMMER2] = 17;
	_yerina.strikingPower[HAMMER3] = 19;
	_yerina.strikingPower[HAMMER4] = 23;
	_yerina.strikingPower[HAMMER5] = 5;
	_yerina.strikingPower[HAMMERDOWN] = 25;
	_yerina.strikingPower[HAMMERUP] = 25;
	_yerina.strikingPower[RIBBONSKILL] = 30;

	//_yerina.strikingPower[] = ;
	for (int i = 0; i < 8; ++i)
	{
		_yerina.isAttacting[i] = false;
		_yerina.strikingPower_upCount[i] = 0;
		_yerina.strikingPower_upRange[i] = 10;
	}

	// IDLE, JUMP, FALL, BOMB, SPRINGJUMP, MOVE, SLIDE, DEAD, ATTACT1, ATTACT2, ATTACT3, ATTACT4, ATTACT5, DOWNATTACT, UPATTACT, YERINAEND

	_yerinaImg[IDLE] = IMAGEMANAGER->addFrameImage("에리나IDLE", "resource/player/에리나IDLE.bmp", 1600, 400, 8, 2);
	_yerinaImg[JUMP] = IMAGEMANAGER->addFrameImage("에리나JUMP", "resource/player/에리나JUMP.bmp", 400, 400, 2, 2);
	_yerinaImg[FALL] = IMAGEMANAGER->addFrameImage("에리나FALL", "resource/player/에리나FALL.bmp", 400, 400, 2, 2);
	_yerinaImg[BOMB] = IMAGEMANAGER->addFrameImage("에리나CARROT", "resource/player/에리나CARROT.bmp", 2000, 400, 10, 2);
	_yerinaImg[SPRINGJUMP] = IMAGEMANAGER->addFrameImage("에리나SPRINGJUMP", "resource/player/에리나SPRINGJUMP.bmp", 1200, 400, 6, 2);
	_yerinaImg[MOVE] = IMAGEMANAGER->addFrameImage("에리나RUN", "resource/player/에리나MOVE.bmp", 1200, 400, 6, 2);
	_yerinaImg[SLIDE] = IMAGEMANAGER->addFrameImage("에리나SLIDE", "resource/player/에리나SLIDE.bmp", 800, 400, 4, 2);
	_yerinaImg[BEATTACTED] = IMAGEMANAGER->addFrameImage("에리나BEATTACTED", "resource/player/에리나BEATTACTED.bmp", 400, 400, 2, 2);
	_yerinaImg[DEAD] = IMAGEMANAGER->addFrameImage("에리나DEAD", "resource/player/에리나DEAD.bmp", 3400, 400, 17, 2);

	_yerinaImg[ATTACT1] = IMAGEMANAGER->addFrameImage("에리나ATTACT1", "resource/player/에리나ATTACT1.bmp", 1200, 400, 6, 2);
	_yerinaImg[ATTACT2] = IMAGEMANAGER->addFrameImage("에리나ATTACT2", "resource/player/에리나ATTACT2.bmp", 1400, 400, 7, 2);
	_yerinaImg[ATTACT3] = IMAGEMANAGER->addFrameImage("에리나ATTACT3", "resource/player/에리나ATTACT3.bmp", 1400, 400, 7, 2);
	_yerinaImg[ATTACT4] = IMAGEMANAGER->addFrameImage("에리나ATTACT4", "resource/player/에리나ATTACT4.bmp", 1200, 400, 6, 2);
	_yerinaImg[ATTACT5] = IMAGEMANAGER->addFrameImage("에리나ATTACT5", "resource/player/에리나ATTACT5.bmp", 1000, 400, 5, 2);
	_yerinaImg[DOWNATTACT] = IMAGEMANAGER->addFrameImage("에리나DOWNATTACT", "resource/player/에리나DOWNATTACT.bmp", 1000, 400, 5, 2);
	_yerinaImg[UPATTACT] = IMAGEMANAGER->addFrameImage("에리나UPATTACT", "resource/player/에리나UPATTACT.bmp", 1000, 400, 5, 2);
	IMAGEMANAGER->addImage("에리나DOWN잔상", "resource/player/에리나DOWN잔상2.bmp", 200, 400, true, MAGENTA);
	IMAGEMANAGER->addImage("에리나UP잔상", "resource/player/에리나UP잔상.bmp", 200, 400, true, MAGENTA);
	IMAGEMANAGER->addImage("에리나SLIDE잔상", "resource/player/에리나SLIDE잔상.bmp", 200, 400, true, MAGENTA);



	//_yerinaHammer[NOEXIST] = NULL;
	_yerinaHammer[HAMMER1] = IMAGEMANAGER->addFrameImage("해머1", "resource/player/해머1.bmp", 320, 400, 4, 2);
	_yerinaHammer[HAMMER2] = IMAGEMANAGER->addFrameImage("해머2", "resource/player/해머2.bmp", 850, 200, 5, 2);
	_yerinaHammer[HAMMER3] = IMAGEMANAGER->addFrameImage("해머3", "resource/player/해머3.bmp", 1500, 220, 10, 2);
	_yerinaHammer[HAMMER4] = IMAGEMANAGER->addFrameImage("해머4", "resource/player/해머4.bmp", 320, 400, 4, 2);
	_yerinaHammer[HAMMER5] = IMAGEMANAGER->addFrameImage("해머5", "resource/player/해머5.bmp", 264, 108, 4, 2);
	_yerinaHammer[HAMMERDOWN] = IMAGEMANAGER->addFrameImage("해머DOWN", "resource/player/해머DOWN.bmp", 229, 108, 4, 2);
	_yerinaHammer[HAMMERUP] = IMAGEMANAGER->addFrameImage("해머UP", "resource/player/해머UP.bmp", 229, 108, 4, 2);



	// 카메라 중점잡아주기
	cameraX = WINSIZEX / 2;
	cameraY = WINSIZEY / 2;


	CAMERAMANAGER->init("플레이어카메라", cameraX, cameraY, cameraX, cameraY, WINSIZEX, WINSIZEY);




	checkckckckkcckk = false;

	//스프링
	isSpringActive = false;


	//리본할당
	_ribbon = new ribbonT;
	_ribbon->init();
	_ribbon->setX(_yerina.x);
	_ribbon->setY(_yerina.y - 100);

	//당근할당
	_carrot = new yerinaCarrot;
	_carrot->init();
	IMAGEMANAGER->addImage("당근", "resource/player/CARROT.bmp", 30, 28, true, MAGENTA);

	return S_OK;
}

void yerinaT::release(void)
{
}

void yerinaT::update(stage_MAPt* _stageMap)
{
	_count++;
	

	this->keyInPut(_stageMap);
	this->makingBodyRc();
	this->makingAttactRc();

	this->makingAfterImageRc();
	this->tileCollision(_stageMap);
	this->enemyBodyCollision();
	//if (SAVEDATA->getCurrentStage() == STAGEBOSS1)
	this->BossCollision();

	this->move();
	if(_state < ATTACT1)
		this->animation();
	else
		this->commandAnimation();
	this->springCollision(_stageMap);

	_carrot->update();

	if(_yerina.isClearStage1)
		_ribbon->update(_yerina.x, _yerina.y, _yerina.speed, _direction);

}

void yerinaT::render(void)
{

	for (int i = 0; i < 10; i++)
	{
		if (_yerina.afterImageRc[i].isActive)// && _yerina.y > _yerina.afterImageRc[9].y)
		//if ( _yerina.afterImageRc[i].isActive && _yerina.y > _yerina.afterImageRc[9].y)
		{
			//IMAGEMANAGER->alphaRender("에리나DOWN잔상", getMemDC(), _yerina.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 100, _yerina.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top - 100, 0, 0, 200, 200, 100);
			//Rectangle(getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
			if (_state == DOWNATTACT)
			{
				if (_direction == LEFT)
					IMAGEMANAGER->alphaRender("에리나DOWN잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
				else
					IMAGEMANAGER->alphaRender("에리나DOWN잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 200, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
			}
			else if (_state == UPATTACT)
			{
				if (_direction == LEFT)
					IMAGEMANAGER->alphaRender("에리나UP잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
				else
					IMAGEMANAGER->alphaRender("에리나UP잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 200, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

			}
			else if (_state == SLIDE)
			{
				if (_direction == LEFT)
					IMAGEMANAGER->alphaRender("에리나SLIDE잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top +30 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 0, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
				else
					IMAGEMANAGER->alphaRender("에리나SLIDE잔상", getMemDC(), _yerina.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.top +30 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 0, 200, 200, 200, _yerina.afterImageRc[i].alpha);// _yerina.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

			}
		}


	}

	if(_yerina._isAttacted)
		_yerinaImg[_state]->alphaFrameRender(getMemDC(), _yerina.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerinaImg[_state]->getFrameX(), _yerinaImg[_state]->getFrameY(),_yerina.invincibleAlpha);
	else
		_yerinaImg[_state]->frameRender(getMemDC(), _yerina.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerinaImg[_state]->getFrameX(), _yerinaImg[_state]->getFrameY());


	for (int i = 0; i < 8; i++)
	{
		if (_yerina.isAttacting[i])
		{
			if (KEYMANAGER->isToggleKey(VK_F10))
				Rectangle(getMemDC(), _yerina.attackRc[i].left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.attackRc[i].top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.attackRc[i].right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.attackRc[i].bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
			//_yerinaHammer[_hammer]->stretchFrameRender(getMemDC(), _yerina.attackRc[i].left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.attackRc[i].top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerinaHammer[_hammer]->getFrameX(), _yerinaHammer[_hammer]->getFrameY());
					_yerinaHammer[_hammer]->frameRender(getMemDC(), _yerina.attackRc[i].left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.attackRc[i].top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerinaHammer[_hammer]->getFrameX(), _yerinaHammer[_hammer]->getFrameY());

		}
	}



	_carrot->render();

	if (_yerina.isClearStage1)
		_ribbon->render();

	this->debug();

	char checking[128];
	wsprintf(checking, "%d", _state);
	TextOut(getMemDC(), 900, 100, checking, strlen(checking));

	char checkGravity[128];
	sprintf(checkGravity, "%f", _yerina.gravity);
	TextOut(getMemDC(), 900, 120, checkGravity, strlen(checkGravity));

	char checkBool1[128];
	wsprintf(checkBool1, "%d", _yerina._isFall);
	TextOut(getMemDC(), 900, 140, checkBool1, strlen(checkBool1));

	char checkingboo[128];
	wsprintf(checkingboo, "%d", checkckckckkcckk);
	TextOut(getMemDC(), 900, 160, checkingboo, strlen(checkingboo));

	
	char checkingY[128];
	sprintf(checkingY, "%f", _yerina.y);
	TextOut(getMemDC(), 900, 180, checkingY, strlen(checkingY));
}

void yerinaT::keyInPut(stage_MAPt* _stageMap)
{

	if (!_yerina.isActiveCommand && !_yerina._dontMove)
	{
		//if (_keymg->isStayKeyDown(VK_RIGHT) && _state != BOMB)
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _state != BOMB)
		{

			if (_yerina.LRColliRc.right < _stageMap->getL_X())
			{
				//EFFECTMANAGER->play_png("타격이펙트2", _yerina.x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.y - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

				if (_yerina.speed < 7.5f)
					_yerina.speed *= 1.0045f;
				_yerina.x += _yerina.speed;
			}

			if (_state != JUMP && _state != FALL && _state != SPRINGJUMP && _state != UPATTACT && _state != DOWNATTACT && _state != SLIDE)
				_state = MOVE;
			_direction = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _state != BOMB)
		{
			if (_state != JUMP && _state != FALL && _state != SPRINGJUMP)
				_state = IDLE;
			_yerina.speed = 4.5;
		}


		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _state != BOMB)
		{
			if (_yerina.LRColliRc.left > 0)
			{
				if (_yerina.speed < 7.5f)
					_yerina.speed *= 1.0045f;
				_yerina.x -= _yerina.speed;
			}

			if (_state != JUMP && _state != FALL && _state != SPRINGJUMP && _state != UPATTACT && _state != DOWNATTACT && _state != SLIDE)
				_state = MOVE;
			_direction = LEFT;

		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _state != BOMB)
		{
			if (_state != JUMP && _state != FALL && _state != SPRINGJUMP)
				_state = IDLE;
			_yerina.speed = 4.5;

		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_yerina._isPushDownKey = true;

	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_yerina._isPushDownKey = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_yerina._isPushUpkey = true;

	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_yerina._isPushUpkey = false;
	}

	//점프 및 확인버튼
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_yerina._isPushDownKey)
		{
			_state = SLIDE;
			_yerina._isSlde = true;
			SOUNDMANAGER->play("슬라이드", SAVEDATA->getEffSound());

		}
		else
		{
			_state = JUMP;
			SOUNDMANAGER->play("점프", SAVEDATA->getEffSound());
		}
		if (_direction == LEFT)
			_bodyIndex = 0;
		if (_direction == RIGHT)
			_bodyIndex = 2;
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (_state != IDLE && _state != MOVE && _yerina.jumpSpeed < 25.f)
			//_yerina.jumpSpeed += 0.6f;
			_yerina.jumpSpeed *= 1.1f;

	}
	//리본공격

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (_direction == LEFT)
		{
			_ribbon->setX(_yerina.x - 150);
			_ribbon->setY(_yerina.y - 15);
		}
		else
		{
			_ribbon->setX(_yerina.x + 100);
			_ribbon->setY(_yerina.y - 15);
		}

		_ribbon->setCharge(_ribbon->getCharge() + 1);

		_ribbon->setIscharging(true);

		if (_count % (int)_chargeCount == 0)
		{
			SOUNDMANAGER->play("리본차징", SAVEDATA->getEffSound());
			if (_chargeCount > 20)
				_chargeCount *= 0.75f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		if (_ribbon->getCharge() > 100 && _ribbon->getCurMp()>=20)
		{
			_ribbon->fire(_yerina.x, _yerina.y, _direction);
			_ribbon->setCurMp(_ribbon->getCurMp() - 20);
			SOUNDMANAGER->play("리본블루총알파이어" , SAVEDATA->getEffSound());
			_chargeCount = 40;
		}

		_ribbon->setCharge(0);
		_ribbon->setIscharging(false);
		_ribbon->setChargingIndex(0);

	}

	// 공격 및 폭탄 버튼
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_yerina._isPushDownKey && _state == IDLE)
		{
			if (_direction == LEFT)
				_bodyIndex = 0;
			if (_direction == RIGHT)
				_bodyIndex = 10;
			_state = BOMB;
		}


		if (_yerina._isPushDownKey && (_state == JUMP || _state == FALL || _yerina._isFall))
		{
			_yerina._isAttactDown = true;
			_yerina.isCommanding = true;
			_yerina.isAttacting[HAMMERDOWN] = true;
			SOUNDMANAGER->play("다운해머", SAVEDATA->getEffSound());
		}

		if (_yerina._isPushUpkey && (_state == IDLE || _state == MOVE))
		{
			_yerina._isAttactUp = true;
			_yerina.isCommanding = true;
			_yerina.isAttacting[HAMMERUP] = true;
			SOUNDMANAGER->play("업해머", SAVEDATA->getEffSound());

			_state = UPATTACT;
			if (_direction == LEFT)
				_bodyIndex = 0;
			if (_direction == RIGHT)
				_bodyIndex = 4;
		}

		if (!_yerina.isActiveCommand && !_yerina._isPushDownKey && (_state == IDLE || _state == MOVE) && _yerina.curEnergy > 10)
		{
			_yerina.isActiveCommand = true;
			_yerina.commandNum = 0;
			_yerina.isCommanding = true;
			if (_yerina.curEnergy > 10)
				_yerina.curEnergy -= 10;
			//_yerina.isCommand[0] = true;
			_state = ATTACT1;
			_yerina.isAttacting[HAMMER1] = true;
			_hammer = HAMMER1;
			SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());

		}
		else if (_yerina.isActiveCommand && _yerina.commandNum < 4 && !_yerina._isPushDownKey && _yerina.curEnergy > 10)
		{
			_yerina.commandNum++;
			_yerina.isCommanding = true;
			if(_yerina.curEnergy > 10)
				_yerina.curEnergy -= 10;

			switch (_yerina.commandNum)
			{

			case 1:
				_state = ATTACT2;
				_yerina.isAttacting[HAMMER2] = true;
				_yerina.isAttacting[HAMMER1] = false;
				SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());
				break;
			case 2:
				_state = ATTACT3;
				_yerina.isAttacting[HAMMER3] = true;
				_yerina.isAttacting[HAMMER2] = false;
				SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());

				break;
			case 3:
				_state = ATTACT4;
				_yerina.isAttacting[HAMMER4] = true;
				_yerina.isAttacting[HAMMER3] = false;
				SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());

				break;
			case 4:
				_state = ATTACT5;
				_yerina.isAttacting[HAMMER5] = true;
				_yerina.isAttacting[HAMMER4] = false;

				break;

			default:
				break;
			}

			if (_direction == LEFT)
			{
				_bodyIndex = 0;
				_hammerIndex = 0;
			}
			if (_direction == RIGHT)
			{
				_bodyIndex = _yerinaImg[_state]->getMaxFrameX();
				_hammerIndex = _yerinaHammer[_hammer]->getMaxFrameX();
			}
			_yerina.commandCount = 0;

		}

	}

	if (_yerina.isActiveCommand)
	{
		_yerina.commandCount++;
		if (_state == ATTACT5)
		{
			if (_yerina.commandCount > _yerinaImg[_state]->getMaxFrameX() * 20)
			{
				_yerina.isCommanding = false;
				_yerina.isActiveCommand = false;
				_yerina.commandCount = 0;
				_yerina.commandNum = 0;
				_yerina.isAttacting[HAMMER5] = false;
				_state = IDLE;
			}
		}
		else
		{
			if (_yerina.commandCount > _yerinaImg[_state]->getMaxFrameX() * 3)
			{
				_yerina.isCommanding = false;
				_yerina.isActiveCommand = false;
				_yerina.commandCount = 0;
				_yerina.commandNum = 0;
				for (int i = 0; i < 8; i++)
					_yerina.isAttacting[i] = false;
				_state = IDLE;
			}
		}

	}

	if (_count % 4 == 0)
		if (_yerina.curEnergy < _yerina.maxEnergy)
			_yerina.curEnergy++;

}

void yerinaT::move()
{
	switch (_state)
	{

	case JUMP:
		_yerina.gravity += 0.98f;
		_yerina.y += -sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity;
		if (-sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity > 0)
		{
			_state = FALL;
			if (_yerina._isAttactDown)
				_state = DOWNATTACT;
		}
		break;
	case SPRINGJUMP:
		_yerina.gravity += 0.98f;
		_yerina.y += -sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity;
		if (-sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity > 0)
		{
			_state = FALL;
			if (_yerina._isAttactDown)
				_state = DOWNATTACT;
		}
		break;

	case FALL:
		if (_yerina._isFall)
		{
			_yerina.gravity += 0.5f;
			_yerina.y += _yerina.gravity;
			//_yerina.y += -sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity;
			if (_yerina._isAttactDown)
				_state = DOWNATTACT;

			if (_yerina._isSlde)
			{
				_state = SLIDE;
			}
		}
		else if (_yerina._isHeadCollide)
		{		
			_yerina.gravity *= 0.96f;
			_yerina.y += (1 / _yerina.gravity) * 200;
		}
		
		else
		{
			_yerina.gravity += 0.98f;
			_yerina.y += -sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity;
			if (_yerina._isAttactDown)
				_state = DOWNATTACT;

			if (_yerina._isSlde)
			{
				_state = SLIDE;
			}
		}


		break;

	case DOWNATTACT:
		_yerina.gravity += 0.98f;
		_yerina.y += -sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity;
		for (int i = 0; i < AFTERIMAGES; i++)
		{
			if (_yerina.afterImageRc[i].y < _yerina.y)
				_yerina.afterImageRc[i].isActive = true;
		}
		break;


	case UPATTACT:
		_yerina.gravity += 0.7f;
		if (_direction == LEFT)
		{
			_yerina.x += cosf(PI / 180 * 110) * 5;
			_yerina.y += -sinf(_yerina.angle) * 22 + _yerina.gravity;

		}
		else
		{
			_yerina.x += cosf(PI / 180 * 70) * 5;
			_yerina.y += -sinf(_yerina.angle) * 22 + _yerina.gravity;

		}

		for (int i = 0; i < AFTERIMAGES; i++)
		{
			if (_yerina.afterImageRc[i].y > _yerina.y)
				_yerina.afterImageRc[i].isActive = true;
		}


		if (-sinf(_yerina.angle)*_yerina.jumpSpeed + _yerina.gravity > 0)
		{
			_state = FALL;
			if (_yerina._isAttactDown)
				_state = DOWNATTACT;
		}
		break;
	case SLIDE:
		if (_direction == LEFT)
		{
			_yerina.gravity += 0.5f;
			_yerina.x -= _yerina.speed * 5 - _yerina.gravity;
			if (_yerina.speed * 5 - _yerina.gravity < 0)
			{
				_state = IDLE;
				_yerina._isSlde = false;
				_yerina.gravity = 0;
			}
		}

		else
		{
			_yerina.gravity += 0.5f;
			_yerina.x += _yerina.speed * 5 - _yerina.gravity;
			if (_yerina.speed * 5 - _yerina.gravity < 0)
			{
				_state = IDLE;
				_yerina._isSlde = false;
				_yerina.gravity = 0;
			}

		}
		for (int i = 0; i < AFTERIMAGES; i++)
		{
			if (_direction == LEFT)
			{
				if (_yerina.afterImageRc[i].x > _yerina.x)
					_yerina.afterImageRc[i].isActive = true;
			}
			else
			{
				if (_yerina.afterImageRc[i].x < _yerina.x)
					_yerina.afterImageRc[i].isActive = true;
			}
		}
		break;
	}

}
void yerinaT::makingBodyRc()
{
	_yerina.rc = RectMakeCenter(_yerina.x, _yerina.y, 200, 200);

	_yerina.beAttRc = RectMakeCenter(_yerina.x, _yerina.y, 30, 128);

	_yerina.LRColliRc = RectMake(_yerina.x-10, _yerina.y, 20, 20);

	_yerina.tileCollRc = RectMakeCenter(_yerina.x, _yerina.y , 1, YERINASIZE - 2);

	_yerina.bottomTileCheckRc = RectMake(_yerina.x, _yerina.y + 80, 1, 2 );

	_yerina.topTileCheckRc = RectMake(_yerina.x, _yerina.y - 60, 1, 2);

	_yerina.pixelRc = RectMake(_yerina.x , _yerina.y + 50, 1, 78);

	_yerina.realSizeRc = RectMakeCenter(_yerina.x, _yerina.y, 60, 200);
}
void yerinaT::makingAfterImageRc()
{
	for (int i = 0; i < AFTERIMAGES; i++)
	{

		if (i == 0) //머리냐?
		{

			_yerina.afterImageRc[i].x = _yerina.x;
			_yerina.afterImageRc[i].y = _yerina.y - 30;


		}
		else//구슬 첫번째를 따라오는 몸통들 (지렁이 따라오는 핵심)
		{
			float distance = getDistance(_yerina.afterImageRc[i].x, _yerina.afterImageRc[i].y, _yerina.afterImageRc[i - 1].x, _yerina.afterImageRc[i - 1].y);

			if (distance > 30)// || distance < -5)
			{
				_yerina.afterImageRc[i].angle = getAngle(_yerina.afterImageRc[i].x, _yerina.afterImageRc[i].y, _yerina.afterImageRc[i - 1].x, _yerina.afterImageRc[i - 1].y);
				/*_yerina.afterImageRc[i].x = _yerina.afterImageRc[i - 1].x - cosf(_yerina.afterImageRc[i].angle) * (_yerina.afterImageRc[i].radius * 2);
				_yerina.afterImageRc[i].y = _yerina.afterImageRc[i - 1].y - (-sinf(_yerina.afterImageRc[i].angle)) * (_yerina.afterImageRc[i].radius * 2);*/
				_yerina.afterImageRc[i].x = _yerina.afterImageRc[i - 1].x - cosf(_yerina.afterImageRc[i].angle) * 30;
				_yerina.afterImageRc[i].y = _yerina.afterImageRc[i - 1].y - (-sinf(_yerina.afterImageRc[i].angle)) * 30;

				/*_yerina.afterImageRc[i].x = _yerina.x;
				_yerina.afterImageRc[i].y = _yerina.y;*/
				//_yerina.afterImageRc[i].speed = sinf(_yerina.afterImageRc[i].angle)*_yerina.jumpSpeed;// +_yerina.gravity;
			}


			_yerina.afterImageRc[i].x += cosf(_yerina.afterImageRc[i].angle) * _yerina.afterImageRc[i].speed;
			_yerina.afterImageRc[i].y += -sinf(_yerina.afterImageRc[i].angle) * _yerina.afterImageRc[i].speed;


			//else
			//	_yerina.afterImageRc[i].isActive = true;

		}

		if (_yerina.afterImageRc[i].y >= _yerina.y - 50)
			_yerina.afterImageRc[i].isActive = false;

		//if(_yerina.afterImageRc[i].isActive)
		_yerina.afterImageRc[i].rc = RectMakeCenter(_yerina.afterImageRc[i].x, _yerina.afterImageRc[i].y, _yerina.afterImageRc[i].radius, _yerina.afterImageRc[i].radius);
	}


}
void yerinaT::makingAttactRc()
{
	if (_yerina.isCommanding)
	{
		if (_direction == LEFT)
		{
			switch (_state)
			{
			case ATTACT1:
				_yerina.attackRc[HAMMER1] = RectMakeCenter(_yerina.x - 70, _yerina.y - 40, 70, 120);
				_hammer = HAMMER1;
				break;
			case ATTACT2:
				_yerina.attackRc[HAMMER2] = RectMake(_yerina.x - 75, _yerina.y - 25, 170, 100);
				_hammer = HAMMER2;

				break;
			case ATTACT3:
				_yerina.attackRc[HAMMER3] = RectMake(_yerina.x - 80, _yerina.y - 25, 170, 100);
				_hammer = HAMMER3;

				break;
			case ATTACT4:
				_yerina.attackRc[HAMMER4] = RectMakeCenter(_yerina.x - 70, _yerina.y - 40, 70, 120);
				_hammer = HAMMER4;

				break;
			case ATTACT5:
				_yerina.attackRc[HAMMER5] = RectMakeCenter(_yerina.x - 109, _yerina.y, 66, 50);
				_hammer = HAMMER5;
				break;
			case DOWNATTACT:
				_yerina.attackRc[HAMMERDOWN] = RectMakeCenter(_yerina.x -15 , _yerina.y + 70, 66, 50);
				_hammer = HAMMERDOWN;
				break;
			case UPATTACT:
				_yerina.attackRc[HAMMERUP] = RectMakeCenter(_yerina.x - 35, _yerina.y - 60, 66, 50);
				_hammer = HAMMERUP;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (_state)
			{
			case ATTACT1:
				_yerina.attackRc[HAMMER1] = RectMakeCenter(_yerina.x + 70, _yerina.y - 40, 70, 120);
				_hammer = HAMMER1;

				break;
			case ATTACT2:
				_yerina.attackRc[HAMMER2] = RectMake(_yerina.x - 90, _yerina.y - 25, 170, 100);
				_hammer = HAMMER2;

				break;
			case ATTACT3:
				_yerina.attackRc[HAMMER3] = RectMake(_yerina.x - 70, _yerina.y - 25, 170, 100);
				_hammer = HAMMER3;

				break;
			case ATTACT4:
				_yerina.attackRc[HAMMER4] = RectMakeCenter(_yerina.x + 70, _yerina.y - 40, 70, 120);
				_hammer = HAMMER4;

				break;
			case ATTACT5:
				_yerina.attackRc[HAMMER5] = RectMakeCenter(_yerina.x + 100, _yerina.y, 66, 50);
				_hammer = HAMMER5;

				break;

			case DOWNATTACT:
				_yerina.attackRc[HAMMERDOWN] = RectMakeCenter(_yerina.x +15 , _yerina.y + 70, 66, 50);
				_hammer = HAMMERDOWN;
				break;
			case UPATTACT:
				_yerina.attackRc[HAMMERUP] = RectMakeCenter(_yerina.x + 40, _yerina.y - 65, 66, 50);
				_hammer = HAMMERUP;
				break;

			default:
				break;
			}
		}

	}


	if (_state != ATTACT1)
		_yerina.attackRc[HAMMER1] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != ATTACT2)
		_yerina.attackRc[HAMMER2] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != ATTACT3)
		_yerina.attackRc[HAMMER3] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != ATTACT4)
		_yerina.attackRc[HAMMER4] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != ATTACT5)
		_yerina.attackRc[HAMMER5] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != DOWNATTACT)
		_yerina.attackRc[HAMMERDOWN] = RectMakeCenter(-100, -100, 66, 50);
	if (_state != UPATTACT)
		_yerina.attackRc[HAMMERUP] = RectMakeCenter(-100, -100, 66, 50);


}
void yerinaT::tileCollision(stage_MAPt* _stageMap)
{
	_currentTileX = _yerina.tileCollRc.left / TILESIZE;
	_currentTileY = _yerina.tileCollRc.top / TILESIZE;

	switch (_direction)
	{
	case LEFT:
		_collisionTileIndex[0] = _currentTileX + _currentTileY * TILEX;
		_collisionTileIndex[1] = _currentTileX + (_currentTileY - 1)* TILEX;
		_collisionTileIndex[2] = _currentTileX + _currentTileY * TILEX + 1;
		_collisionTileIndex[3] = _currentTileX + (_currentTileY - 1) * TILEX + 1;
		_collisionTileIndex[4] = _currentTileX + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[5] = _currentTileX + (_currentTileY + 1) * TILEX + 1;
		_collisionTileIndex[6] = _currentTileX + (_currentTileY + 1) * TILEX - 1 ;
		_collisionTileIndex[7] = _currentTileX + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY + 2) * TILEX - 1;
		_collisionTileIndex[9] = _currentTileX + (_currentTileY + 2) * TILEX + 1;
		_collisionTileIndex[10] = _currentTileX + (_currentTileY + 3) * TILEX;
		break;

	case RIGHT:
		_collisionTileIndex[0] = _currentTileX + _currentTileY * TILEX;
		_collisionTileIndex[1] = _currentTileX + _currentTileY * TILEX + 1;
		_collisionTileIndex[2] = _currentTileX + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[3] = _currentTileX + (_currentTileY - 1) * TILEX + 1;
		_collisionTileIndex[4] = _currentTileX + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[5] = _currentTileX + (_currentTileY + 1) * TILEX + 1;
		_collisionTileIndex[6] = _currentTileX + (_currentTileY + 1) * TILEX - 1;
		_collisionTileIndex[7] = _currentTileX + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY + 2) * TILEX - 1;
		_collisionTileIndex[9] = _currentTileX + (_currentTileY + 2) * TILEX + 1;
		_collisionTileIndex[10] = _currentTileX + (_currentTileY + 3) * TILEX ;
		break;

	}

	for (int i = 0; i < 4; ++i)
	{
		RECT _rct;

		if (_collisionTileIndex[i] < 0) continue;
		//상단충돌
		if (IntersectRect(&_rct, &_yerina.topTileCheckRc, &_stageMap->getTiles()[_collisionTileIndex[i]].rc) && !_stageMap->getCanPass()[_collisionTileIndex[i]] && _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_DOPASS && _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF)//  && !_yerina._isLRCollide)// && _state != MOVE)// (_state == FALL || _yerina._isFall) && && _stage1_map->getTiles()[_tileIndex[i]].terrain != TR_DIAGONAL)
		{
			
			_state = FALL;
			_yerina.rc.top = _stageMap->getTiles()[_collisionTileIndex[i]].rc.bottom - 42;
			_yerina.rc.bottom = _stageMap->getTiles()[_collisionTileIndex[i]].rc.bottom + 200 - 42;
			_yerina.y = _yerina.rc.top + (_yerina.rc.bottom - _yerina.rc.top) / 2;
			_yerina._isHeadCollide = true;
			if (_yerina._isLRCollide)
			{
				_yerina._isHeadCollide = false;
			}
			break;
		}
		
	}


	for (int i = 2; i < CHECKTILEINDEX; ++i)
	{
		RECT _rct;

		if (_collisionTileIndex[i] < 0) continue;

		//좌우충돌
		if (IntersectRect(&_rct, &_yerina.LRColliRc, &_stageMap->getTiles()[_collisionTileIndex[i]].rc)
			&& !_stageMap->getCanPass()[_collisionTileIndex[i]] 
			&& (_state == MOVE || _state == FALL || _state == JUMP) 
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF 
			&& !_yerina._isHeadCollide)// && _state !=FALL)
		{

			switch (_direction)
			{
			case LEFT:
				_yerina.rc.left = _stageMap->getTiles()[_collisionTileIndex[i]].rc.right - 90;
				_yerina.rc.right = _stageMap->getTiles()[_collisionTileIndex[i]].rc.right + 200 - 90;
				_yerina.x = _yerina.rc.left + (_yerina.rc.right - _yerina.rc.left) / 2;
				_yerina._isLRCollide = true;
				break;

			case RIGHT:
				_yerina.rc.right = _stageMap->getTiles()[_collisionTileIndex[i]].rc.left + 90;
				_yerina.rc.left = _stageMap->getTiles()[_collisionTileIndex[i]].rc.left - 200 + 90;
				_yerina.x = _yerina.rc.left + (_yerina.rc.right - _yerina.rc.left) / 2;// +100;
				_yerina._isLRCollide = true;

				break;

			}
		}
	/*	else
			_yerina._isLRCollide = false;*/

	}



	for (int i = 0; i < CHECKTILEINDEX; ++i)
	{
		RECT _rct;

		if (_collisionTileIndex[i] < 0) continue;

		//하단충돌
		if (IntersectRect(&_rct, &_yerina.bottomTileCheckRc, &_stageMap->getTiles()[_collisionTileIndex[i]].rc)
			&& (_stageMap->getCanPass()[_collisionTileIndex[i]] == false)
			&& (_state == FALL || _yerina._isFall || _state ==DOWNATTACT || _state == BEATTACTED)
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_DOPASS)// && _stage1_map->getTiles()[_tileIndex[i]].terrain != TR_NONE && _stage1_map->getTiles()[_tileIndex[i]].obj != OBJECT_NONE)// && _stage1_map->getTiles()[_tileIndex[i]].terrain != TR_DIAGONAL)
		{
			_state = IDLE;
			if (_yerina._dontMove)
				_state = BEATTACTED;
			//if (_stage1_map->getTiles()[_tileIndex[i]].terrain == TR_ROOF)
			//	_yerina._isClimb = true;
			_yerina.gravity = 0;
			_yerina.jumpSpeed = YERINAJUMPSPEED;
			_yerina.rc.bottom = _stageMap->getTiles()[_collisionTileIndex[i]].rc.top + 42;
			_yerina.rc.top = _stageMap->getTiles()[_collisionTileIndex[i]].rc.top - 200 + 42;
			_yerina.y = _yerina.rc.top + (_yerina.rc.bottom - _yerina.rc.top) / 2;
			_yerina._isFall = false;
			_yerina._isHeadCollide = false;
			_yerina._isLRCollide = false;
			_yerina._isAttactDown = false;
			_yerina.isAttacting[HAMMERDOWN] = false;

			checkckckckkcckk = true;

			break;
		}
		else
			checkckckckkcckk = false;

	}




	for (int i = 4; i < CHECKTILEINDEX; ++i)
	{
		RECT _rct;

		if (_collisionTileIndex[i] < 0) continue;

		//사선충돌	
		if (IntersectRect(&_rct, &_yerina.pixelRc, &_stageMap->getTiles()[_collisionTileIndex[i]].rc) && _stageMap->getTiles()[_collisionTileIndex[i]].terrain == TR_DIAGONAL && _state!=JUMP)
		{

			for (int j = 0; j < 64; j++)
			{
				COLORREF color = GetPixel(_stageMap->getTileImage(_stageMap->getTiles()[_collisionTileIndex[i]].tileType, _stageMap->getTiles()[_collisionTileIndex[i]].reverse)->getMemDC(), _stageMap->getTiles()[_collisionTileIndex[i]].terrainFrameX * 64 + (_yerina.x - _stageMap->getTiles()[_collisionTileIndex[i]].rc.left), _stageMap->getTiles()[_collisionTileIndex[i]].terrainFrameY * 64 + j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (!(r == 255 && g == 0 && b == 255))
				{

					_yerina.y = _stageMap->getTiles()[_collisionTileIndex[i]].rc.top + j - 64 + 6;// -(_yerina.pixelRc.top - _stage1_map->getTiles()[_tileIndex[i]].rc.top) - 64);

					_yerina.rc = RectMakeCenter(_yerina.x + _yerina.speed, _yerina.y, 200, 200);

					break;

				}
			}

		}

	}



	for (int i = 7; i < CHECKTILEINDEX; ++i)
	{
		RECT _rct;

		if (_collisionTileIndex[i] < 0) continue;

		//추락충돌
		if (IntersectRect(&_rct, &_stageMap->getTiles()[_collisionTileIndex[i]].rc, &_yerina.bottomTileCheckRc)
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_GROUND
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_DIAGONAL
			&& _stageMap->getTiles()[_collisionTileIndex[i]].terrain != TR_BOMB
			&& _stageMap->getTiles()[_collisionTileIndex[i]].obj != OBJECT_DONTPASS
			&& _state != JUMP && _state != FALL && _state != SPRINGJUMP && _state != UPATTACT && _state != SLIDE)// && !_yerina._isFall)
		{
			switch (_direction)
			{
			case LEFT:
				_yerina.rc = RectMakeCenter(_yerina.x - _yerina.speed, _yerina.y, 200, 200);
				//_yerina._isClimb = false;
				_state = FALL;
				if (_yerina._isAttactDown)
				{
					_state = DOWNATTACT;
				}
				_yerina._isFall = true;
				_yerina._isHeadCollide = false;
				break;

			case RIGHT:
				_yerina.rc = RectMakeCenter(_yerina.x + _yerina.speed, _yerina.y, 200, 200);
				//_yerina._isClimb = false;
				_state = FALL;
				if (_yerina._isAttactDown)
				{
					_state = DOWNATTACT;
				}
				_yerina._isFall = true;
				_yerina._isHeadCollide = false;

				break;

			}

		}
	}


		RECT _rctCarrot;
		int _carrotTileX;
		int _carrotTileY;


		//당근충돌
		for (int ofCarrot = 0; ofCarrot < _carrot->getVCarrot().size(); ++ofCarrot)
		{
			_carrotTileX = _carrot->getVCarrot()[ofCarrot].rc.left / TILESIZE;
			_carrotTileY = _carrot->getVCarrot()[ofCarrot].rc.top / TILESIZE;


			if (IntersectRect(&_rctCarrot, &_stageMap->getTiles()[_carrotTileX + _carrotTileY * TILEX].rc, &_carrot->getVCarrot()[ofCarrot].rc) && _stageMap->getTiles()[_carrotTileX + _carrotTileY * TILEX].terrain == TR_BOMB)
			{
				for (int bombSiteX = 0; bombSiteX < 2; bombSiteX++)
				{
					for (int bombSiteY = 0; bombSiteY < 2; bombSiteY++)
					{
						if (_carrotTileX + (_carrotTileY + bombSiteY) * TILEX + bombSiteX > TILEX * TILEY) continue;
						if (_stageMap->getTiles()[_carrotTileX + (_carrotTileY + bombSiteY) * TILEX + bombSiteX].terrain != TR_BOMB) continue;
						_stageMap->setTerrain(_carrotTileX + (_carrotTileY + bombSiteY) * TILEX + bombSiteX, TR_NONE);
						_stageMap->setObject(_carrotTileX + (_carrotTileY + bombSiteY) * TILEX + bombSiteX, OBJECT_NONE);
						_stageMap->setCanPass(_carrotTileX + (_carrotTileY + bombSiteY) * TILEX + bombSiteX, true);

					}

				}
			
				_carrot->setVCarrotY(_stageMap->getTiles()[_carrotTileX + _carrotTileY * TILEX].rc.top + _carrot->getVCarrot()[ofCarrot].radius / 2, ofCarrot);
				_carrot->setVCarrotGravity(0, ofCarrot);

				break;
			}
		}


}
void yerinaT::enemyBodyCollision()
{
	for (int i = 0; i < _eMG->getVEnemy().size(); ++i)
	{
		//에너미 충돌
		RECT _rct;
		if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getVEnemy()[i]->getRealSizeRc()) 
			&& !_yerina._isAttacted 
			&& !_eMG->getVEnemy()[i]->getIsAttacted()
			&& !_eMG->getVEnemy()[i]->getIsDead() 
			&& !_eMG->getVEnemy()[i]->getDontMove())
		{
			SOUNDMANAGER->play("데미지",SAVEDATA->getEffSound());
			_state = BEATTACTED;
			_yerina._isAttacted = true;
			_yerina._dontMove = true;
			_yerina.curHp -= 10;
			if (_direction == LEFT)
			{
				_yerina.x += cosf(PI / 180 * 45) * 30;
				//_yerina.y += -sinf(PI / 180 * 45) * 30;
			}
			else
			{
				_yerina.x += cosf(PI / 180 * 135) * 30;
				//_yerina.y += -sinf(PI / 180 * 135) * 30;
			}

		}
	}


	if (_yerina._isAttacted)
	{
		_yerina.invincibleStateCount++;
		_yerina.invincibleAlpha += 150;
		if (_yerina.invincibleStateCount == 10)
		{
			_yerina._dontMove = false;
		}
		if (_yerina.invincibleStateCount > 50)
		{
			_yerina.invincibleStateCount = 0;
			_yerina.invincibleAlpha = 0;
			_yerina._isAttacted = false;
		}
	}



}
void yerinaT::BossCollision()
{
	if (SAVEDATA->getCurrentStage() == STAGEBOSS1)
	{
		//보스충돌
		RECT _rct;
		if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getRect()) && !_yerina._isAttacted)
		{
			_state = BEATTACTED;
			_yerina._isAttacted = true;
			_yerina._dontMove = true;
			_yerina.curHp -= 10;
			SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());

			if (_direction == LEFT)
			{
				_yerina.x += cosf(PI / 180 * 45) * 30;
				//_yerina.y += -sinf(PI / 180 * 45) * 30;
			}
			else
			{
				_yerina.x += cosf(PI / 180 * 135) * 30;
				//_yerina.y += -sinf(PI / 180 * 135) * 30;
			}
		}


		if (_eMG->getRibbon()->getFinalSkill()[BBYORORONG])
		{
			for (int i = 0; i < _eMG->getRibbon()->getRibbonBlueBullet()->getBigBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getRibbonBlueBullet()->getBigBullet()[i].rc) && !_yerina._isAttacted)
				{

					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getRibbon()->getRibbonBlueBullet()->getBigBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());

					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}

		if (_eMG->getRibbon()->getFinalSkill()[BLUERAIN])
		{
			for (int i = 0; i < _eMG->getRibbon()->getRibbonBlueRain()->getBlueRain().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getRibbonBlueRain()->getBlueRain()[i].rc) && !_yerina._isAttacted)
				{
					//if (!_eMG->getRibbon()->getRibbonBlueRain()->getBlueRain()[i].isfire) continue;
					//if (!_eMG->getRibbon()->getRibbonBlueRain()->getBlueRain()[i].isActive_first) continue;

					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getRibbon()->getRibbonBlueRain()->getBlueRain()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}

		if (_eMG->getRibbon()->getFinalSkill()[SUNBEAM])
		{
			for (int i = 0; i < _eMG->getRibbon()->getSunFlowerBullet()->getSun().size(); i++)
			{
				for (int j = 0; j < _eMG->getRibbon()->getSunFlowerBullet()->getSun()[i].size(); j++)
				{
					if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getSunFlowerBullet()->getSun()[i][j].rc) && !_yerina._isAttacted)
					{
						_state = BEATTACTED;
						_yerina._isAttacted = true;
						_yerina._dontMove = true;
						_yerina.curHp -= _eMG->getRibbon()->getSunFlowerBullet()->getSun()[0][0].damage;
						SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


						if (_direction == LEFT)
						{
							_yerina.x += cosf(PI / 180 * 45) * 30;
							//_yerina.y += -sinf(PI / 180 * 45) * 30;
						}
						else
						{
							_yerina.x += cosf(PI / 180 * 135) * 30;
							//_yerina.y += -sinf(PI / 180 * 135) * 30;
						}
					}
				}

			}
		}

		

		if (_eMG->getRibbon()->getFinalSkill()[FLOWERBEAM])
		{
			for (int i = 0; i < _eMG->getRibbon()->getSunFlowerBullet()->getFlower().size(); i++)
			{
				for (int j = 0; j < _eMG->getRibbon()->getSunFlowerBullet()->getFlower()[i].size(); j++)
				{
					if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getSunFlowerBullet()->getFlower()[i][j].rc) && !_yerina._isAttacted)
					{
						_state = BEATTACTED;
						_yerina._isAttacted = true;
						_yerina._dontMove = true;
						_yerina.curHp -= _eMG->getRibbon()->getSunFlowerBullet()->getFlower()[0][0].damage;
						SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


						if (_direction == LEFT)
						{
							_yerina.x += cosf(PI / 180 * 45) * 30;
							//_yerina.y += -sinf(PI / 180 * 45) * 30;
						}
						else
						{
							_yerina.x += cosf(PI / 180 * 135) * 30;
							//_yerina.y += -sinf(PI / 180 * 135) * 30;
						}
					}
				}

			}
		}

		
		
		if (_eMG->getRibbon()->getFinalSkill()[SPIDERWEB])
		{
			for (int i = 0; i < _eMG->getRibbon()->getSpiderWebBullet()->getSpiderWeb().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getRibbon()->getSpiderWebBullet()->getSpiderWeb()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getRibbon()->getSpiderWebBullet()->getSpiderWeb()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}
		

	}
	else if (SAVEDATA->getCurrentStage() == FINALBOSS)
	{
		// 유도별
		RECT _rct;
		if (_eMG->getFinalBoss()->getFinalSkill()[GUIDEDMISSILE])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalGuidedBullet()->getGuidedBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalGuidedBullet()->getGuidedBullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalGuidedBullet()->getGuidedBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}
		
		//토네이도
		if (_eMG->getFinalBoss()->getFinalSkill()[TORNADO])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalTornadoBullet()->getTornadoBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalTornadoBullet()->getTornadoBullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalTornadoBullet()->getTornadoBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}

		//스네이크
		if (_eMG->getFinalBoss()->getFinalSkill()[SNAKE])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalSnakeBullet()->getSnakebullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalSnakeBullet()->getSnakebullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalSnakeBullet()->getSnakebullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}

		//다각형
		if (_eMG->getFinalBoss()->getFinalSkill()[POLYGON])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalPolygonBullet()->getPolygonBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalPolygonBullet()->getPolygonBullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalPolygonBullet()->getPolygonBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}


		//문어
		if (_eMG->getFinalBoss()->getFinalSkill()[OCTOPUS])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalOctopusBullet()->getOctopusBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalOctopusBullet()->getOctopusBullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalOctopusBullet()->getOctopusBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}

		//볼
		if (_eMG->getFinalBoss()->getFinalSkill()[BALL])
		{
			for (int i = 0; i < _eMG->getFinalBoss()->getFinalBallBullet()->getBallBullet().size(); i++)
			{
				if (IntersectRect(&_rct, &_yerina.beAttRc, &_eMG->getFinalBoss()->getFinalBallBullet()->getBallBullet()[i].rc) && !_yerina._isAttacted)
				{
					_state = BEATTACTED;
					_yerina._isAttacted = true;
					_yerina._dontMove = true;
					_yerina.curHp -= _eMG->getFinalBoss()->getFinalBallBullet()->getBallBullet()[0].damage;
					SOUNDMANAGER->play("데미지", SAVEDATA->getEffSound());


					if (_direction == LEFT)
					{
						_yerina.x += cosf(PI / 180 * 45) * 30;
						//_yerina.y += -sinf(PI / 180 * 45) * 30;
					}
					else
					{
						_yerina.x += cosf(PI / 180 * 135) * 30;
						//_yerina.y += -sinf(PI / 180 * 135) * 30;
					}
				}
			}
		}



	}


}
void yerinaT::animation()
{
	if (_direction == LEFT)
	{
		if (_count % 6 == 0)
		{
			_bodyIndex++;
			if (_bodyIndex > _yerinaImg[_state]->getMaxFrameX())
			{
				_bodyIndex = 0;
				if (_state == JUMP || _state == SLIDE)
					_bodyIndex = _yerinaImg[_state]->getMaxFrameX();
				if (_state == BOMB)
				{
					_state = IDLE;
					_bodyIndex = 0;
				}

			}
			if (_state == BOMB)
				if (_bodyIndex == 4)
					_carrot->fire(_yerina.x, _yerina.y, LEFT);
		}
		_yerinaImg[_state]->setFrameX(_bodyIndex);
		_yerinaImg[_state]->setFrameY(0);

	}
	else if (_direction == RIGHT)
	{
		if (_count % 6 == 0)
		{
			_bodyIndex--;
			if (_bodyIndex < 0)
			{
				_bodyIndex = _yerinaImg[_state]->getMaxFrameX();
				if (_state == JUMP || _state == SLIDE)
					_bodyIndex = 0;
				if (_state == BOMB)
				{
					_state = IDLE;
					_bodyIndex = 6;
				}
			}
			if (_state == BOMB)
				if (_bodyIndex == 5)
					_carrot->fire(_yerina.x, _yerina.y, RIGHT);
		}
		_yerinaImg[_state]->setFrameX(_bodyIndex);
		_yerinaImg[_state]->setFrameY(1);

	}
	

}

void yerinaT::commandAnimation()
{
	if (_direction == LEFT)
	{
		if (_state == ATTACT5 || _state == DOWNATTACT)
		{
			if (_count % 2 == 0)
			{
				_bodyIndex++;
				_hammerIndex++;
				if (_bodyIndex > _yerinaImg[_state]->getMaxFrameX())
					_bodyIndex = 2;

				if (_hammerIndex > _yerinaHammer[_hammer]->getMaxFrameX())
				{
					_hammerIndex = 0;
					SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());
				}
			}
		}
		else
		{
			if (_count % 4 == 0)
			{
				_bodyIndex++;
				_hammerIndex++;

				if (_bodyIndex > _yerinaImg[_state]->getMaxFrameX())
					_bodyIndex = _yerinaImg[_state]->getMaxFrameX();
				if (_hammerIndex > _yerinaHammer[_hammer]->getMaxFrameX())
					_hammerIndex = _yerinaHammer[_hammer]->getMaxFrameX();
			}
		}
		_yerinaImg[_state]->setFrameX(_bodyIndex);
		_yerinaImg[_state]->setFrameY(0);
		_yerinaHammer[_hammer]->setFrameX(_hammerIndex);
		_yerinaHammer[_hammer]->setFrameY(0);

	}
	else
	{
		if (_state == ATTACT5 || _state == DOWNATTACT)
		{
			if (_count % 2 == 0)
			{
				_bodyIndex--;
				_hammerIndex--;
				if (_bodyIndex < 0)
					_bodyIndex = _yerinaImg[_state]->getMaxFrameX() - 2;

				if (_hammerIndex < 0)
				{
					_hammerIndex = _yerinaHammer[_hammer]->getMaxFrameX();
					SOUNDMANAGER->play("해머", SAVEDATA->getEffSound());
				}
			}
		}
		else
		{

			if (_count % 4 == 0)
			{
				_bodyIndex--;
				_hammerIndex--;
				if (_bodyIndex < 0)
					_bodyIndex = 0;
				if (_hammerIndex < 0)
					_hammerIndex = 0;
			}
		}
		_yerinaImg[_state]->setFrameX(_bodyIndex);
		_yerinaImg[_state]->setFrameY(1);
		_yerinaHammer[_hammer]->setFrameX(_hammerIndex);
		_yerinaHammer[_hammer]->setFrameY(1);
	}


}

void yerinaT::springCollision(stage_MAPt* _stageMap)
{
	RECT _rct;
	if (IntersectRect(&_rct, &_stageMap->getSpringRc(), &_yerina.realSizeRc) && _state == FALL)
	{
		isSpringActive = true;
	}
	else
	{
		isSpringActive = false;
		_yerina._isSpringJump = false;
		_stageMap->setSpringIndex(0);
	}

	if (isSpringActive)
	{
		
		for (int j = 0; j < 50; j++)
		{
			COLORREF color = GetPixel(_stageMap->getSpringImg()->getMemDC(), _stageMap->getSpringImg()->getFrameWidth()/2 + _stageMap->getSpringIndex() * _stageMap->getSpringImg()->getFrameWidth(), j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{

				_yerina.y = _stageMap->getSpringRc().top + j - 82;
				_yerina.rc = RectMakeCenter(_yerina.x + _yerina.speed, _yerina.y, 200, 200);

			}
		}

		if (_count % 3 == 0)
		{
			_stageMap->setSpringIndex(_stageMap->getSpringIndex() + 1);
			if (_stageMap->getSpringIndex() > _stageMap->getSpringImg()->getMaxFrameX())
			{
				_stageMap->setSpringIndex(0);
				isSpringActive = false;
				_yerina._isSpringJump = true;
				_yerina.y -= 25;

			}
		}

	}


	if (_yerina._isSpringJump)
	{
		if (_direction == LEFT)
		{
			_bodyIndex = 0;
		}
		else if (_direction == RIGHT)
		{
			_bodyIndex = 5;
		}
		_state = SPRINGJUMP;
		_yerina.jumpSpeed = YERINAJUMPSPEED;
		_yerina.jumpSpeed += 33.f;
		_yerina.gravity = 0;
	}

}

void yerinaT::debug()
{
	//Rectangle(getMemDC(), CAMERAMANAGER->getVCam("플레이어카메라")[0].rc);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _yerina.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);		
		//Rectangle(getMemDC(), _yerina.realSizeRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.realSizeRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.realSizeRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.realSizeRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
		//Rectangle(getMemDC(), _yerina.tileCollRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.tileCollRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.tileCollRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.tileCollRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	}

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		for (int i = 0; i < CHECKTILEINDEX; ++i)
		{
			//Rectangle(getMemDC(), _stage1_map->getTiles()[_collisionTileIndex[i]].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _stage1_map->getTiles()[_collisionTileIndex[i]].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _stage1_map->getTiles()[_collisionTileIndex[i]].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _stage1_map->getTiles()[_collisionTileIndex[i]].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
		}

	}

	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		Rectangle(getMemDC(), _yerina.bottomTileCheckRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.bottomTileCheckRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.bottomTileCheckRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.bottomTileCheckRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
		//Rectangle(getMemDC(), _yerina.pixelRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.pixelRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.pixelRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.pixelRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
		//Rectangle(getMemDC(), _yerina.LRColliRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.LRColliRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.LRColliRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.LRColliRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);


		//_yerina.bottomTileCheckRc
	}

	if (KEYMANAGER->isToggleKey(VK_F7))
	{
		Rectangle(getMemDC(), _yerina.topTileCheckRc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.topTileCheckRc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _yerina.topTileCheckRc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _yerina.topTileCheckRc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

	}



}


