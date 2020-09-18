#include "stdafx.h"
#include "ribbonT.h"

//if (pos.x < _player->getX() - 70 || pos.x > _player->getX() - 30 || pos.y < _player->getY() - 70 || pos.y > _player->getY() - 30)
//{
//	angle = getAngle(pos.x, pos.y, _player->getX() - 50, _player->getY() - 50);

//	pos.x += cosf(angle)*speed;
//	pos.y += -sinf(angle)*speed;
//}

HRESULT ribbonT::init()
{
	ZeroMemory(&_ribbon, sizeof(RIBBONINF));

	//_ribbon.x = 500;
	//_ribbon.y = 500;
	_ribbon.angle = PI / 4;
	_ribbon.speed = 7.f;
	_ribbon.state = R_MOVE;
	_ribbon.maxMp = 100;
	_ribbon.curMp = 75;
	_ribbon.charge = 0;
	_ribbon.isCharging = false;
	_ribbon.skillPower = 30;

	_ribbon.image[R_MOVE] = IMAGEMANAGER->addFrameImage("리본idle", "resource/player/리본IDLE.bmp", 384, 192, 4, 2);
	_ribbon.image[R_ATTACT1] = IMAGEMANAGER->addFrameImage("리본attact1", "resource/player/리본ATTACT1.bmp", 384, 192, 4, 2);
	_ribbon.image[R_ATTACT2] = IMAGEMANAGER->addFrameImage("리본attact2", "resource/player/리본ATTACT2.bmp", 480, 192, 5, 2);

	GDIPLUS->addFrameImage("블루총알충전", "resource/bullet/블루총알충전.png", 0, 0, 10, 1);

	IMAGEMANAGER->addFrameImage("리본똥꼬", "resource/player/리본똥꼬.bmp", 443, 50, 8, 1);

	for (int i = 0; i < RIBBONAFTERIMAGES; i++)
	{
		_ribbon.afterImageRc[i].radius = 10;
		_ribbon.afterImageRc[i].speed = 5.5f;// -0.3f*i;
		_ribbon.afterImageRc[i].angle = (i == 0) ? RND->getFloat(2 * PI) : _ribbon.afterImageRc[i - 1].angle;
		_ribbon.afterImageRc[i].x = _ribbon.x;
		_ribbon.afterImageRc[i].y = _ribbon.y;
		_ribbon.afterImageRc[i].alpha = 255 - 25 * i;
		
		_ribbon.afterImageRc[i].isActive = false;
		_ribbonBackIndex[i] = i;
	}

	_index = _count = _bulletIndex = _chargingIndex =0;

	_bbyororong = new ribbonBlueBullet;
	_bbyororong->init();

	return S_OK;
}

void ribbonT::release()
{
}

void ribbonT::update(float yerinaX, float yerinaY, float yerinaSpeed , DIRECTION _dir)
{
	_count++;

	_bbyororong->update();

	this->move(yerinaX, yerinaY, yerinaSpeed, _dir);
	this->animation(_dir);
	this->makingAfterImageRc();
	this->manaCharge();
}

void ribbonT::render()
{

	//Rectangle(getMemDC(), _ribbon.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _ribbon.rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);


	for (int i = 0; i < RIBBONAFTERIMAGES; i++)
	{
		if(_ribbon.afterImageRc[i].isActive)
			IMAGEMANAGER->frameRender("리본똥꼬", getMemDC(), _ribbon.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 20, _ribbon.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top  -25, _ribbonBackIndex[i], 0);

		//Rectangle(getMemDC(), _ribbon.afterImageRc[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.afterImageRc[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _ribbon.afterImageRc[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.afterImageRc[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	}

	_ribbon.image[_ribbon.state]->frameRender(getMemDC(), _ribbon.rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _index, _ribbon.image[_ribbon.state]->getFrameY());

	// 따라가는 작은 블루 뷸렛
	for (int i = 0; i < _bbyororong->getSmallBullet().size(); i++)
	{
		//Rectangle(getMemDC(), _blueBullet->getSmallBullet()[i].rc);
		//_ribbonBoss->setBulletIndex(RND->getInt(3));

		int randNum = RND->getInt(3);
		_bbyororong->getSmallBullet()[i]._bulletImg[randNum]->gdiRender(getMemDC(), _bbyororong->getSmallBullet()[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _bbyororong->getSmallBullet()[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

	}
	// 충돌을 일으키는 큰 블루 뷸렛
	for (int i = 0; i < _bbyororong->getBigBullet().size(); i++)
	{
		_bbyororong->getBigBullet()[i]._bulletImg[0]->gdiFrameRender(getMemDC(), _bbyororong->getBigBullet()[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _bbyororong->getBigBullet()[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, 6,0);// _bbyororong->getBigBullet()[i]._bulletImg[0]->getFrameX(), _bbyororong->getBigBullet()[i]._bulletImg[0]->getFrameY());
	}

	if(_ribbon.isCharging)
	 	GDIPLUS->gdiFrameRender("블루총알충전",getMemDC(), _ribbon.x - 30 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _ribbon.y - 30 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _chargingIndex, 0);



}

void ribbonT::move(float yerinaX, float yerinaY, float yerinaSpeed, DIRECTION _dir)
{
	if (_dir == LEFT)
	{
		if (_ribbon.x > yerinaX + 80 || _ribbon.x < yerinaX + 40 || _ribbon.y < yerinaY - 100 || _ribbon.y > yerinaY - 60)
		{
			_ribbon.angle = getAngle(_ribbon.x, _ribbon.y, yerinaX + 60, yerinaY - 80);
			float distance = getDistance(_ribbon.x, _ribbon.y, yerinaX + 60, yerinaY - 80);

			if (distance > 100)
				_ribbon.speed = 19.f;
			else
				_ribbon.speed = yerinaSpeed;

			_ribbon.x += cosf(_ribbon.angle)*_ribbon.speed;
			_ribbon.y += -sinf(_ribbon.angle)*_ribbon.speed;
			_ribbon.rc = RectMakeCenter(_ribbon.x, _ribbon.y, 40, 40);
		}
	}
	else 
	{
		if (_ribbon.x < yerinaX - 120 || _ribbon.x > yerinaX - 80 || _ribbon.y < yerinaY - 100 || _ribbon.y > yerinaY - 60)
		{
			_ribbon.angle = getAngle(_ribbon.x, _ribbon.y, yerinaX - 100, yerinaY - 80);
			float distance = getDistance(_ribbon.x, _ribbon.y, yerinaX - 100, yerinaY - 80);

			if (distance > 100)
				_ribbon.speed = 19.f;
			else
				_ribbon.speed = yerinaSpeed;

			_ribbon.x += cosf(_ribbon.angle)*_ribbon.speed;
			_ribbon.y += -sinf(_ribbon.angle)*_ribbon.speed;
			_ribbon.rc = RectMakeCenter(_ribbon.x, _ribbon.y, 40, 40);
		}
	}

}

void ribbonT::animation(DIRECTION _dir)
{
	if (_dir == LEFT)
	{
		if (_count % 6 == 0)
		{
			_index++;
			if (_index > _ribbon.image[_ribbon.state]->getMaxFrameX())
				_index = 0;

		}
		_ribbon.image[_ribbon.state]->setFrameY(0);
	}
	else
	{
		if (_count % 6 == 0)
		{
			_index--;
			if (_index < 0)
				_index = _ribbon.image[_ribbon.state]->getMaxFrameX();

		}
		_ribbon.image[_ribbon.state]->setFrameY(1);

	}

	if (_count % 5 == 0)
	{
		for (int i = 0; i < RIBBONAFTERIMAGES; ++i)
		{
			_ribbonBackIndex[i]++;
			if (_ribbonBackIndex[i] > 8)
				_ribbonBackIndex[i] = 0;
		}
		
	}

	if (_count % 5 == 0)
	{
		_bulletIndex++;
		if (_bulletIndex > 7)
			_bulletIndex = 0;

	}
	if (_ribbon.isCharging)
	{
		if (_count % 4 == 0)
		{
			_chargingIndex++;
			if (_chargingIndex > 10)
				_chargingIndex = 0;
		}

	}

}

void ribbonT::makingAfterImageRc()
{
	for (int i = 0; i < RIBBONAFTERIMAGES; i++)
	{

		if (i == 0) //머리냐?
		{

			_ribbon.afterImageRc[i].x = _ribbon.x + 30;
			_ribbon.afterImageRc[i].y = _ribbon.y + 30; // -30;


		}
		else//구슬 첫번째를 따라오는 몸통들 (지렁이 따라오는 핵심)
		{
			float distance = getDistance(_ribbon.afterImageRc[i].x, _ribbon.afterImageRc[i].y, _ribbon.afterImageRc[i - 1].x, _ribbon.afterImageRc[i - 1].y);

			if (distance > 30)// || distance < -5)
			{
				_ribbon.afterImageRc[i].angle = getAngle(_ribbon.afterImageRc[i].x, _ribbon.afterImageRc[i].y, _ribbon.afterImageRc[i - 1].x, _ribbon.afterImageRc[i - 1].y);
				/*_yerina.afterImageRc[i].x = _yerina.afterImageRc[i - 1].x - cosf(_yerina.afterImageRc[i].angle) * (_yerina.afterImageRc[i].radius * 2);
				_yerina.afterImageRc[i].y = _yerina.afterImageRc[i - 1].y - (-sinf(_yerina.afterImageRc[i].angle)) * (_yerina.afterImageRc[i].radius * 2);*/
				_ribbon.afterImageRc[i].x = _ribbon.afterImageRc[i - 1].x - cosf(_ribbon.afterImageRc[i].angle) * 30;
				_ribbon.afterImageRc[i].y = _ribbon.afterImageRc[i - 1].y - (-sinf(_ribbon.afterImageRc[i].angle)) * 30;

				/*_yerina.afterImageRc[i].x = _yerina.x;
				_yerina.afterImageRc[i].y = _yerina.y;*/
				//_yerina.afterImageRc[i].speed = sinf(_yerina.afterImageRc[i].angle)*_yerina.jumpSpeed;// +_yerina.gravity;
			}


			_ribbon.afterImageRc[i].x += cosf(_ribbon.afterImageRc[i].angle) * _ribbon.afterImageRc[i].speed;
			_ribbon.afterImageRc[i].y += -sinf(_ribbon.afterImageRc[i].angle) * _ribbon.afterImageRc[i].speed;


			//else
			//	_yerina.afterImageRc[i].isActive = true;

		}
		//if (_ribbon.x > yerinaX + 80 || _ribbon.x < yerinaX + 40 || _ribbon.y < yerinaY - 100 || _ribbon.y > yerinaY - 60)

		if (_ribbon.afterImageRc[i].x > _ribbon.x + 70 || _ribbon.afterImageRc[i].x < _ribbon.x -10)
			_ribbon.afterImageRc[i].isActive = true;
		else
			_ribbon.afterImageRc[i].isActive = false;

		//if(_yerina.afterImageRc[i].isActive)
		_ribbon.afterImageRc[i].rc = RectMakeCenter(_ribbon.afterImageRc[i].x, _ribbon.afterImageRc[i].y, _ribbon.afterImageRc[i].radius, _ribbon.afterImageRc[i].radius);
	}


}

void ribbonT::fire(float x, float y, DIRECTION _dir)
{

	_bbyororong->fire(x, y, _dir);

}

void ribbonT::manaCharge()
{

	if (_count % 10 == 0)
		if (_ribbon.curMp <= _ribbon.maxMp - 1)
			_ribbon.curMp++;
}
