#include "stdafx.h"
#include "rabiribiBullet.h"
#include "yerinaT.h"

//=============
//	에리나 당근
//=============
HRESULT yerinaCarrot::init()
{
	IMAGEMANAGER->addImage("당근", "resource/player/CARROT.bmp", 30, 28, true, MAGENTA);



	return S_OK;
}

void yerinaCarrot::release()
{
}

void yerinaCarrot::update()
{
	

	this->move();

}

void yerinaCarrot::render()
{
	for (int fireCarrot = 0; fireCarrot < _vCarrot.size(); ++fireCarrot)
	{
		if (_vCarrot[fireCarrot].isfire)
		{

			if(_vCarrot[fireCarrot].angleY > PI/2)
				_vCarrot[fireCarrot]._bulletImg->rotateRender(getMemDC(), _vCarrot[fireCarrot].rc.left + _vCarrot[fireCarrot].radius / 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vCarrot[fireCarrot].rc.top + _vCarrot[fireCarrot].radius / 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _vCarrot[fireCarrot].rotateRate);
			else
				_vCarrot[fireCarrot]._bulletImg->rotateRender(getMemDC(), _vCarrot[fireCarrot].rc.left + _vCarrot[fireCarrot].radius / 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _vCarrot[fireCarrot].rc.top + _vCarrot[fireCarrot].radius / 2 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, -_vCarrot[fireCarrot].rotateRate);

		}
	}
}



void yerinaCarrot::fire(float x, float y, int dir)
{

	if (_vCarrot.size() + 1 > CARROT) return;

	RB_BULLET _carrot;
	ZeroMemory(&_carrot, sizeof(RB_BULLET));
	_carrot.isfire = true;
	_carrot.x = _carrot.fireX = x;
	_carrot.y = _carrot.fireY = y;
	_carrot.speed = 5.f;
	_carrot.radius = 25;
	_carrot._bulletImg = IMAGEMANAGER->findImage("당근");

	if (dir == 0)
	{
		_carrot.angleY = PI / 180 * 100;
	}
	else if (dir == 1)
	{
		_carrot.angleY = PI / 180 * 80;
	}

	_vCarrot.push_back(_carrot);
}

void yerinaCarrot::move()
{

	for (int fireCarrot = 0; fireCarrot < _vCarrot.size(); ++fireCarrot)
	{
		if (_vCarrot[fireCarrot].isfire)
		{
			_vCarrot[fireCarrot].rotateRate += 0.05f;

			_vCarrot[fireCarrot].count++;
			_vCarrot[fireCarrot].gravity += 0.2f;
			_vCarrot[fireCarrot].x += cosf(_vCarrot[fireCarrot].angleY)*_vCarrot[fireCarrot].speed;
			_vCarrot[fireCarrot].y += -sinf(_vCarrot[fireCarrot].angleY)*_vCarrot[fireCarrot].speed + _vCarrot[fireCarrot].gravity;
			_vCarrot[fireCarrot].rc = RectMakeCenter(_vCarrot[fireCarrot].x, _vCarrot[fireCarrot].y, _vCarrot[fireCarrot].radius, _vCarrot[fireCarrot].radius);

			if (_vCarrot[fireCarrot].count == 65)
			{
				_vCarrot.erase(_vCarrot.begin() + fireCarrot);
			}
		}

	}


}

//=============
//	리본 파랑 뾰로롱 총알
//=============

HRESULT ribbonBlueBullet::init()
{
	_image[0] = GDIPLUS->addImage("블루총알1", "resource/bullet/블루총알1.png");
	_image[1] = GDIPLUS->addImage("블루총알2", "resource/bullet/블루총알2.png");
	_image[2] = GDIPLUS->addImage("블루총알3", "resource/bullet/블루총알.png");

	_image_Big = GDIPLUS->addFrameImage("블루큰총알", "resource/bullet/블루큰총알.png", 1050, 200, 7, 2);

	count = 0;

	return S_OK;
}

void ribbonBlueBullet::release()
{
}

void ribbonBlueBullet::update()
{
	count++;
	this->move();
	this->animation();
}

void ribbonBlueBullet::render()
{
}

void ribbonBlueBullet::fire(float x, float y, int dir)
{
	//큰
	RB_BULLET_PNG bigBullet;
	if (dir == 0)
	{
		bigBullet.x = x - 50;
		bigBullet.angleX_first = PI;
		bigBullet.indexX = 0;
	}
	else
	{
		bigBullet.x = x ;
		bigBullet.angleX_first = 0;
		bigBullet.indexX = 6;
	}
	bigBullet.y = y;
	bigBullet.fireX = x;
	bigBullet.fireY = y;
	bigBullet.radius = 80;
	bigBullet.damage = 10;
	bigBullet.angleY_first = 0;
	bigBullet.isfire = true;
	bigBullet.speed = 8*2.5f;
	bigBullet._bulletImg[0] = GDIPLUS->findImage("블루큰총알");

	_vBigBullet.push_back(bigBullet);


	//_bigBullet._bulletImg[1] = GDIPLUS->findImage("블루큰총알");
	//_bigBullet._bulletImg[2] = GDIPLUS->findImage("블루큰총알");

	//작은
	for (int i = 0; i < BLUEBULLET; i++)
	{
		RB_BULLET_PNG _bullet;

		_bullet.x = x;
		_bullet.y = y;
		_bullet.fireX = x;
		_bullet.fireY = y;
		_bullet.radius = 10;
		
		if (dir == 0)
		{
			_bullet.angleX_first = PI;
			_bullet.angleY_first = PI - PI / 6;
		}
		else
		{
			_bullet.angleX_first = 0;
			_bullet.angleY_first = PI / 6;
		}
		_bullet.isfire = false;
		_bullet.speed = 8.f - 0.1f*i;
		_bullet.count = i;
		_bullet._bulletImg[0] = GDIPLUS->findImage("블루총알1");
		_bullet._bulletImg[1] = GDIPLUS->findImage("블루총알2");
		_bullet._bulletImg[2] = GDIPLUS->findImage("블루총알3");


		_vSmallBullet.push_back(_bullet);
	}


}

void ribbonBlueBullet::move()
{
	for (int i = 0; i < _vBigBullet.size(); ++i)
	{
		if (_vBigBullet[i].isfire)
		{
			_vBigBullet[i].x += cosf(_vBigBullet[i].angleX_first)*_vBigBullet[i].speed;
			_vBigBullet[i].rc = RectMakeCenter(_vBigBullet[i].x, _vBigBullet[i].y, _vBigBullet[i].radius, _vBigBullet[i].radius);

			if (_vBigBullet[i].x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left < -WINSIZEX || _vBigBullet[i].x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left > WINSIZEX * 2)
			{
				_vBigBullet.erase(_vBigBullet.begin() + i);
			}
		}
	}

	for (int i = 0; i < _vSmallBullet.size(); ++i)
	{
		if (!_vSmallBullet[i].isfire)
		{
			_vSmallBullet[i].isfire = true;

			break;
		}
	}
	for (int i = 0; i < _vSmallBullet.size(); ++i)
	{
		if (_vSmallBullet[i].isfire)
		{
			if (_vSmallBullet[i].count % 2 == 0)
				_vSmallBullet[i].angleY_first += 0.3f;
			else
				_vSmallBullet[i].angleY_first -= 0.3f;

			_vSmallBullet[i].x += cosf(_vSmallBullet[i].angleX_first)*_vSmallBullet[i].speed * 2.5f;
			_vSmallBullet[i].y += -sinf(_vSmallBullet[i].angleY_first)*_vSmallBullet[i].speed * 0.7f;

			_vSmallBullet[i].rc = RectMakeCenter(_vSmallBullet[i].x, _vSmallBullet[i].y , _vSmallBullet[i].radius, _vSmallBullet[i].radius);

			if (_vSmallBullet[i].x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left < - WINSIZEX || _vSmallBullet[i].x - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left > WINSIZEX * 2 )
			{
				_vSmallBullet.erase(_vSmallBullet.begin() + i);
			}


		}
	}

}

void ribbonBlueBullet::animation()
{
	for (int i = 0; i < _vBigBullet.size(); i++)
	{
		if (_vBigBullet[i].angleX_first == PI)
		{
			if (count % 6 == 0)
			{
				_vBigBullet[i].indexX++;
				if (_vBigBullet[i].indexX > 6)
				{
					_vBigBullet[i].indexX = 6;
				}
				_vBigBullet[i]._bulletImg[0]->setFrameX(_vBigBullet[i].indexX);
				_vBigBullet[i]._bulletImg[0]->setFrameY(0);
			}
		}
		else
		{
			if (count % 6 == 0)
			{
				_vBigBullet[i].indexX--;
				if (_vBigBullet[i].indexX < 0)
				{
					_vBigBullet[i].indexX = 0;
				}
				_vBigBullet[i]._bulletImg[0]->setFrameX(_vBigBullet[i].indexX);
				_vBigBullet[i]._bulletImg[0]->setFrameY(1);

			}
		}
	}
	
}


// 블루 레인~ ~~ //

HRESULT ribbonBlueRain::init()
{
	IMAGEMANAGER->addImage("블루레인총알알맹이", "resource/bullet/블루레인총알알맹이.bmp", 60, 57, true, MAGENTA);

	GDIPLUS->addImage("블루레인총알테두리", "resource/bullet/블루레인총알테두리.png");

	return S_OK;
}

void ribbonBlueRain::release()
{
}

void ribbonBlueRain::update()
{
	this->move();
}

void ribbonBlueRain::render()
{
}

void ribbonBlueRain::fire(float x, float y, int dir)
{

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			RB_BULLET_PNG blueRainBullet;

			//ZeroMemory(&blueRainBullet, sizeof(RB_BULLET_PNG));

			blueRainBullet.x = x;
			blueRainBullet.y = y;
			blueRainBullet.fireX = x;
			blueRainBullet.fireY = y;
			blueRainBullet.angleX_first = blueRainBullet.angleY_first = (PI / 180 * 20) + i * (PI / 180 * 20);
			blueRainBullet.radius = 20;
			blueRainBullet.gravity = 0;
			blueRainBullet.damage = 15;
			blueRainBullet.isfire = false;
			blueRainBullet.speed = 8.f ;
			//blueRainBullet._bulletImg[0] = GDIPLUS->findImage("블루레인총알알맹이");
			blueRainBullet._bulletImg[1] = GDIPLUS->findImage("블루레인총알테두리");
			blueRainBullet._image = IMAGEMANAGER->findImage("블루레인총알알맹이");
			//blueRainBullet.indexX = 6;

			_vBlueRain.push_back(blueRainBullet);
		}
		
	}
	
}

void ribbonBlueRain::move()
{
	for (int i = 0; i < _vBlueRain.size(); i++)
	{
		if (!_vBlueRain[i].isfire )//&& count % 2 == 0)
		{
			_vBlueRain[i].isfire = true;
			if (i % 9 == 0)
				SOUNDMANAGER->play("리본블루레인파이어", SAVEDATA->getEffSound());
			break;
		}
	}

	for (int i = 0; i < _vBlueRain.size(); i++)
	{
		if (_vBlueRain[i].isfire)
		{
			_vBlueRain[i].gravity += 0.4f;
			_vBlueRain[i].x += cosf(_vBlueRain[i].angleX_first)*_vBlueRain[i].speed * 1.7f;
			_vBlueRain[i].y += -sinf(_vBlueRain[i].angleY_first)*_vBlueRain[i].speed * 0.7 + _vBlueRain[i].gravity;


			_vBlueRain[i].rc = RectMakeCenter(_vBlueRain[i].x, _vBlueRain[i].y, _vBlueRain[i].radius, _vBlueRain[i].radius);

			if (_vBlueRain[i].y > WINSIZEY)
				_vBlueRain.erase(_vBlueRain.begin() + i);

		}
	}



}

// 옐로우 , 플라워 // 

HRESULT ribbonYellowBlue::init()
{
	count = yellowCount =  0;
	yellowsRotateRate = 0;
	yellowsLimitSpeed = 20.f;

	GDIPLUS->addImage("태양총알테두리", "resource/bullet/태양총알테두리2.png");
	IMAGEMANAGER->addImage("태양총알알맹이", "resource/bullet/태양총알알맹이.bmp", 40, 40,true, MAGENTA);

	GDIPLUS->addImage("플라워테두리", "resource/bullet/플라워테두리8.png");
	IMAGEMANAGER->addImage("플라워알맹이", "resource/bullet/플라워알맹이6.bmp", 60, 60, true, MAGENTA);

	for (int sun = 0; sun < SUN; sun++)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				RB_BULLET_PNG yellows;

				//ZeroMemory(&blueRainBullet, sizeof(RB_BULLET_PNG));
				yellows.angleX_first = PI / 3 * i + PI / 180 * 8 * j + PI / 180 * yellowsRotateRate;
				yellows.angleY_first = PI / 3 * i + PI / 180 * 8 * j + PI / 180 * yellowsRotateRate;

				yellows.x = 0;
				yellows.y = 0;
				yellows.fireX = 0;
				yellows.fireY = 0;
				yellows.radius = 20;
				yellows.gravity = 0;
				yellows.damage = 10;
				yellows.isfire = false;  // 동시에 발사
				yellows.speed = 0.5f;
				//yellows.indexX = j;
				yellows._bulletImg[0] = GDIPLUS->findImage("태양총알테두리");
				yellows._image = IMAGEMANAGER->findImage("태양총알알맹이");
				//blueRainBullet._bulletImg[0] = GDIPLUS->findImage("블루레인총알알맹이");
				//yellows._bulletImg[1] = GDIPLUS->findImage("블루레인총알테두리");
				//yellows._image = IMAGEMANAGER->findImage("블루레인총알알맹이");
				//blueRainBullet.indexX = 6;

				_vYellow.push_back(yellows);
			}
		}
		_vSun.push_back(_vYellow);
		_vYellow.clear();
		yellowsRotateRate += 20;
		if (yellowsRotateRate > 60)
			yellowsRotateRate = 0;
	}


	//플라워~~~~~~~~~~~~~~~~~~~//


	for (int leaf = 0; leaf < 3; leaf++)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				RB_BULLET_PNG flowerLeaf;

				flowerLeaf.angleX_first = flowerLeaf.angleY_first = (leaf * (2 * 6) + (i * 6) + j)*(PI / 180 * 10);

				flowerLeaf.angleX_second = 0;
				flowerLeaf.angleY_second = 0;
				flowerLeaf.x = 0;
				flowerLeaf.y = 0;
				flowerLeaf.fireX = 0;
				flowerLeaf.fireY = 0;
				flowerLeaf.radius = 20;
				flowerLeaf.gravity = 0;
				flowerLeaf.damage = 20;
				flowerLeaf.count = 0;
				flowerLeaf.isfire = false;  
				flowerLeaf.isActive_first = false;  // 동시에 발사
				flowerLeaf.isActive_second = false;  // 동시에 발사

				if (i == 0)
					flowerLeaf.speed = 0.2f + j * 0.2f;
				else
					flowerLeaf.speed = 1.2f - j * 0.2f;

				//yellows.indexX = j;
				flowerLeaf._bulletImg[0] = GDIPLUS->findImage("플라워테두리");
				flowerLeaf._image = IMAGEMANAGER->findImage("플라워알맹이");

				_vFlowerLeaf.push_back(flowerLeaf);
			}
		}
		_vFlower.push_back(_vFlowerLeaf);
		_vFlowerLeaf.clear();

	}

	return S_OK;
}

void ribbonYellowBlue::release()
{
}

void ribbonYellowBlue::update()
{

	count++;

	this->move_yellows();
	this->move_blues();
	this->move_flower();
	//this->animation();

	
}

void ribbonYellowBlue::fire_yellows(float x, float y, int order)
{
	for (int i = 0; i < _vSun[order].size(); i++)
	{
		_vSun[order][i].x = x - 10;// +i * 10 + cosf(_vSun[order][i].angleX) * 100;
		_vSun[order][i].y = y - 10; // -sinf(_vSun[order][i].angleY) * 100;
		_vSun[order][i].fireX = x;
		_vSun[order][i].fireY = y;
		_vSun[order][i].isfire = true;
	}
}

void ribbonYellowBlue::fire_blues(float x, float y, int dir)
{

}

void ribbonYellowBlue::fire_flower(float x, float y, int dir)
{
	for (int i = 0; i < _vFlower.size(); i++)
	{
		for (int j = 0; j < _vFlower[i].size(); j++)
		{
			_vFlower[i][j].x = x -20; 
			_vFlower[i][j].y = y -20; 
			_vFlower[i][j].fireX = x;
			_vFlower[i][j].fireY = y;
			_vFlower[i][j].isfire = true;
		}
	}
}

void ribbonYellowBlue::move_yellows()
{
	
	for (int j = 0; j < _vSun.size(); j++)
	{
		for (int i = 0; i < _vSun[j].size(); i++)
		{
			if (_vSun[j][i].isfire)
			{
				if (_vSun[j][i].speed < yellowsLimitSpeed)//&& _vSun[j][i].speed > 0.f)
				{
					_vSun[j][i].speed *= 1.05f;// +0.01f*(j*_vSun[j].size() + i);
				}
				else
				{
					_vSun[j][i].speed = 0.1f;
				}

				//_vSun[j][i].angleX += 0.02f;
				//_vSun[j][i].angleY += 0.02f;
				
				_vSun[j][i].x += cosf(_vSun[j][i].angleX_first)*_vSun[j][i].speed;
				_vSun[j][i].y += -sinf(_vSun[j][i].angleY_first)*_vSun[j][i].speed;
				_vSun[j][i].rc = RectMakeCenter(_vSun[j][i].x, _vSun[j][i].y, _vSun[j][i].radius, _vSun[j][i].radius);
			}


		}
	}



	for (int j = 0; j < _vSun.size(); j++)
	{
		for (int i = 0; i < _vSun[j].size(); i++)
		{
			if (_vSun[j][i].isfire)
			{
				if (_vSun[j][i].x < CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left
					|| _vSun[j][i].x > CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.right
					|| _vSun[j][i].y < CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top
					|| _vSun[j][i].y > CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.bottom)
				{
					_vSun[j][i].isfire = false;
					_vSun[j][i].speed = 0.5f;
					_vSun[j][i].x = -100.f;
					_vSun[j][i].y = -100.f;
					//_vSun[j][i].angleX = PI / 3 * i + PI / 180 * 5 * j + PI / 180 * yellowsRotateRate;
					//_vSun[j][i].angleY = PI / 3 * i + PI / 180 * 5 * j + PI / 180 * yellowsRotateRate;
				}
			}	
		}
	
	}

	

}

void ribbonYellowBlue::move_blues()
{
}

void ribbonYellowBlue::move_flower()
{
	for (int i = 0; i < _vFlower.size(); i++)
	{
		for (int j = 0; j < _vFlower[i].size(); j++)
		{

			if (_vFlower[i][j].isfire)
			{
				_vFlower[i][j].count++;
				_vFlower[i][j].speed *= 1.008f;
				if (_vFlower[i][j].speed > 10.f)
					_vFlower[i][j].speed = 10.f;

				_vFlower[i][j].angleX_first += 0.002f;
				_vFlower[i][j].angleY_first += 0.002f;

				if (_vFlower[i][j].count % 150 < 75)
				{
					_vFlower[i][j].x += cosf(_vFlower[i][j].angleX_first)*_vFlower[i][j].speed;
					_vFlower[i][j].y += -sinf(_vFlower[i][j].angleY_first)*_vFlower[i][j].speed;
				}
				else
				{
					_vFlower[i][j].x += cosf(_vFlower[i][j].angleX_first)* -_vFlower[i][j].speed;
					_vFlower[i][j].y += -sinf(_vFlower[i][j].angleY_first)* -_vFlower[i][j].speed;
				}
				_vFlower[i][j].rc = RectMakeCenter(_vFlower[i][j].x, _vFlower[i][j].y, _vFlower[i][j].radius, _vFlower[i][j].radius);

				if (_vFlower[i][j].count > 200)
				{
					_vFlower[i][j].isfire = false;
					_vFlower[i][j].isActive_first = true;
					_vFlower[i][j].angleX_second = _vFlower[i][j].angleY_second = RND->getFromFloatTo(PI / 4, PI * 3 / 4);
						break;
				}

			}
		}
	}


	for (int i = 0; i < _vFlower.size(); i++)
	{
		for (int j = 0; j < _vFlower[i].size(); j++)
		{
			if (_vFlower[i][j].isActive_first )
			{
				if (!_vFlower[i][j].isActive_second && count % 15 == 0)
				{
					
					_vFlower[i][j].isActive_second = true;
					SOUNDMANAGER->play("리본플라워총알파이어", SAVEDATA->getEffSound());

					break;
				}
			}
		}
	}

	for (int i = 0; i < _vFlower.size(); i++)
	{
		for (int j = 0; j < _vFlower[i].size(); j++)
		{
			if (_vFlower[i][j].isActive_second)// && count % 3 ==0)
			{
				//float angle = RND->getFromFloatTo(PI/6,PI*5/6);
				float speedX = 15;// RND->getFloat(10);
				float speedY = 15;// RND->getFloat(2);
				_vFlower[i][j].gravity += 0.4f;
				_vFlower[i][j].x += cosf(_vFlower[i][j].angleX_second)*speedX;
				_vFlower[i][j].y +=  -sinf(_vFlower[i][j].angleY_second)*speedY + _vFlower[i][j].gravity;
				

				_vFlower[i][j].rc = RectMakeCenter(_vFlower[i][j].x, _vFlower[i][j].y, _vFlower[i][j].radius, _vFlower[i][j].radius);

				if (_vFlower[i][j].y > CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.bottom + 300)
				{
					_vFlower[i][j].isActive_first = false;
					_vFlower[i][j].isActive_second = false;
					_vFlower[i][j].x = -100.f;
					_vFlower[i][j].y = -100.f;
					_vFlower[i][j].count = 0;
					_vFlower[i][j].angleX_first = _vFlower[i][j].angleY_first = (i* _vFlower[i].size() + j)*(PI / 180 * 10);
					_vFlower[i][j].gravity = 0;
					if (j < 6)
						_vFlower[i][j].speed = 0.2f + j * 0.2f;
					else
						_vFlower[i][j].speed = 1.2f - (j-6) * 0.2f;
				}

			}
		}
	}


}

HRESULT ribbonSpiderWeb::init()
{
	_image = IMAGEMANAGER->addFrameImage("스노우총알", "resource/bullet/스노우총알.bmp", 960, 20, 48, 1);
	_pngImage = GDIPLUS->addFrameImage("스노우총알P", "resource/bullet/스노우총알.png", 0, 0, 3, 1);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{

			RB_BULLET_PNG _spiderBullet;


			_spiderBullet.angleX_second = 0;
			_spiderBullet.angleY_second = 0;
			_spiderBullet.x = 0;
			_spiderBullet.y = 0;
			_spiderBullet.fireX = 0;
			_spiderBullet.fireY = 0;
			_spiderBullet.indexX = 0;
			_spiderBullet.indexY = 0;
			//if (j < 6)
			//	_spiderBullet.speed = 5.f + 1.f*j;
			//else
			//	_spiderBullet.speed = 10.f - 1.f*(j - 6);
			_spiderBullet.speed = 7.f;
			_spiderBullet.radius = 20;
			_spiderBullet.gravity = 0;
			_spiderBullet.damage = 10;
			_spiderBullet.count = 0;
			_spiderBullet.isfire = false;
			_spiderBullet.isActive_first = false;  // 동시에 발사
			_spiderBullet.isActive_second = false;  // 동시에 발사
			_spiderBullet._image = IMAGEMANAGER->findImage("스노우총알");
			_spiderBullet._bulletImg[0] = GDIPLUS->findImage("스노우총알P");

			_vSpiderWebBullet.push_back(_spiderBullet);

		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = 0;

	return S_OK;
}

void ribbonSpiderWeb::release()
{
}

void ribbonSpiderWeb::update()
{
	count++;
	this->move();
	this->animation();

}

void ribbonSpiderWeb::fire(float x, float y, int order)
{
	for (int i = 0; i < _vSpiderWebBullet.size(); i++)
	{
		
		_vSpiderWebBullet[i].x = -20 + x + cosf(PI / 180 * 60 * i) * 100;
		_vSpiderWebBullet[i].y = -20 + y + sinf(PI / 180 * 60 * i) * 100;
		_vSpiderWebBullet[i].angleX_first = (i)*(PI / 180 * 5.f);
		_vSpiderWebBullet[i].angleY_first = (i)*(PI / 180 * 5.f);
		_vSpiderWebBullet[i].fireX = -20 + x + cosf(PI / 180 * 60 * i) * 100;
		_vSpiderWebBullet[i].fireY = -20 + y + sinf(PI / 180 * 60 * i) * 100;
		_vSpiderWebBullet[i].speed = 7.f;

		_vSpiderWebBullet[i].isfire = true;
		
	}
	
}

void ribbonSpiderWeb::move()
{
	for (int j = 0; j < 6; j++)
	{
		for (int i = j; i < _vSpiderWebBullet.size(); i+=6)
		{
			if (_vSpiderWebBullet[i].isfire )
			{
				_vSpiderWebBullet[i].x += cosf(_vSpiderWebBullet[i].angleX_first)*_vSpiderWebBullet[i].speed;
				_vSpiderWebBullet[i].y += -sinf(_vSpiderWebBullet[i].angleY_first)*_vSpiderWebBullet[i].speed;

				_vSpiderWebBullet[i].count++;

				if (_vSpiderWebBullet[i].count == 84)
				{
					_vSpiderWebBullet[i].speed = 0.f;
				}
				else if(_vSpiderWebBullet[i].count > 150)
				{
					_vSpiderWebBullet[i].isActive_first = true;
					_vSpiderWebBullet[i].isfire = false;
					_vSpiderWebBullet[i].count = 0;
					SOUNDMANAGER->play("리본거미줄파이어", SAVEDATA->getEffSound());

				}

				_vSpiderWebBullet[i].rc = RectMakeCenter(_vSpiderWebBullet[i].x, _vSpiderWebBullet[i].y, _vSpiderWebBullet[i].radius, _vSpiderWebBullet[i].radius);
			}
		
		}

	}

	//for (int j = 0; j < 24; j++)
	{
		for (int i = 0; i < _vSpiderWebBullet.size(); i += 1)
		{
			if (_vSpiderWebBullet[i].isActive_first)
			{

				_vSpiderWebBullet[i].speed = 21.f;

				_vSpiderWebBullet[i].x += cosf(_vSpiderWebBullet[i].angleX_first)* (-_vSpiderWebBullet[i].speed);
				_vSpiderWebBullet[i].y += -sinf(_vSpiderWebBullet[i].angleY_first)* (-_vSpiderWebBullet[i].speed);
				_vSpiderWebBullet[i].rc = RectMakeCenter(_vSpiderWebBullet[i].x, _vSpiderWebBullet[i].y, _vSpiderWebBullet[i].radius, _vSpiderWebBullet[i].radius);

				_vSpiderWebBullet[i].count++;

				if (_vSpiderWebBullet[i].count > 28)
				{
					_vSpiderWebBullet[i].isActive_second = true;
					_vSpiderWebBullet[i].isActive_first = false;
					_vSpiderWebBullet[i].speed = 1.f;
					_vSpiderWebBullet[i].x = (i / 12) * 200 +300 ;
					_vSpiderWebBullet[i].y = 200 + (i / 12) * 100;
					_vSpiderWebBullet[i].angleX_second = PI / 180 * 30 * (i % 12);
					_vSpiderWebBullet[i].angleY_second = PI / 180 * 30 * (i % 12);
					_vSpiderWebBullet[i].count = 0;

				}
			}
		}
	}


	for (int j = 0; j < 6; j++)
	{
		for (int i = j; i < _vSpiderWebBullet.size(); i += 6)
		{
			if (_vSpiderWebBullet[i].isActive_second)
			{

				_vSpiderWebBullet[i].speed *= 1.005f;
				_vSpiderWebBullet[i].angleX_second += 0.03f;
				_vSpiderWebBullet[i].angleY_second += 0.02f;

				_vSpiderWebBullet[i].x += cosf(_vSpiderWebBullet[i].angleX_second)* _vSpiderWebBullet[i].speed * 4;
				_vSpiderWebBullet[i].y += -sinf(_vSpiderWebBullet[i].angleY_second)* _vSpiderWebBullet[i].speed * 4;
				_vSpiderWebBullet[i].rc = RectMakeCenter(_vSpiderWebBullet[i].x, _vSpiderWebBullet[i].y, _vSpiderWebBullet[i].radius, _vSpiderWebBullet[i].radius);

				_vSpiderWebBullet[i].count++;

				if (_vSpiderWebBullet[i].count == 400)
				{
					_vSpiderWebBullet[i].isActive_second = false;
					_vSpiderWebBullet[i].rc = RectMakeCenter(-100, -100, 20, 20);
					_vSpiderWebBullet[i].count = 0;
				}


				/*if (_vSpiderWebBullet[i].x < CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left
					|| _vSpiderWebBullet[i].x > CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.right
					|| _vSpiderWebBullet[i].y < CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top
					|| _vSpiderWebBullet[i].y > CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.bottom)
				{
					_vSpiderWebBullet[i].isActive_second = false;
				}*/
			}
		}
	}

}

void ribbonSpiderWeb::animation()
{
	//for (int i = 0; i < _vSpiderWebBullet.size(); i++)
	//{
	//	//if (count % 3 == 0)
	//	{
	//		_vSpiderWebBullet[i].indexX++;
	//		if (_vSpiderWebBullet[i].indexX > _image->getMaxFrameX())
	//		{
	//			_vSpiderWebBullet[i].indexX = 0;
	//		}
	//		//_vSpiderWebBullet[i].indexY = 0;

	//		_vSpiderWebBullet[i]._image->setFrameX(_vSpiderWebBullet[i].indexX);
	//		_vSpiderWebBullet[i]._image->setFrameY(0);
	//	}
	//}

	for (int i = 0; i < _vSpiderWebBullet.size(); i++)
	{
		//if (count % 2 == 0)
		{
			_vSpiderWebBullet[i].indexX++;
			if (_vSpiderWebBullet[i].indexX > 3)
			{
				_vSpiderWebBullet[i].indexX = 0;
			}
			//_vSpiderWebBullet[i].indexY = 0;

			_vSpiderWebBullet[i]._bulletImg[0]->setFrameX(_vSpiderWebBullet[i].indexX);
			_vSpiderWebBullet[i]._bulletImg[0]->setFrameY(0);
		}
	}

}



//void ribbonYellowBlue::animation()
//{
//	if (count % 5 == 0)
//	{
//		for (int j = 0; j < _vSun.size(); j++)
//		{
//			for (int i = 0; i < _vSun[j].size(); i++)
//			{
//				_vSun[j][i].indexX++;
//				if (_vSun[j][i].indexX > _vSun[j][i]._image->getMaxFrameX())
//					_vSun[j][i].indexX = 0;
//
//
//			}
//		}
//	}
//}



//=============
//	보스 총알
//=============
HRESULT guided_bullet::init()
{

	GDIPLUS->addImage("유도탄총알1", "resource/bullet/유도탄총알1.png");
	GDIPLUS->addImage("유도탄총알2", "resource/bullet/유도탄총알2.png");
	GDIPLUS->addImage("유도탄총알3", "resource/bullet/유도탄총알3.png");


	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 60; j++)
		{

			RB_BULLET_PNG _guidedBullet;

			ZeroMemory(&_guidedBullet, sizeof(RB_BULLET_PNG));

			_guidedBullet.angleX_second = 0;
			_guidedBullet.angleY_second = 0;
			_guidedBullet.x = 0;
			_guidedBullet.y = 0;
			_guidedBullet.fireX = 0;
			_guidedBullet.fireY = 0;
			_guidedBullet.indexX = 0;
			_guidedBullet.indexY = 0;
			//if (j < 6)
			//	_spiderBullet.speed = 5.f + 1.f*j;
			//else
			//	_spiderBullet.speed = 10.f - 1.f*(j - 6);
			_guidedBullet.speed = 7.f;
			_guidedBullet.radius = 20;
			_guidedBullet.gravity = 0;
			_guidedBullet.count = 0;
			_guidedBullet.damage = 15;
			_guidedBullet.isfire = false;
			_guidedBullet.isActive_first = false;  // 동시에 발사
			_guidedBullet.isActive_second = false;  // 동시에 발사
			//_guidedBullet._image = IMAGEMANAGER->findImage("스노우총알");
			_guidedBullet._bulletImg[0] = GDIPLUS->findImage("유도탄총알1");
			_guidedBullet._bulletImg[1] = GDIPLUS->findImage("유도탄총알2");
			_guidedBullet._bulletImg[2] = GDIPLUS->findImage("유도탄총알3");

			_vGuidedBullet.push_back(_guidedBullet);

		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = 0;

	return S_OK;
	return S_OK;
}

void guided_bullet::release()
{
}

void guided_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void guided_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 10; i++)
	{
		int randSiteX = RND->getFromIntTo(100, 1100);
		int randSiteY = RND->getFromIntTo(100, 600);

		for (int j = 0; j < 6; j++)
		{
			_vGuidedBullet[i * 6 + j].x = randSiteX;
			_vGuidedBullet[i * 6 + j].y = randSiteY;
			_vGuidedBullet[i * 6 + j].angleX_first = (i)*(PI / 180 * 60);
			_vGuidedBullet[i * 6 + j].angleY_first = (i)*(PI / 180 * 60);
			_vGuidedBullet[i * 6 + j].fireX = randSiteX;
			_vGuidedBullet[i * 6 + j].fireY = randSiteY;
			_vGuidedBullet[i * 6 + j].speed = 0.5f;
			_vGuidedBullet[i * 6 + j].limitedCount = 150 + (i * 10 + j) * 5;
			_vGuidedBullet[i * 6 + j].isfire = true;
		}
	}
}

void guided_bullet::move()
{
	//for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < _vGuidedBullet.size(); ++i)
		{
			if (_vGuidedBullet[i].isfire)
			{
				_vGuidedBullet[i].x += cosf(_vGuidedBullet[i].angleX_first)*_vGuidedBullet[i].speed;
				_vGuidedBullet[i].y += -sinf(_vGuidedBullet[i].angleY_first)*_vGuidedBullet[i].speed;

				_vGuidedBullet[i].count++;

				if (_vGuidedBullet[i].count == 84)
				{
					_vGuidedBullet[i].speed = 0.f;
				}
				else if (_vGuidedBullet[i].count > _vGuidedBullet[i].limitedCount)
				{
					_vGuidedBullet[i].isActive_first = true;
					_vGuidedBullet[i].isfire = false;
					_vGuidedBullet[i].count = 0;

					_vGuidedBullet[i].angleX_second = getAngle(_vGuidedBullet[i].x, _vGuidedBullet[i].y, _player->getX(), _player->getY());
					_vGuidedBullet[i].angleY_second = getAngle(_vGuidedBullet[i].x, _vGuidedBullet[i].y, _player->getX(), _player->getY());
					SOUNDMANAGER->play("최종별파이어", SAVEDATA->getEffSound());
				}

				_vGuidedBullet[i].rc = RectMakeCenter(_vGuidedBullet[i].x, _vGuidedBullet[i].y, _vGuidedBullet[i].radius, _vGuidedBullet[i].radius);
			}

		}

	}

	for (int i = 0; i < _vGuidedBullet.size(); i ++)
	{
		if (_vGuidedBullet[i].isActive_first)
		{
			_vGuidedBullet[i].speed = 15.f;

			_vGuidedBullet[i].x += cosf(_vGuidedBullet[i].angleX_second)* (_vGuidedBullet[i].speed);
			_vGuidedBullet[i].y += -sinf(_vGuidedBullet[i].angleY_second)* (_vGuidedBullet[i].speed);
			_vGuidedBullet[i].rc = RectMakeCenter(_vGuidedBullet[i].x, _vGuidedBullet[i].y, _vGuidedBullet[i].radius, _vGuidedBullet[i].radius);

			_vGuidedBullet[i].count++;

			if (_vGuidedBullet[i].count > 300)
			{
				//_vGuidedBullet[i].isActive_second = false;
				_vGuidedBullet[i].isActive_first = false;
				/*_vGuidedBullet[i].speed = 1.f;
				_vGuidedBullet[i].x = (i / 12) * 200 + 300;
				_vGuidedBullet[i].y = 200 + (i / 12) * 100;
				_vGuidedBullet[i].angleX_second = PI / 180 * 30 * (i % 12);
				_vGuidedBullet[i].angleY_second = PI / 180 * 30 * (i % 12);*/
				_vGuidedBullet[i].count = 0;

			}
		}
	}
}

void guided_bullet::animation()
{
}


///////////////////////////// 토네이도
///////////////////////////////////////
HRESULT tornado_bullet::init()
{

	GDIPLUS->addImage("회오리총알1", "resource/bullet/회오리총알11.png");
	GDIPLUS->addImage("회오리총알2", "resource/bullet/회오리총알22.png");
	GDIPLUS->addImage("회오리총알3", "resource/bullet/회오리총알33.png");


	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 200; j++)
		{

			RB_BULLET_PNG _tornadoBullet;

			ZeroMemory(&_tornadoBullet, sizeof(RB_BULLET_PNG));

			_tornadoBullet.angleX_second = 0;
			_tornadoBullet.angleY_second = 0;
			_tornadoBullet.x = 0;
			_tornadoBullet.y = 0;
			_tornadoBullet.fireX = 0;
			_tornadoBullet.fireY = 0;
			_tornadoBullet.indexX = 0;
			_tornadoBullet.indexY = 0;
			//if (j < 6)
			//	_spiderBullet.speed = 5.f + 1.f*j;
			//else
			//	_spiderBullet.speed = 10.f - 1.f*(j - 6);
			_tornadoBullet.speed = 7.f;
			_tornadoBullet.radius = 20;
			_tornadoBullet.gravity = 0;
			_tornadoBullet.damage = 30;
			_tornadoBullet.count = 0;
			_tornadoBullet.isfire = false;
			_tornadoBullet.isActive_first = false;  // 동시에 발사
			_tornadoBullet.isActive_second = false;  // 동시에 발사
			_tornadoBullet._bulletImg[0] = GDIPLUS->findImage("회오리총알1");
			_tornadoBullet._bulletImg[1] = GDIPLUS->findImage("회오리총알2");
			_tornadoBullet._bulletImg[2] = GDIPLUS->findImage("회오리총알3");

			_vTornadoBullet.push_back(_tornadoBullet);

		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = checkCount = 0;

	return S_OK;
}

void tornado_bullet::release()
{
}

void tornado_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void tornado_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (!_vTornadoBullet[i * 20 + j].isfire && !_vTornadoBullet[i * 20 + j].isActive_first)
			{
				_vTornadoBullet[i * 20 + j].angleX_first = PI / 180 * 18 * j + i*6;
				_vTornadoBullet[i * 20 + j].angleY_first = PI / 180 * 18 * j + i*6;
				_vTornadoBullet[i * 20 + j].x = x + 30 + cosf(_vTornadoBullet[i * 20 + j].angleX_first) * (i % 2 + 2) * 100;
				_vTornadoBullet[i * 20 + j].y = y + 30 - sinf(_vTornadoBullet[i * 20 + j].angleY_first) * (i % 2 + 2) * 100;
				_vTornadoBullet[i * 20 + j].fireX = x + 30 + cosf(_vTornadoBullet[i * 20 + j].angleX_first) * (i % 2 + 2) * 100;
				_vTornadoBullet[i * 20 + j].fireY = y + 30 - sinf(_vTornadoBullet[i * 20 + j].angleY_first) * (i % 2 + 2) * 100;
				_vTornadoBullet[i * 20 + j].speed = (i % 2 + 2) * 2.f;
				_vTornadoBullet[i * 20 + j].limitedCount = 200;
				_vTornadoBullet[i * 20 + j].isfire = true;
				_vTornadoBullet[i * 20 + j].isActive_first = true;
				
			}
		}
		if (i == checkCount)
		{
			checkCount++;
			break;
		}
	}
}

void tornado_bullet::move()
{
	//for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < _vTornadoBullet.size(); ++i)
		{
			if (_vTornadoBullet[i].isfire)
			{
				if ((i / 40) % 2 == 0)
				{
					_vTornadoBullet[i].angleX_first += 0.02f;
					_vTornadoBullet[i].angleY_first += 0.02f;
					_vTornadoBullet[i].x += cosf(_vTornadoBullet[i].angleX_first + PI / 2) *_vTornadoBullet[i].speed;
					_vTornadoBullet[i].y += -sinf(_vTornadoBullet[i].angleY_first + PI / 2) *_vTornadoBullet[i].speed;
				}
				else
				{
					_vTornadoBullet[i].angleX_first -= 0.02f;
					_vTornadoBullet[i].angleY_first -= 0.02f;
					_vTornadoBullet[i].x += cosf(_vTornadoBullet[i].angleX_first - PI / 2) *_vTornadoBullet[i].speed;
					_vTornadoBullet[i].y += -sinf(_vTornadoBullet[i].angleY_first - PI / 2) *_vTornadoBullet[i].speed;
				}
				



				_vTornadoBullet[i].count++;

				if(_vTornadoBullet[i].count > _vTornadoBullet[i].limitedCount)
				{
					//SOUNDMANAGER->play("최종토네이도파이어", SAVEDATA->getEffSound());

					if ((i / 40) % 2 == 0)
					{
						_vTornadoBullet[i].angleX_first -= 0.02f;
						_vTornadoBullet[i].angleY_first -= 0.02f;
					}
					else
					{
						_vTornadoBullet[i].angleX_first += 0.02f;
						_vTornadoBullet[i].angleY_first += 0.02f;
					}
					_vTornadoBullet[i].speed = 18.f;
					//_vTornadoBullet[i].isActive_first = true;
					//_vTornadoBullet[i].isfire = false;
					//_vTornadoBullet[i].count = 0;

					//_vTornadoBullet[i].angleX_second = getAngle(_vTornadoBullet[i].x, _vTornadoBullet[i].y, _player->getX(), _player->getY());
					//_vTornadoBullet[i].angleY_second = getAngle(_vTornadoBullet[i].x, _vTornadoBullet[i].y, _player->getX(), _player->getY());

				}
				if (_vTornadoBullet[i].count > 400)
				{
					_vTornadoBullet[i].isfire = false;
					_vTornadoBullet[i].count = 0;
					if (i == _vTornadoBullet.size() - 1)
					{
						checkCount = 0;
						for (int i = 0; i < _vTornadoBullet.size(); ++i)
						{
							_vTornadoBullet[i].isActive_first = false;
						}
					}
				}


				_vTornadoBullet[i].rc = RectMakeCenter(_vTornadoBullet[i].x, _vTornadoBullet[i].y, _vTornadoBullet[i].radius, _vTornadoBullet[i].radius);
			}

		}

	}

}

void tornado_bullet::animation()
{
}




///////////////////////////// 스네이크
///////////////////////////////////////
HRESULT snake_bullet::init()
{

	GDIPLUS->addImage("뱀총알", "resource/bullet/뱀총알.png");
	
	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			RB_BULLET_PNG _snakeBullet;

			ZeroMemory(&_snakeBullet, sizeof(RB_BULLET_PNG));

			_snakeBullet.angleX_second = 0;
			_snakeBullet.angleY_second = 0;
			_snakeBullet.x = 0;
			_snakeBullet.y = 0;
			_snakeBullet.fireX = 0;
			_snakeBullet.fireY = 0;
			_snakeBullet.indexX = 0;
			_snakeBullet.indexY = 0;
			//if (j < 6)
			//	_spiderBullet.speed = 5.f + 1.f*j;
			//else
			//	_spiderBullet.speed = 10.f - 1.f*(j - 6);
			_snakeBullet.speed = 7.f;
			_snakeBullet.radius = 20;
			_snakeBullet.gravity = 0;
			_snakeBullet.damage = 40;
			_snakeBullet.count = 0;
			_snakeBullet.isfire = false;
			_snakeBullet.isActive_first = false;  // 동시에 발사
			_snakeBullet.isActive_second = false;  // 동시에 발사
			_snakeBullet._bulletImg[0] = GDIPLUS->findImage("뱀총알");
			//_snakeBullet._bulletImg[1] = GDIPLUS->findImage("회오리총알2");
			//_snakeBullet._bulletImg[2] = GDIPLUS->findImage("회오리총알3");

			_vSnakebullet.push_back(_snakeBullet);

		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = checkCount = 0;

	return S_OK;
}

void snake_bullet::release()
{
}

void snake_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void snake_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (!_vSnakebullet[i * 20 + j].isfire && !_vSnakebullet[i * 20 + j].isActive_first)
			{
				_vSnakebullet[i * 20 + j].angleX_first = PI / 180 * 12 * i + PI / 180 * 60;
				_vSnakebullet[i * 20 + j].angleY_first = PI / 180 * 12 * i + PI / 180 * 60;
				_vSnakebullet[i * 20 + j].x = x + 30;// +cosf(_vSnakebullet[i * 20 + j].angleX_first) * (i % 2 + 2) * 100;
				_vSnakebullet[i * 20 + j].y = y + 30;// -sinf(_vSnakebullet[i * 20 + j].angleY_first) * (i % 2 + 2) * 100;
				_vSnakebullet[i * 20 + j].fireX = x + 30;// +cosf(_vSnakebullet[i * 20 + j].angleX_first) * (i % 2 + 2) * 100;
				_vSnakebullet[i * 20 + j].fireY = y + 30;// -sinf(_vSnakebullet[i * 20 + j].angleY_first) * (i % 2 + 2) * 100;
				_vSnakebullet[i * 20 + j].speed = 5.f;
				_vSnakebullet[i * 20 + j].limitedCount = j*3;
				_vSnakebullet[i * 20 + j].isfire = true;
				_vSnakebullet[i * 20 + j].isActive_first = true;
				SOUNDMANAGER->play("최종스네이크파이어", SAVEDATA->getEffSound());
			}
		}
		if (i == checkCount)
		{
			checkCount++;
			break;
		}
	}
}

void snake_bullet::move()
{
	//for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < _vSnakebullet.size(); ++i)
		{
			if (_vSnakebullet[i].isfire)
			{
				//if ((i / 40) % 2 == 0)
				{
					/*_vSnakebullet[i].angleX_first += 0.02f;
					_vSnakebullet[i].angleY_first += 0.02f;*/
					_vSnakebullet[i].gravity += 0.05f;
					_vSnakebullet[i].x += cosf(_vSnakebullet[i].angleX_first ) *_vSnakebullet[i].speed;
					_vSnakebullet[i].y += -sinf(_vSnakebullet[i].angleY_first ) *_vSnakebullet[i].speed + _vSnakebullet[i].gravity;
				}
				/*else
				{
					_vSnakebullet[i].angleX_first -= 0.02f;
					_vSnakebullet[i].angleY_first -= 0.02f;
					_vSnakebullet[i].x += cosf(_vSnakebullet[i].angleX_first - PI / 2) *_vSnakebullet[i].speed;
					_vSnakebullet[i].y += -sinf(_vSnakebullet[i].angleY_first - PI / 2) *_vSnakebullet[i].speed;
				}*/

				//_vSnakebullet[i].count++;

				if (_vSnakebullet[i].y > 710)
				{
					_vSnakebullet[i].isfire = false;
					_vSnakebullet[i].isActive_second = true;
					_vSnakebullet[i].angleX_second = PI / 2;
					_vSnakebullet[i].angleY_second = PI / 2;
					_vSnakebullet[i].gravity = 0.f;
					_vSnakebullet[i].speed = 10.f;
					SOUNDMANAGER->play("최종스네이크파이어2", SAVEDATA->getEffSound());

				}

				_vSnakebullet[i].rc = RectMakeCenter(_vSnakebullet[i].x, _vSnakebullet[i].y, _vSnakebullet[i].radius, _vSnakebullet[i].radius);
			}

		}

	}

	for (int i = 0; i < _vSnakebullet.size(); i++)
	{
		if (_vSnakebullet[i].isActive_second)
		{
			_vSnakebullet[i].angleX_second += 0.3f;
			_vSnakebullet[i].x += cosf(_vSnakebullet[i].angleX_second)* (_vSnakebullet[i].speed);
			_vSnakebullet[i].y += -sinf(_vSnakebullet[i].angleY_second)* (_vSnakebullet[i].speed);

			_vSnakebullet[i].count++;

			if (_vSnakebullet[i].count > _vSnakebullet[i].limitedCount)
			{
				_vSnakebullet[i].speed = 0.f;
			}
			if (_vSnakebullet[_vSnakebullet.size() - 1].speed == 0)
			{
				for (int i = 0; i < _vSnakebullet.size(); i++)
				{
					_vSnakebullet[i].isActive_third = true;
					_vSnakebullet[i].isActive_second = false;
					_vSnakebullet[i].angleX_first = PI / 180 * (RND->getInt(360));
					_vSnakebullet[i].angleY_first = PI / 180 * (RND->getInt(360));
					_vSnakebullet[i].speed = 3.f;
					_vSnakebullet[i].count = 0;;
				}
			}
			_vSnakebullet[i].rc = RectMakeCenter(_vSnakebullet[i].x, _vSnakebullet[i].y, _vSnakebullet[i].radius, _vSnakebullet[i].radius);
		}
	}

	for (int i = 0; i < _vSnakebullet.size(); i++)
	{
		if (_vSnakebullet[i].isActive_third)
		{
			_vSnakebullet[i].x += cosf(_vSnakebullet[i].angleX_first)* (_vSnakebullet[i].speed);
			_vSnakebullet[i].y += -sinf(_vSnakebullet[i].angleY_first)* (_vSnakebullet[i].speed);

			_vSnakebullet[i].count++;

			if (_vSnakebullet[i].count > 500)
			{
				_vSnakebullet[i].isActive_first = false;
				_vSnakebullet[i].isActive_third = false;
				checkCount = 0;
				_vSnakebullet[i].count = 0;
			}
			_vSnakebullet[i].rc = RectMakeCenter(_vSnakebullet[i].x, _vSnakebullet[i].y, _vSnakebullet[i].radius, _vSnakebullet[i].radius);
		}
	}
}

void snake_bullet::animation()
{
}




///////////////////////////// 다각형
///////////////////////////////////////
HRESULT polygon_bullet::init()
{

	GDIPLUS->addImage("다각형총알1", "resource/bullet/다각형총알1.png");

	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 80; j++)
		{

			RB_BULLET_PNG _polygonBullet;

			ZeroMemory(&_polygonBullet, sizeof(RB_BULLET_PNG));

			_polygonBullet.angleX_second = 0;
			_polygonBullet.angleY_second = 0;
			_polygonBullet.x = 0;
			_polygonBullet.y = 0;
			_polygonBullet.fireX = 0;
			_polygonBullet.fireY = 0;
			_polygonBullet.indexX = 0;
			_polygonBullet.indexY = 0;
			//if (j < 6)
			//	_spiderBullet.speed = 5.f + 1.f*j;
			//else
			//	_spiderBullet.speed = 10.f - 1.f*(j - 6);
			_polygonBullet.speed = 7.f;
			_polygonBullet.radius = 20;
			_polygonBullet.gravity = 0;
			_polygonBullet.damage = 50;
			_polygonBullet.count = 0;
			_polygonBullet.isfire = false;
			_polygonBullet.isActive_first = false;  // 동시에 발사
			_polygonBullet.isActive_second = false;  // 동시에 발사
			_polygonBullet._bulletImg[0] = GDIPLUS->findImage("블루총알1");
			_polygonBullet._bulletImg[1] = GDIPLUS->findImage("다각형총알1");
			_polygonBullet._bulletImg[2] = GDIPLUS->findImage("유도탄총알2");

			_vPolygonBullet.push_back(_polygonBullet);

		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = checkCount = 0;

	return S_OK;
}

void polygon_bullet::release()
{
}

void polygon_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void polygon_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (!_vPolygonBullet[i * 16 + j].isfire)
			{
				_vPolygonBullet[i * 16 + j].angleX_first = PI / 180 * (72 * i);
				_vPolygonBullet[i * 16 + j].angleY_first = PI / 180 * (72 * i);
				_vPolygonBullet[i * 16 + j].x = x + 30;
				_vPolygonBullet[i * 16 + j].y = y + 30;
				_vPolygonBullet[i * 16 + j].fireX = x + 30;
				_vPolygonBullet[i * 16 + j].fireY = y + 30;
				_vPolygonBullet[i * 16 + j].speed = 8.f;
				_vPolygonBullet[i * 16 + j].limitedCount = j * 3;
				_vPolygonBullet[i * 16 + j].isfire = true;
				SOUNDMANAGER->play("최종다각형파이어", SAVEDATA->getEffSound());

			}
		}
	}
}

void polygon_bullet::move()
{

	for (int i = 0; i < _vPolygonBullet.size(); ++i)
	{
		if (_vPolygonBullet[i].isfire)
		{
			_vPolygonBullet[i].count++;

			if (_vPolygonBullet[i].count > _vPolygonBullet[i].limitedCount)
			{
				_vPolygonBullet[i].speed = 13.f;
				_vPolygonBullet[i].x += cosf(_vPolygonBullet[i].angleX_first) *_vPolygonBullet[i].speed;
				_vPolygonBullet[i].y += -sinf(_vPolygonBullet[i].angleY_first) *_vPolygonBullet[i].speed;
			}
			
			if(_vPolygonBullet[i].count > 50)
			{
				SOUNDMANAGER->play("최종다각형파이어", SAVEDATA->getEffSound());

				_vPolygonBullet[i].speed = 0.f;
				_vPolygonBullet[i].angleX_first += PI / 180 * 120;
				_vPolygonBullet[i].angleY_first += PI / 180 * 120;
				_vPolygonBullet[i].count = 0;
				checkCount++;
			}

			if (checkCount == 12*80)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						_vPolygonBullet[i * 16 + j].isfire = false;
						_vPolygonBullet[i * 16 + j].isActive_first = true;
						_vPolygonBullet[i * 16 + j].angleX_first = PI/180*240;
						_vPolygonBullet[i * 16 + j].angleY_first = PI/180*240;
						_vPolygonBullet[i * 16 + j].limitedCount = (i * 16 + j) * 6;
						_vPolygonBullet[i * 16 + j].x = WINSIZEX/2+40;
						_vPolygonBullet[i * 16 + j].y = 100;
						_vPolygonBullet[i * 16 + j].count = 0;
						if (i == 4)
						{
							_vPolygonBullet[i * 16 + j].isfire = false;
							_vPolygonBullet[i * 16 + j].isActive_first = true;
							_vPolygonBullet[i * 16 + j].x = _vPolygonBullet[i * 16 + j].fireX + 20;
							_vPolygonBullet[i * 16 + j].y = _vPolygonBullet[i * 16 + j].fireY + 20;
							_vPolygonBullet[i * 16 + j].angleX_first = getAngle(_vPolygonBullet[i * 16 + j].x, _vPolygonBullet[i * 16 + j].y, _player->getX(), _player->getY());
							_vPolygonBullet[i * 16 + j].angleY_first = getAngle(_vPolygonBullet[i * 16 + j].x, _vPolygonBullet[i * 16 + j].y, _player->getX(), _player->getY());
							_vPolygonBullet[i * 16 + j].limitedCount = (i * 16 + j)*6;
							_vPolygonBullet[i * 16 + j].speed = 8.f;
							_vPolygonBullet[i * 16 + j].count = 0;
						}
						SOUNDMANAGER->play("최종다각형파이어", SAVEDATA->getEffSound());

						checkCount = 0;
					}
				}
			}

			_vPolygonBullet[i].rc = RectMakeCenter(_vPolygonBullet[i].x, _vPolygonBullet[i].y, _vPolygonBullet[i].radius, _vPolygonBullet[i].radius);
		}

	}



	for (int i = 0; i < _vPolygonBullet.size(); i++)
	{
		if (_vPolygonBullet[i].isActive_first)
		{
			_vPolygonBullet[i].count++;

			if (i < 64)
			{
				if (_vPolygonBullet[i].count > _vPolygonBullet[i].limitedCount)
				{
					_vPolygonBullet[i].speed = 10.f;
					_vPolygonBullet[i].x += cosf(_vPolygonBullet[i].angleX_first) *_vPolygonBullet[i].speed;
					_vPolygonBullet[i].y += -sinf(_vPolygonBullet[i].angleY_first) *_vPolygonBullet[i].speed;
				}
				if (_vPolygonBullet[i].count == 64 + _vPolygonBullet[i].limitedCount)
				{
					_vPolygonBullet[i].speed = 0.f;
					_vPolygonBullet[i].angleX_first += PI / 180 * 144;
					_vPolygonBullet[i].angleY_first += PI / 180 * 144;
					_vPolygonBullet[i].count = 0;
				}
			}
			else
			{
				if (_vPolygonBullet[i].count == _vPolygonBullet[i].limitedCount)
				{
					_vPolygonBullet[i].angleX_first = getAngle(_vPolygonBullet[i].x, _vPolygonBullet[i].y, _player->getX(), _player->getY());
					_vPolygonBullet[i].angleY_first = getAngle(_vPolygonBullet[i].x, _vPolygonBullet[i].y, _player->getX(), _player->getY());
					SOUNDMANAGER->play("최종다각형파이어2", SAVEDATA->getEffSound());

				}
				else if (_vPolygonBullet[i].count > _vPolygonBullet[i].limitedCount)
				{
					_vPolygonBullet[i].x += cosf(_vPolygonBullet[i].angleX_first) *_vPolygonBullet[i].speed;
					_vPolygonBullet[i].y += -sinf(_vPolygonBullet[i].angleY_first) *_vPolygonBullet[i].speed;
				}
				if (_vPolygonBullet[i].count == _vPolygonBullet[i].limitedCount + 100)
				{
					_vPolygonBullet[i].x = _vPolygonBullet[i].fireX + 20;
					_vPolygonBullet[i].y = _vPolygonBullet[i].fireY + 20;
					_vPolygonBullet[i].limitedCount = i * 6;
					_vPolygonBullet[i].speed = 8.f;
					_vPolygonBullet[i].count = 0;
					checkCount++;

					if (checkCount == 40)
					{

						for (int i = 0; i < _vPolygonBullet.size(); i++)
						{
							_vPolygonBullet[i].isActive_first = false;
						}
					}
				}


			}




			_vPolygonBullet[i].rc = RectMakeCenter(_vPolygonBullet[i].x, _vPolygonBullet[i].y, _vPolygonBullet[i].radius, _vPolygonBullet[i].radius);
		}
	}

}

void polygon_bullet::animation()
{
}

///////////////////////////// 문어///
///////////////////////////////////////
HRESULT octopus_bullet::init()
{

	GDIPLUS->addImage("문어총알1", "resource/bullet/문어총알1.png");
	GDIPLUS->addImage("문어총알2", "resource/bullet/문어총알2.png");
	GDIPLUS->addImage("문어총알3", "resource/bullet/문어총알3.png");
	GDIPLUS->addImage("문어총알4", "resource/bullet/문어총알4.png");

	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 68; j++)
		{

			RB_BULLET_PNG _octopusBullet;

			ZeroMemory(&_octopusBullet, sizeof(RB_BULLET_PNG));

			_octopusBullet.angleX_second = 0;
			_octopusBullet.angleY_second = 0;
			_octopusBullet.x = 0;
			_octopusBullet.y = 0;
			_octopusBullet.fireX = 0;
			_octopusBullet.fireY = 0;
			_octopusBullet.indexX = 0;
			_octopusBullet.indexY = 0;
			_octopusBullet.speed = 7.f;
			_octopusBullet.radius = 20;
			_octopusBullet.gravity = 0;
			_octopusBullet.damage = 50;
			_octopusBullet.count = 0;
			_octopusBullet.isfire = false;
			_octopusBullet.isActive_first = false;  // 동시에 발사
			_octopusBullet.isActive_second = false;  // 동시에 발사
			_octopusBullet._bulletImg[0] = GDIPLUS->findImage("문어총알1");
			_octopusBullet._bulletImg[1] = GDIPLUS->findImage("문어총알2");
			_octopusBullet._bulletImg[2] = GDIPLUS->findImage("문어총알3");
			_octopusBullet._bulletImg[3] = GDIPLUS->findImage("문어총알4");

			_vOctopusBullet.push_back(_octopusBullet);
		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = checkCount = 0;

	return S_OK;
}

void octopus_bullet::release()
{
}

void octopus_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void octopus_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (!_vOctopusBullet[i * 16 + j].isfire)// && !_vPolygonBullet[i * 16 + j].isActive_first)
			{
				_vOctopusBullet[i * 16 + j].angleX_first = j / 8 * PI;
				_vOctopusBullet[i * 16 + j].angleY_first = 0;
				_vOctopusBullet[i * 16 + j].x = WINSIZEX / 2;
				_vOctopusBullet[i * 16 + j].y = WINSIZEY/2 - 100 - 180 + 60 * (j % 8);
				_vOctopusBullet[i * 16 + j].fireX = WINSIZEX / 2;
				_vOctopusBullet[i * 16 + j].fireY = WINSIZEY / 2 - 100 - 180 + 60 * (j % 8);
				if (j < 4)
					_vOctopusBullet[i * 16 + j].speed = j * SPINSPEED;
				else if (j < 8)
					_vOctopusBullet[i * 16 + j].speed = 3* SPINSPEED - (j - 4) * SPINSPEED;
				else if (j < 12)
					_vOctopusBullet[i * 16 + j].speed = (j - 8) * SPINSPEED;
				else if (j < 16)
					_vOctopusBullet[i * 16 + j].speed = 3* SPINSPEED - (j - 12)*SPINSPEED;
				_vOctopusBullet[i * 16 + j].limitedCount = i * 50;
				_vOctopusBullet[i * 16 + j].isfire = true;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_vOctopusBullet[48 + i * 5 + j].x = WINSIZEX / 2 + cosf(PI / 180 * 5 * j + PI / 2 * i) * 100;
			_vOctopusBullet[48 + i * 5 + j].y = WINSIZEY / 2 - 100 + sinf(PI / 180 * 5 * j + PI / 2 * i) * 100;
			_vOctopusBullet[48 + i * 5 + j].fireX = WINSIZEX / 2 + cosf(PI / 180 * 5 * j + PI / 2 * i) * 100;
			_vOctopusBullet[48 + i * 5 + j].fireY = WINSIZEY / 2 - 100 + sinf(PI / 180 * 5 * j + PI / 2 * i) * 100;

			_vOctopusBullet[48 + i * 5 + j].angleX_first = PI / 180 * 5 * j + PI / 2 * i;
			_vOctopusBullet[48 + i * 5 + j].angleY_first = PI / 180 * 5 * j + PI / 2 * i;
		
			_vOctopusBullet[48 + i * 5 + j].speed = 5.f;
			_vOctopusBullet[48 + i * 5 + j].limitedCount = 150 + (i * 5 + j)*10;
			_vOctopusBullet[48 + i * 5 + j].isfire = true;

		}
	}
}

void octopus_bullet::move()
{

	for (int i = 0; i < _vOctopusBullet.size(); ++i)
	{
		if (_vOctopusBullet[i].isfire)
		{
			_vOctopusBullet[i].count++;

			if (i < 48)
			{

				if (_vOctopusBullet[i].count > _vOctopusBullet[i].limitedCount)
				{
					_vOctopusBullet[i].angleX_first += 0.02f;
					_vOctopusBullet[i].x += cosf(_vOctopusBullet[i].angleX_first) *_vOctopusBullet[i].speed;
					_vOctopusBullet[i].y += -sinf(_vOctopusBullet[i].angleY_first) *_vOctopusBullet[i].speed;
					if(count == 30)
						SOUNDMANAGER->play("최종문어파이어", SAVEDATA->getEffSound());

				}
			}
			else
			{
				_vOctopusBullet[i].angleX_first += 0.05f;
				_vOctopusBullet[i].angleY_first += 0.05f;
				_vOctopusBullet[i].x += cosf(_vOctopusBullet[i].angleX_first + PI / 2) *_vOctopusBullet[i].speed;
				_vOctopusBullet[i].y += -sinf(_vOctopusBullet[i].angleY_first + PI / 2) *_vOctopusBullet[i].speed;


				if (_vOctopusBullet[i].count == _vOctopusBullet[i].limitedCount)
				{
					_vOctopusBullet[i].isActive_first = true;
					_vOctopusBullet[i].isfire = false;
					_vOctopusBullet[i].count = 0;
					_vOctopusBullet[i].x = _vOctopusBullet[i].fireX;
					_vOctopusBullet[i].y = _vOctopusBullet[i].fireY;

				}


			}


			_vOctopusBullet[i].rc = RectMakeCenter(_vOctopusBullet[i].x, _vOctopusBullet[i].y, _vOctopusBullet[i].radius, _vOctopusBullet[i].radius);
		}

	}



	for (int i = 0; i < _vOctopusBullet.size(); i++)
	{
		if (_vOctopusBullet[i].isActive_first)
		{
			_vOctopusBullet[i].count++;

			if (_vOctopusBullet[i].count == _vOctopusBullet[i].limitedCount)
			{
				_vOctopusBullet[i].angleX_first = getAngle(_vOctopusBullet[i].x, _vOctopusBullet[i].y, _player->getX(), _player->getY());
				_vOctopusBullet[i].angleY_first = getAngle(_vOctopusBullet[i].x, _vOctopusBullet[i].y, _player->getX(), _player->getY());
				SOUNDMANAGER->play("최종문어파이어2", SAVEDATA->getEffSound());

			}

			if (_vOctopusBullet[i].count > _vOctopusBullet[i].limitedCount)
			{
				_vOctopusBullet[i].speed = 10.f;
				_vOctopusBullet[i].x += cosf(_vOctopusBullet[i].angleX_first) *_vOctopusBullet[i].speed;
				_vOctopusBullet[i].y += -sinf(_vOctopusBullet[i].angleY_first) *_vOctopusBullet[i].speed;
			}

			if (_vOctopusBullet[i].count == _vOctopusBullet[i].limitedCount + 100)
			{
				_vOctopusBullet[i].x = _vOctopusBullet[i].fireX;
				_vOctopusBullet[i].y = _vOctopusBullet[i].fireY;
				_vOctopusBullet[i].limitedCount = i * 10 - 45;
				_vOctopusBullet[i].speed = 10.f;
				_vOctopusBullet[i].count = 0;


				checkCount++;

				if (checkCount == 60)
				{
					for (int i = 0; i < _vOctopusBullet.size(); i++)
					{
						_vOctopusBullet[i].isActive_first = false;
						_vOctopusBullet[i].isfire = false;
						_vOctopusBullet[i].count = 0;

					}
				}
			}


			_vOctopusBullet[i].rc = RectMakeCenter(_vOctopusBullet[i].x, _vOctopusBullet[i].y, _vOctopusBullet[i].radius, _vOctopusBullet[i].radius);
		}
	}

	/*
	for (int i = 0; i < _vSnakebullet.size(); i++)
	{
		if (_vSnakebullet[i].isActive_third)
		{
			_vSnakebullet[i].x += cosf(_vSnakebullet[i].angleX_first)* (_vSnakebullet[i].speed);
			_vSnakebullet[i].y += -sinf(_vSnakebullet[i].angleY_first)* (_vSnakebullet[i].speed);

			_vSnakebullet[i].count++;

			if (_vSnakebullet[i].count > 400)
			{
				_vSnakebullet[i].isActive_first = false;
				_vSnakebullet[i].isActive_third = false;
				checkCount = 0;
				_vSnakebullet[i].count = 0;
			}
			_vSnakebullet[i].rc = RectMakeCenter(_vSnakebullet[i].x, _vSnakebullet[i].y, _vSnakebullet[i].radius, _vSnakebullet[i].radius);
		}
	}*/
}

void octopus_bullet::animation()
{
}





///////////////////////////// 볼     ///
///////////////////////////////////////
HRESULT ball_bullet::init()
{

	GDIPLUS->addImage("볼총알", "resource/bullet/태양총알테두리.png");


	//for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 90; j++)
		{

			RB_BULLET_PNG _ballBullet;

			ZeroMemory(&_ballBullet, sizeof(RB_BULLET_PNG));

			_ballBullet.angleX_second = 0;
			_ballBullet.angleY_second = 0;
			_ballBullet.x = 0;
			_ballBullet.y = 0;
			_ballBullet.fireX = 0;
			_ballBullet.fireY = 0;
			_ballBullet.indexX = 0;
			_ballBullet.indexY = 0;
			_ballBullet.speed = 7.f;
			_ballBullet.radius = 20;
			_ballBullet.gravity = 0;
			_ballBullet.damage = 50;
			_ballBullet.count = 0;
			_ballBullet.isfire = false;
			_ballBullet.isActive_first = false;  // 동시에 발사
			_ballBullet.isActive_second = false;  // 동시에 발사
			_ballBullet._bulletImg[0] = GDIPLUS->findImage("볼총알");
			//_ballBullet._bulletImg[1] = GDIPLUS->findImage("문어총알2");
			//_ballBullet._bulletImg[2] = GDIPLUS->findImage("문어총알3");
			//_ballBullet._bulletImg[3] = GDIPLUS->findImage("문어총알4");

			_vBallBullet.push_back(_ballBullet);
		}

		//_vSpider.push_back(_vSpiderWebBullet);
		//_vSpiderWebBullet.clear();
	}

	count = checkCount = 0;

	return S_OK;
}

void ball_bullet::release()
{
}

void ball_bullet::update()
{
	count++;
	this->move();
	this->animation();
}

void ball_bullet::fire(float x, float y, int order)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (!_vBallBullet[i * 30 + j].isfire)// && !_vPolygonBullet[i * 16 + j].isActive_first)
			{
				_vBallBullet[i * 30 + j].angleX_first = 0;
				_vBallBullet[i * 30 + j].angleY_first = 0;
				_vBallBullet[i * 30 + j].x = x + 30;
				_vBallBullet[i * 30 + j].y = y -150;
				_vBallBullet[i * 30 + j].fireX = x + 30;
				_vBallBullet[i * 30 + j].fireY = y - 150;
				_vBallBullet[i * 30 + j].speed = 2.f;
				_vBallBullet[i * 30 + j].limitedCount = j * 5 + 150 * i;
				_vBallBullet[i * 30 + j].isfire = true;
			}
		}
	}


}

void ball_bullet::move()
{

	for (int i = 0; i < _vBallBullet.size(); ++i)
	{
		if (_vBallBullet[i].isfire)
		{
			_vBallBullet[i].count++;

			if (_vBallBullet[i].count == _vBallBullet[i].limitedCount)
				SOUNDMANAGER->play("최종볼파이어", SAVEDATA->getEffSound());

			if (_vBallBullet[i].count > _vBallBullet[i].limitedCount)
			{
				_vBallBullet[i].angleX_first += 0.2f;
				_vBallBullet[i].angleY_first += 0.2f;
				_vBallBullet[i].speed += 0.1f;

				_vBallBullet[i].x += cosf(_vBallBullet[i].angleX_first + PI/2) *_vBallBullet[i].speed;
				_vBallBullet[i].y += -sinf(_vBallBullet[i].angleY_first + PI/2) *_vBallBullet[i].speed;
			}
			if (_vBallBullet[i].count == 500)
			{
				_vBallBullet[i].isfire = false;
				_vBallBullet[i].isActive_first = true;
				_vBallBullet[i].count = 0;
			}

			_vBallBullet[i].rc = RectMakeCenter(_vBallBullet[i].x, _vBallBullet[i].y, _vBallBullet[i].radius, _vBallBullet[i].radius);
		}

	}

	for (int i = 0; i < _vBallBullet.size(); ++i)
	{
		if (_vBallBullet[i].isActive_first)
		{
			_vBallBullet[i].count++;

			if (_vBallBullet[i].count < 100)
			{
				_vBallBullet[i].angleX_first += 0.2f;
				_vBallBullet[i].angleY_first += 0.2f;
				//_vBallBullet[i].speed -= 0.1f;

				_vBallBullet[i].x += cosf(_vBallBullet[i].angleX_first + PI / 2) *_vBallBullet[i].speed + 3;
				_vBallBullet[i].y += -sinf(_vBallBullet[i].angleY_first + PI / 2) *_vBallBullet[i].speed - 1;
			}
			else
			{
				_vBallBullet[i].speed = 5.f;
				_vBallBullet[i].x += cosf(_vBallBullet[i].angleX_first) *_vBallBullet[i].speed;
				_vBallBullet[i].y += -sinf(_vBallBullet[i].angleY_first) *_vBallBullet[i].speed;
			}
			if (_vBallBullet[i].count == 300)
			{
				_vBallBullet[i].isActive_first = false;
				_vBallBullet[i].count = 0;
			}

			_vBallBullet[i].rc = RectMakeCenter(_vBallBullet[i].x, _vBallBullet[i].y, _vBallBullet[i].radius, _vBallBullet[i].radius);
		}

	}


}

void ball_bullet::animation()
{
}
