#include "stdafx.h"
#include "RBenemy.h"

void RBenemy::init()
{

}

void RBenemy::update(stage_MAPt* _maps)
{
	count++;



	if (KEYMANAGER->isStayKeyDown('L'))
	{
		pos.x += 5;
		_eDir = E_RIGHT;
		if (_eState != E_JUMP && _eState != E_FALL)
			_eState = E_MOVE;

	}
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		pos.x -= 5;
		_eDir = E_LEFT;
		if (_eState != E_JUMP && _eState != E_FALL)
			_eState = E_MOVE;

	}
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		pos.y += 2;

	}
	if (KEYMANAGER->isStayKeyDown('I'))
	{
		//pos.y -= 20;
		_eState = E_JUMP;

	}

	this->move(_maps);
	this->makingRc();
	
	if(!isDead)
		this->tileMapCollision(_maps);
	
	this->animation();
}

void RBenemy::animation()
{
	switch (_eDir)
	{
	case E_LEFT:
		if (count % frameSpeed == 0)
		{
			index++;
			if (index > _image[_eState]->getMaxFrameX())
			{
				index = 0;
			}

			_image[_eState]->setFrameX(index);
		}
		indexY = 0;

		break;

	case E_RIGHT:
		if (count % frameSpeed == 0)
		{
			index--;
			if (index < 0)
			{
				index = _image[_eState]->getMaxFrameX();
			}

			_image[_eState]->setFrameX(index);
		}
		indexY = 1;

		break;

	}


}
void RBenemy::makingRc()
{


	tileCollRc = RectMake(pos.x - _image[_eState]->getFrameWidth() / 16, pos.y, _image[_eState]->getFrameWidth() / 8, 10);

	realSizeRc = RectMakeCenter(pos.x, pos.y, _image[_eState]->getFrameWidth(), _image[_eState]->getFrameHeight());

	bottomTileCheckRc = RectMake(pos.x, pos.y + _image[_eState]->getFrameHeight() / 2, 2, 50);

	pixelRc = RectMake(pos.x, pos.y + _image[_eState]->getFrameHeight() / 2 - 5, 2, 50);

	topTileCheckRc = RectMake(pos.x, pos.y - _image[_eState]->getFrameHeight() / 2 - 2, 2, 2);

	if (_isAttacted)
	{
		damsY += -sinf(PI / 2) * 5;
		damsRc = RectMake(damsX , damsY, 15, 21);
	}
	else
		damsRc = RectMake(-100, -100, 15, 21);


	_currentTileX = realSizeRc.left / TILESIZE;
	_currentTileY = realSizeRc.top / TILESIZE;

	switch (_eState)
	{
	case E_IDLE:
		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 3) * TILEX;
		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 3) * TILEX;
		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 3) * TILEX;
		_collisionTileIndex[3] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[7] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[9] = _currentTileX + 1 + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[10] = _currentTileX + 2 + (_currentTileY - 1) * TILEX;


	case E_FALL:
		_collisionTileIndex[0] = _currentTileX + 1 + (_currentTileY)* TILEX;
		_collisionTileIndex[1] = _currentTileX + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[2] = _currentTileX + 1 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[3] = _currentTileX + 2 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[7] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[9] = _currentTileX + 1 + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[10] = _currentTileX + 2 + (_currentTileY - 1) * TILEX;

	case E_JUMP:
		_collisionTileIndex[0] = _currentTileX + 1 + (_currentTileY)* TILEX;
		_collisionTileIndex[1] = _currentTileX + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[2] = _currentTileX + 1 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[3] = _currentTileX + 2 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[7] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY)* TILEX;
		_collisionTileIndex[9] = _currentTileX + 1 + (_currentTileY)* TILEX;
		_collisionTileIndex[10] = _currentTileX + 2 + (_currentTileY)* TILEX;

	case E_MOVE:
		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 1) * TILEX;
		_collisionTileIndex[3] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[4] = _currentTileX + (_currentTileY)* TILEX;
		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY)* TILEX;
		_collisionTileIndex[6] = _currentTileX + 2 + (_currentTileY)* TILEX;
		_collisionTileIndex[7] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
		_collisionTileIndex[8] = _currentTileX + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[9] = _currentTileX + 1 + (_currentTileY - 1) * TILEX;
		_collisionTileIndex[10] = _currentTileX + 2 + (_currentTileY - 1) * TILEX;

	}

}

void RBenemy::move(stage_MAPt* _maps)
{
	if (isTrace && !_dontMove)
	{
		switch (_eState)
		{
		case IDLE:

			if (count % 200 == 0)
				_eState = E_MOVE;
			break;

		case E_MOVE:

			if (count % 400 < 200)
			{
				if (pos.x < _maps->getL_X() - speed)
					if (_eDir == LEFT)
						pos.x -= speed;
					else
						pos.x += speed;

			}
			else if (count % 400 < 400)
			{
				if (pos.x > speed)
					if (_eDir == LEFT)
						pos.x -= speed;
					else
						pos.x += speed;
			}




			if (count % jumpCount == 0 && _eType != FLOWER)
				_eState = E_JUMP;
			break;
		case E_JUMP:
			gravity += 0.3f;
			if (_isLRCollide)
			{
				pos.x += cosf(angle)*jumpSpeed * 0.2;
				pos.y += -sinf(angle)*jumpSpeed * 1.2f + gravity;

			}
			else
			{
				if (_eDir == LEFT)
				{
					pos.x += cosf(PI / 180 * 135)*jumpSpeed;
					pos.y += -sinf(PI / 180 * 135)*jumpSpeed + gravity;
				}
				else
				{
					pos.x += cosf(PI / 180 * 45)*jumpSpeed;
					pos.y += -sinf(PI / 180 * 45)*jumpSpeed + gravity;
				}


			}

			if (-sinf(angle)*jumpSpeed + gravity > 0)
			{
				_eState = E_FALL;

			}
			break;
		case E_FALL:
			if (isFall)
			{
				gravity += 0.3f;
				pos.y += gravity;
				if (pos.x > speed)
					if (_eDir == LEFT)
						pos.x -= speed;
					else
						pos.x += speed;
			}
			else if (_isHeadCollide)
			{
				gravity *= 0.95f;
				pos.y += 1 / gravity * 20;
			}
			else
			{
				gravity += 0.3f;
				pos.y += -sinf(angle)*jumpSpeed + gravity;

				if (_eDir == LEFT)
				{
					pos.x += cosf(PI / 180 * 135)*jumpSpeed;
					pos.y += -sinf(PI / 180 * 135)*jumpSpeed + gravity;

				}
				else
				{
					pos.x += cosf(PI / 180 * 45)*jumpSpeed;
					pos.y += -sinf(PI / 180 * 45)*jumpSpeed + gravity;

				}
			}
			/*
				if (count % 200 == 0)
					_eState = E_MOVE;*/
			break;

		case E_DEAD:

			if (pos.y < 720*4)
			{
				gravity += 0.3f;

				if (_eDir == LEFT)
				{
					pos.x += cosf(PI / 180 * 60)*10;
					pos.y += -sinf(PI / 180 * 60)* 10 + gravity;
				}
				else
				{
					pos.x += cosf(PI / 180 * 120)* 10;
					pos.y += -sinf(PI / 180 * 120)* 10 + gravity;
				}
			}
			else
				isActived = false;


			

		}
	}





}


void RBenemy::tileMapCollision(stage_MAPt* _maps)
{
	RECT _rct;

	for (int i = 8; i < 11; i++)
	{
		//»ó´ÜÃæµ¹
		if (IntersectRect(&_rct, &topTileCheckRc, &_maps->getTiles()[_collisionTileIndex[i]].rc) && _maps->getTiles()[_collisionTileIndex[i]].terrain == TR_GROUND)// && _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_DIAGONAL && _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF && _eState != E_JUMP && _eState != E_FALL)
		{
			_eState = E_FALL;
			tileCollRc.top = _maps->getTiles()[_collisionTileIndex[i]].rc.bottom;
			tileCollRc.bottom = _maps->getTiles()[_collisionTileIndex[i]].rc.bottom + _image[_eState]->getFrameHeight();
			pos.y = tileCollRc.top + (tileCollRc.bottom - tileCollRc.top) / 2;
			_isHeadCollide = true;
		}
	}



	for (int i = 4; i < 7; i++)
	{
		if (IntersectRect(&_rct, &tileCollRc, &_maps->getTiles()[_collisionTileIndex[i]].rc) 
			&& !_maps->getCanPass()[_collisionTileIndex[i]]
			&& (_eState == MOVE || _eState == FALL || _eState == JUMP) 
			&& _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF)
		{
			//	//ÁÂ¿ìÃæµ¹

			switch (_eDir)
			{
			case E_LEFT:
				rc.left = _maps->getTiles()[_collisionTileIndex[i]].rc.right;
				rc.right = _maps->getTiles()[_collisionTileIndex[i]].rc.right + _image[_eState]->getFrameWidth() / 8;
				pos.x = rc.left + (rc.right - rc.left) / 2;
				_isLRCollide = true;
				_eState = E_JUMP;
				break;

			case E_RIGHT:
				rc.right = _maps->getTiles()[_collisionTileIndex[i]].rc.left;
				rc.left = _maps->getTiles()[_collisionTileIndex[i]].rc.left - _image[_eState]->getFrameWidth() / 8;
				pos.x = rc.left + (rc.right - rc.left) / 2;// +100;
				_isLRCollide = true;
				_eState = E_JUMP;
				break;

			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		//ÇÏ´ÜÃæµ¹
		RECT _rct;
		if (IntersectRect(&_rct, &bottomTileCheckRc, &_maps->getTiles()[_collisionTileIndex[i]].rc) 
			&& !_maps->getCanPass()[_collisionTileIndex[i]] 
			&& (_maps->getTiles()[_collisionTileIndex[i]].terrain == TR_GROUND || _maps->getTiles()[_collisionTileIndex[i]].terrain == TR_ROOF) 
			&& _eState != E_JUMP)
		{
			pos.y = _maps->getTiles()[_collisionTileIndex[i]].rc.top - _image[_eState]->getFrameHeight() / 2;
			_eState = E_MOVE;
			_isLRCollide = false;
			jumpSpeed = 10.f;

			gravity = 0;
			isFall = false;

		}
	}


	for (int i = 0; i < 3; i++)
	{
		//Ãß¶ôÃæµ¹
		RECT _rct;
		if (IntersectRect(&_rct, &bottomTileCheckRc, &_maps->getTiles()[_collisionTileIndex[i]].rc) && _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_GROUND && _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_DIAGONAL && _maps->getTiles()[_collisionTileIndex[i]].terrain != TR_ROOF && _eState != E_JUMP && _eState != E_FALL)
		{
			if (_eState != E_JUMP)
				_eState = E_FALL;
			isFall = true;
		}
	}



	for (int i = 0; i < 7; i++)
	{
		//»ç¼±Ãæµ¹
		RECT _rct;
		if (IntersectRect(&_rct, &pixelRc, &_maps->getTiles()[_collisionTileIndex[i]].rc) && _maps->getTiles()[_collisionTileIndex[i]].terrain == TR_DIAGONAL && _eState != E_JUMP)
		{
			for (int j = 0; j < 64; j++)
			{
				COLORREF color = GetPixel(_maps->getTileImage(_maps->getTiles()[_collisionTileIndex[i]].tileType, _maps->getTiles()[_collisionTileIndex[i]].reverse)->getMemDC(), _maps->getTiles()[_collisionTileIndex[i]].terrainFrameX * 64 + (pos.x - _maps->getTiles()[_collisionTileIndex[i]].rc.left), _maps->getTiles()[_collisionTileIndex[i]].terrainFrameY * 64 + j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (!(r == 255 && g == 0 && b == 255))
				{

					pos.y = _maps->getTiles()[_collisionTileIndex[i]].rc.top + j - _image[_eState]->getFrameHeight() / 2 + 6;// -(_yerina.pixelRc.top - _stage1_map->getTiles()[_tileIndex[i]].rc.top) - 64);

					//tileCollRc = RectMakeCenter(pos.x + speed, pos.y, 2, _image[_eState]->getFrameHeight());
					tileCollRc = RectMake(pos.x - _image[_eState]->getFrameWidth() / 16 + speed, pos.y, _image[_eState]->getFrameWidth() / 8, 10);
					break;

				}
			}
		}
	}




}




// ¹ö¼¸ 1
void mushRoom::init()
{
	_eType = MUSHROOM;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 5.0f;
	jumpSpeed = 10.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 70;
	indexY = index = count = 0;
	frameSpeed = 10;
	jumpCount = 50;


	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("¹ö¼¸MOVE", "resource/enemy/¹ö¼¸MOVE.bmp", 150, 100, 3, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("¹ö¼¸MOVE", "resource/enemy/¹ö¼¸MOVE.bmp", 150, 100, 3, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("¹ö¼¸MOVE", "resource/enemy/¹ö¼¸MOVE.bmp", 150, 100, 3, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("¹ö¼¸MOVE", "resource/enemy/¹ö¼¸MOVE.bmp", 150, 100, 3, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("¹ö¼¸BEATTACTED", "resource/enemy/¹ö¼¸DEAD.bmp", 50, 100, 1, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("¹ö¼¸DEAD", "resource/enemy/¹ö¼¸DEAD.bmp", 50, 100, 1, 2);

	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;


	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}
// °­¾ÆÁö 2
void puppy::init()
{
	_eType = PUPPY;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 3.0f;
	jumpSpeed = 10.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 80;

	indexY = index = count = 0;
	frameSpeed = 5;
	jumpCount = 200;

	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöMOVE", "resource/enemy/°­¾ÆÁöMOVE.bmp", 240, 100, 4, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöMOVE", "resource/enemy/°­¾ÆÁöMOVE.bmp", 240, 100, 4, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöMOVE", "resource/enemy/°­¾ÆÁöMOVE.bmp", 240, 100, 4, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöMOVE", "resource/enemy/°­¾ÆÁöMOVE.bmp", 240, 100, 4, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöBEATTACTED", "resource/enemy/°­¾ÆÁöDEAD.bmp", 60, 100, 1, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("°­¾ÆÁöDEAD", "resource/enemy/°­¾ÆÁöDEAD.bmp", 60, 100, 1, 2);

	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;


	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}
// Åä³¢ 3
void rabbit::init()
{
	_eType = RABBIT;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 2.0f;
	jumpSpeed = 10.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 110;

	indexY = index = count = 0;
	frameSpeed = 7;
	jumpCount = 30;

	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("Åä³¢IDLE", "resource/enemy/Åä³¢IDLE.bmp", 70, 125, 1, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("Åä³¢MOVE", "resource/enemy/Åä³¢MOVE.bmp", 350, 125, 5, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("Åä³¢MOVE", "resource/enemy/Åä³¢MOVE.bmp", 350, 125, 5, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("Åä³¢MOVE", "resource/enemy/Åä³¢MOVE.bmp", 350, 125, 5, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("Åä³¢BEATTACTED", "resource/enemy/Åä³¢DEAD.bmp", 140, 125, 2, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("Åä³¢DEAD", "resource/enemy/Åä³¢DEAD.bmp", 140, 125, 2, 2);


	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;

	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}
//void rabbit::makingRc()
//{
//	rc = RectMake(pos.x, pos.y, 50, 50);
//
//	tileCollRc = RectMakeCenter(pos.x, pos.y, _image[_eState]->getFrameWidth(), _image[_eState]->getFrameHeight());
//
//	bottomTileCheckRc = RectMakeCenter(pos.x, pos.y + _image[_eState]->getFrameHeight()/2, 10, 20);
//
//	pixelRc = RectMake(pos.x, pos.y + _image[_eState]->getFrameHeight() / 2 - 5, 2, 50);
//
//
//
//
//	_currentTileX = tileCollRc.left / TILESIZE;
//	_currentTileY = tileCollRc.top / TILESIZE;
//
//	switch (_eState)
//	{
//	case E_IDLE:
//		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 3) * TILEX;
//		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 3) * TILEX;
//		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 3) * TILEX;
//		_collisionTileIndex[3] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//	case E_FALL:
//		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[3] = _currentTileX - 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//	case E_JUMP:
//		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[3] = _currentTileX + 1 + (_currentTileY)* TILEX;
//		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[5] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 2) * TILEX;
//	case E_MOVE:
//		_collisionTileIndex[0] = _currentTileX + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[1] = _currentTileX + 1 + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[2] = _currentTileX + 2 + (_currentTileY + 1) * TILEX;
//		_collisionTileIndex[3] = _currentTileX + (_currentTileY + 2)* TILEX;
//		_collisionTileIndex[4] = _currentTileX + 1 + (_currentTileY + 2)* TILEX;
//		_collisionTileIndex[5] = _currentTileX + 2 + (_currentTileY + 2)* TILEX;
//		_collisionTileIndex[6] = _currentTileX + 1 + (_currentTileY + 3) * TILEX;
//
//	}
//}
// º´¾Æ¸® 4
void chick::init()
{
	_eType = CHICK;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 4.0f;
	jumpSpeed = 10.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 15;

	indexY = index = count = 0;
	frameSpeed = 10;

	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®MOVE", "resource/enemy/º´¾Æ¸®MOVE.bmp", 325, 70, 5, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®MOVE", "resource/enemy/º´¾Æ¸®MOVE.bmp", 325, 70, 5, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®MOVE", "resource/enemy/º´¾Æ¸®MOVE.bmp", 325, 70, 5, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®MOVE", "resource/enemy/º´¾Æ¸®MOVE.bmp", 325, 70, 5, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®BEATTACTED", "resource/enemy/º´¾Æ¸®DEAD.bmp", 65, 70, 1, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("º´¾Æ¸®DEAD", "resource/enemy/º´¾Æ¸®DEAD.bmp", 65, 70, 1, 2);


	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;

	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}
// ´Ù¶÷Áã 5
void chipmunk::init()
{
	_eType = CHIPMUNK;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 7.0f;
	jumpSpeed = 10.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 150;

	indexY = index = count = 0;
	frameSpeed = 10;
	jumpCount = 500;

	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãIDLE", "resource/enemy/´Ù¶÷ÁãIDLE.bmp", 180, 100, 3, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãMOVE", "resource/enemy/´Ù¶÷ÁãMOVE.bmp", 480, 100, 8, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãMOVE", "resource/enemy/´Ù¶÷ÁãMOVE.bmp", 480, 100, 8, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãMOVE", "resource/enemy/´Ù¶÷ÁãMOVE.bmp", 480, 100, 8, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãBEATTACTED", "resource/enemy/´Ù¶÷ÁãDEAD.bmp", 60,100, 1, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("´Ù¶÷ÁãDEAD", "resource/enemy/´Ù¶÷ÁãDEAD.bmp", 60, 100, 1, 2);


	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;

	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}

// ²É 6
void flower::init()
{
	_eType = FLOWER;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 0.0f;
	jumpSpeed = 0.0f;
	angle = PI / 2;
	gravity = 0;
	hp = 15;

	indexY = index = count = 0;
	frameSpeed = 10;

	_image[E_IDLE] = IMAGEMANAGER->addFrameImage("²ÉIDLE", "resource/enemy/²ÉIDLE.bmp", 400, 160, 5, 2);
	_image[E_MOVE] = IMAGEMANAGER->addFrameImage("²ÉIDLE", "resource/enemy/²ÉATTACT.bmp", 400, 160, 5, 2);
	_image[E_JUMP] = IMAGEMANAGER->addFrameImage("²ÉIDLE", "resource/enemy/²ÉIDLE.bmp", 400, 160, 5, 2);
	_image[E_FALL] = IMAGEMANAGER->addFrameImage("²ÉIDLE", "resource/enemy/²ÉIDLE.bmp", 400, 160, 5, 2);
	_image[E_BEATTACTED] = IMAGEMANAGER->addFrameImage("²ÉBEATTACTED", "resource/enemy/²ÉDEAD.bmp", 80, 160, 1, 2);
	_image[E_DEAD] = IMAGEMANAGER->addFrameImage("²ÉDEAD", "resource/enemy/²ÉDEAD.bmp", 80, 160, 1, 2);


	//ÇÇ°Ý½Ã
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;

	isFall = false;
	_isHeadCollide = false;
	_isLRCollide = false;

	isTrace = false;
	isActived = true;
	isDead = false;

}
// ¹ú 7 (¿¡ÀÌ½ºÅ¸¸¦ ? )
void bee::init()
{
	_eType = BEE;
	_eState = E_IDLE;
	_eDir = E_LEFT;

	pos.x = pos.y = 500;
	speed = 3.0f;
	jumpSpeed = 5.0f;
	angle = PI / 2;
	gravity = 0;

	indexY = index = count = 0;
	frameSpeed = 10;

	_image[0] = IMAGEMANAGER->addFrameImage("¹úMOVE", "resource/enemy/¹úMOVE.bmp", 280, 140, 4, 2);

	isActived = true;
}
// ´«µ¿ÀÚ
void eyes::init()
{
}
// µÅÁö
void pig::init()
{
}
// °í¾çÀÌ
void cat::init()
{
}
//Ä¸½¶
void capsule::init()
{
}
//¸¶¹ýºÀ¼Ò³à
void magicStick::init()
{
}
