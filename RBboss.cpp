#include "stdafx.h"
#include "RBboss.h"
#include "yerinaT.h"

void RBboss::init()
{
}
void RBboss::release()
{
}

void RBboss::update()
{
}

void RBboss::animation()
{
}

void RBboss::move()
{
}

void RBboss::attactPattern()
{
}

void RBboss::fire()
{
}


		///////////
		//��������//
		///////////

void ribbonBoss::init()
{
	//�Ѿ��׽�Ʈ

	_blueBullet = new ribbonBlueBullet;
	_blueBullet->init();

	_blueRain = new ribbonBlueRain;
	_blueRain->init();

	_sunFlower = new ribbonYellowBlue;
	_sunFlower->init();

	_spiderWeb = new ribbonSpiderWeb;
	_spiderWeb->init();

	bulletIndex = 0;
	gauge = 0;


	_bType = RIBBON_BOSS;
	_bState = IDLE;
	_bDir = LEFT;
	//_bState = (STATE)0;
	pos.x = 1150;
	pos.y = 720 - 64 * 2;

	fixPos.x = 0;
	fixPos.y = 0;

	speed = 3.f;
	jumpSpeed = 0;
	angle = 0;
	gravity = 0;

	index = count = chargeIndex = 0;
	frameSpeed = 5;

	maxHp = 1500;
	currentHp = 50;

	maxPhase = 0;
	currentPhase = 1;
	isAttacting = false;
	isStartBattle = false;
	isReady = true;

	//�ǰݽ�
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;
	
	stopTime = 0;
	stayCount = 0;
	skillTemp = 0;

	//isAttact[READY] = true;
	for (int i = 1; i < RIBBONSKILLEND; i++)
	{
		isAttact[i] = false;
	}
	isStopped = false;


	_image[IDLE] = IMAGEMANAGER->addFrameImage("����IDLE", "resource/player/����IDLE.bmp", 384, 192, 4, 2);
	_image[MOVE] = IMAGEMANAGER->addFrameImage("����IDLE", "resource/player/����IDLE.bmp", 384, 192, 4, 2);
	_image[BEATTACTED] = IMAGEMANAGER->addFrameImage("����BEATTACTED", "resource/player/����BEATTACTED.bmp", 384, 192, 4, 2);
	_image[DEAD] = IMAGEMANAGER->addFrameImage("����DEAD", "resource/player/����DEAD.bmp", 768, 192, 8, 2);
	_image[ATTACT1] = IMAGEMANAGER->addFrameImage("����ATTACT1", "resource/player/����ATTACT1.bmp", 384, 192, 4, 2);
	_image[ATTACT2] = IMAGEMANAGER->addFrameImage("����ATTACT2", "resource/player/����ATTACT2.bmp", 480, 192, 5, 2);

	//�Ѿ�
	_chargingImg[0] = GDIPLUS->addFrameImage("����Ѿ�����", "resource/bullet/����Ѿ�����.png", 0, 0, 10, 1);
	_chargingImg[1] = GDIPLUS->addFrameImage("������", "resource/bullet/������.png", 0, 0, 10, 1);
	_chargingImg[2] = GDIPLUS->addFrameImage("�ö������", "resource/bullet/�ö������.png", 0, 0, 10, 1);
	_chargingImg[3] = GDIPLUS->addFrameImage("�����̴�����", "resource/bullet/�����̴�����.png", 0, 0, 10, 1);

	for (int i = 0; i < 4; i++)
		isCharging[i] = false;

	fixSite = false;
	isDead = false;
}

void ribbonBoss::release()
{
	SAFE_DELETE(_blueBullet);
	SAFE_DELETE(_blueRain);
	SAFE_DELETE(_sunFlower);
	SAFE_DELETE(_spiderWeb);
}


void ribbonBoss::update()
{
	count++;

	if (!isDead)
	{
		this->move();
	}
		_blueBullet->update();
		_blueRain->update();
		_sunFlower->update();
		_spiderWeb->update();

	this->animation();

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		currentHp -= 10;
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		currentHp += 10;
	}
}

void ribbonBoss::move()
{
	this->attactPattern();

	for (int i = 0; i < RIBBONSKILLEND; ++i)
	{
		if (isAttact[i])
		{
			this->attact(i);
			break;
		}
	}
	
	if (isStopped)
	{
		stopTime++;
		if (stopTime > 10)
		{
			isStopped = false;
			stopTime = 0;
		}
	}

	rc = RectMakeCenter(pos.x, pos.y, 96, 96);
	
	//������Ʈ
	if (_isAttacted)
	{
		_bState = BEATTACTED;
		damsY += -sinf(PI / 2) * 5;
		damsRc = RectMake(damsX, damsY, 15, 21);
	}
	else
		damsRc = RectMake(-100, -100, 15, 21);
}

void ribbonBoss::attactPattern()
{
	if (isReady)
	{
		maxPhase = 0;
	}
	else
	{

		if (currentHp == maxHp) // �޸���
			maxPhase = 1;
		else if (currentHp > maxHp * 0.99) // �Ϲ� ���� (�Ϸη�)
			maxPhase = 2;
		else if (currentHp > maxHp * 0.8) // �Ķ� ���� ���
			maxPhase = 3;
		else if (currentHp > maxHp * 0.6) // ��
			maxPhase = 4;
		else if (currentHp > maxHp * 0.4) // �ö��
			maxPhase = 5;
		else if (currentHp > maxHp * 0.2) // ������
			maxPhase = 6; 
		else if (currentHp > 0) // ������
			maxPhase = 7;
	}
	
	if (!isAttacting && isStartBattle && !isReady && maxPhase > 0 )// 0~4 ���� ����
	{
		if (currentPhase > maxPhase - 1)
			currentPhase = 1;

		fixPos.x = _player->getX();
		fixPos.y = _player->getY();

		isAttact[currentPhase] = true;
		isAttacting = true;

		currentPhase++;
	}
}

void ribbonBoss::fire()
{
}

void ribbonBoss::attact(int _curPhase)
{
	switch (_curPhase)
	{
	case STAY:
		this->stay();
		break;
	case BODYRUSH: // �����ġ��
		this->bodyRush();
		break;
	case BBYORORONG: // �Ƿηս��
		this->bbyororong();
		break;
	case BLUERAIN: // ���������
		this->blueRain();
		break;
	case SUNBEAM: // ��� �Ķ� ���� ���
		this->sunBeam();
		break;
	case FLOWERBEAM: // �ʷ� �ֶ��
		this->flowerBeam();
		break;
	case SPIDERWEB:
		this->spiderWeb();
		break;
	default:
		break;
	}

}

void ribbonBoss::stay()
{
	stayCount++;
	_bState = IDLE;

	if (stayCount > 40)
	{
		isAttacting = false;
		isAttact[STAY] = false;
		stayCount = 0;
		for(int i = 0 ; i < 4 ; i ++)
			isCharging[i] = false;
	}
}

void ribbonBoss::bodyRush()
{
	if (!fixSite)
	{
		if (pos.x < fixPos.x - 10 || pos.x > fixPos.x + 10)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY - 64 * 2);

			pos.x += cosf(moveAngle)*speed * 3;
			pos.y += -sinf(moveAngle)*speed * 3;
		}
		else
			fixSite = true;
	}
	else
	{
		if (!isStopped)
		{
			if (_bDir == LEFT)
				pos.x -= speed * 4.0f;
			else
				pos.x += speed * 4.0f;
		}

		if (pos.x < 200)
		{
			_bDir = RIGHT;
			//isAttacting = false;
			isAttact[BODYRUSH] = false;
			isAttact[STAY] = true;
			isStopped = true;
		}
		else if (pos.x > 1080)
		{
			_bDir = LEFT;
			//isAttacting = false;
			isAttact[BODYRUSH] = false;
			isAttact[STAY] = true;
			isStopped = true;
		}
	}
}

void ribbonBoss::bbyororong()
{
	if (_player->getX() > pos.x)
		_bDir = RIGHT;
	else if (_player->getX() < pos.x)
		_bDir = LEFT;

	if (!fixSite)
	{
		if (pos.x < fixPos.x - 10 || pos.x > fixPos.x + 10)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY - 64*2);

			pos.x += cosf(moveAngle)*speed * 3;
			pos.y += -sinf(moveAngle)*speed * 3;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT1;
		gauge++;
		isCharging[0] = true;
		if (gauge == 100)
		{
			_blueBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������Ѿ����̾�", SAVEDATA->getEffSound());
			chargeCount = 40;
			isCharging[0] = false;
			chargeIndex = 0;
		}
		if(gauge == 160)
		{
			gauge = 0;
			isAttact[BBYORORONG] = false;
			isAttact[STAY] = true;
			fixSite = false;
		}
	}
	

}

void ribbonBoss::blueRain()
{
	if (!fixSite)
	{
		if (pos.y < WINSIZEY/3 - 30 || pos.y > WINSIZEY / 3 + 30)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY / 3);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[0] = true;

		if (gauge == 100)
		{
			_blueRain->fire(pos.x, pos.y, _bDir);
		}
		if (gauge == 200)
		{
			isCharging[0] = false;
			gauge = 0;
			chargeIndex = 0;
			isAttact[BLUERAIN] = false;
			isAttact[STAY] = true;
			fixSite = false;
		}
	}
}

void ribbonBoss::sunBeam()
{
	if (!fixSite)
	{
		if (pos.x < fixPos.x - 30 || pos.x > fixPos.x + 30)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY / 4);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[1] = true;

		if (gauge > 250)
		{
			isCharging[1] = false;
		}
		if (gauge == 250)
		{
			_sunFlower->fire_yellows(pos.x, pos.y, 0);
			SOUNDMANAGER->play("�������Ѿ����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 270)
		{
			_sunFlower->fire_yellows(pos.x, pos.y, 1);
			SOUNDMANAGER->play("�������Ѿ����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 290)
		{
			_sunFlower->fire_yellows(pos.x, pos.y, 2);
			SOUNDMANAGER->play("�������Ѿ����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 500)
		{
			gauge = 0;
			chargeIndex = 0;
			isAttact[SUNBEAM] = false;
			isAttact[STAY] = true;
			fixSite = false;
		}
	}
}

void ribbonBoss::flowerBeam()
{
	if (!fixSite)
	{
		if (pos.x < fixPos.x - 30 || pos.x > fixPos.x + 30)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY / 3);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;
		isCharging[2] = true;
		if (gauge >= 199)
			isCharging[2] = false;
		if (gauge == 200)
		{
			_sunFlower->fire_flower(pos.x, pos.y, 0);
			chargeIndex = 0;
		}
		else if (gauge == 700)
		{
			gauge = 0;
			isAttact[STAY] = true;
			isAttact[FLOWERBEAM] = false;
			fixSite = false;
		}
	}
}

void ribbonBoss::spiderWeb()
{
	if (!fixSite)
	{
		if (pos.x < fixPos.x - 30 || pos.x > fixPos.x + 30)
		{
			float moveAngle = getAngle(pos.x, pos.y, fixPos.x, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY / 2);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[3] = true;

		if (gauge >= 199)
			isCharging[3] = false;


		if (gauge == 200)
		{
			_spiderWeb->fire(pos.x, pos.y, 0);
			SOUNDMANAGER->play("�����Ź������̾�", SAVEDATA->getEffSound());
			chargeIndex = 0;

		}
		else if (gauge == 900)
		{
			gauge = 0;
			isAttact[STAY] = true;
			isAttact[SPIDERWEB] = false;
			fixSite = false;
		}
	}

}




void ribbonBoss::animation()
{
	if (_bState == DEAD)
	{
		frameSpeed = 20;
		for (int i = 0; i < 4; i++)
			isCharging[i] = false;
	}
	if (_bDir == LEFT)
	{
		if (count % frameSpeed == 0)
		{
			index++;
			if (index > _image[_bState]->getMaxFrameX())
			{
				index = 0;
				if(_bState==DEAD)
					index = _image[_bState]->getMaxFrameX();
			}
		}
	}
	else
	{
		if (count % frameSpeed == 0)
		{
			index--;
			if (index < 0)
			{
				index = _image[_bState]->getMaxFrameX();
				if (_bState == DEAD)
					index = 0;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (isCharging[i])
		{
			if (count % 5 == 0)
			{
				chargeIndex++;
				if (chargeIndex > 9)
				{
					if(i==0)
						SOUNDMANAGER->play("������¡",SAVEDATA->getEffSound());
					else
						SOUNDMANAGER->play("������¡2", SAVEDATA->getEffSound());
					chargeIndex = 0;
				}
			}
		}
	}

	
}




















































void finalBoss::init()
{
	//�Ѿ��׽�Ʈ

	_guidedBullet = new guided_bullet;
	_guidedBullet->init();
	_guidedBullet->setPlayerLink(_player);

	_tornadoBullet = new tornado_bullet;
	_tornadoBullet->init();

	_snakeBullet = new snake_bullet;
	_snakeBullet->init();

	_polygonBullet = new polygon_bullet;
	_polygonBullet->init();

	_octopusBullet = new octopus_bullet;
	_octopusBullet->init();
		
	_ballBullet = new ball_bullet;
	_ballBullet->init();
		

	bulletIndex = 0;
	gauge = 0;


	_bType = FINAL_BOSS;
	_bState = IDLE;
	_bDir = RIGHT;
	//_bState = (STATE)0;
	pos.x = 300;
	pos.y = 720 - 185;

	fixPos.x = 0;
	fixPos.y = 0;

	speed = 3.f;
	jumpSpeed = 0;
	angle = 0;
	gravity = 0;

	index = count = chargeIndex = 0;
	frameSpeed = 10;

	maxHp = 4000;
	currentHp = 100;

	maxPhase = 0;
	currentPhase = 1;
	isAttacting = false;
	isStartBattle = false;
	isReady = true;

	//�ǰݽ�
	_isAttacted = false;
	_dontMove = false;
	invincibleStateCount = 0;
	invincibleAlpha = 0;

	stopTime = 0;
	stayCount = 0;
	skillTemp = 0;

	//isAttact[READY] = true;
	for (int i = 1; i < FINALBOSSSKILLEND; i++)
	{
		isAttact[i] = false;
	}
	isStopped = false;


	_image[IDLE] = IMAGEMANAGER->addFrameImage("��������IDLE", "resource/boss/��������IDLE.bmp", 800, 400, 4, 2);
	_image[MOVE] = IMAGEMANAGER->addFrameImage("��������MOVE", "resource/boss/��������MOVE.bmp", 1000, 400, 5, 2);
	_image[BEATTACTED] = IMAGEMANAGER->addFrameImage("��������BEATTACTED", "resource/boss/��������BEATTACTED.bmp", 400, 400, 2, 2);
	_image[DEAD] = IMAGEMANAGER->addFrameImage("��������DEAD", "resource/boss/��������DEAD.bmp", 1000, 400, 5, 2);
	_image[ATTACT1] = IMAGEMANAGER->addFrameImage("��������ATTACT1", "resource/boss/��������ATTACT.bmp", 2000, 400, 10, 2);
	_image[ATTACT2] = IMAGEMANAGER->addFrameImage("��������ATTACT2", "resource/boss/��������ATTACT.bmp", 2000, 400, 10, 2);

	////�Ѿ�
	//_chargingImg[0] = GDIPLUS->addFrameImage("����Ѿ�����", "resource/bullet/����Ѿ�����.png", 0, 0, 10, 1);
	//_chargingImg[1] = GDIPLUS->addFrameImage("������", "resource/bullet/������.png", 0, 0, 10, 1);
	//_chargingImg[2] = GDIPLUS->addFrameImage("�ö������", "resource/bullet/�ö������.png", 0, 0, 10, 1);
	//_chargingImg[3] = GDIPLUS->addFrameImage("�����̴�����", "resource/bullet/�����̴�����.png", 0, 0, 10, 1);

	for (int i = 0; i < 4; i++)
		isCharging[i] = false;

	fixSite = false;
	isDead = false;
}

void finalBoss::release()
{
	SAFE_DELETE(_guidedBullet);
	SAFE_DELETE(_tornadoBullet);
	SAFE_DELETE(_snakeBullet);
	SAFE_DELETE(_polygonBullet);
	SAFE_DELETE(_octopusBullet);
	SAFE_DELETE(_ballBullet);


}


void finalBoss::update()
{
	count++;

	if (!isDead)
	{
		this->move();
	}
	_guidedBullet->update();
	_tornadoBullet->update();
	_snakeBullet->update();
	_polygonBullet->update();
	_octopusBullet->update();
	_ballBullet->update();


	this->animation();

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		currentHp -= 10;
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		currentHp += 10;
	}
}

void finalBoss::move()
{
	this->attactPattern();

	for (int i = 0; i < FINALBOSSSKILLEND; ++i)
	{
		if (isAttact[i])
		{
			this->attact(i);
			break;
		}
	}

	if (isStopped)
	{
		stopTime++;
		if (stopTime > 10)
		{
			isStopped = false;
			stopTime = 0;
		}
	}

	rc = RectMakeCenter(pos.x, pos.y, 100, 100);

	//������Ʈ
	if (_isAttacted)
	{
		_bState = BEATTACTED;
		damsY += -sinf(PI / 2) * 5;
		damsRc = RectMake(damsX, damsY, 15, 21);
	}
	else
		damsRc = RectMake(-100, -100, 15, 21);
}

void finalBoss::attactPattern()
{
	if (isReady)
	{
		maxPhase = 0;
	}
	else
	{
		if (currentHp == maxHp) // �޸���
			maxPhase = 1;
		else if (currentHp > maxHp * 0.99) // �Ϲ� ���� (�Ϸη�)
			maxPhase = 2;
		else if (currentHp > maxHp * 0.8) // �Ķ� ���� ���
			maxPhase = 3;
		else if (currentHp > maxHp * 0.6) // ��
			maxPhase = 4;
		else if (currentHp > maxHp * 0.4) // �ö��
			maxPhase = 5;
		else if (currentHp > maxHp * 0.2) // ������
			maxPhase = 6;
		else if (currentHp > 0) // ������
			maxPhase = 7;
	}

	if (!isAttacting && isStartBattle && !isReady && maxPhase > 0)// 0~4 ���� ����
	{
		if (currentPhase > maxPhase - 1)
			currentPhase = 1;

		fixPos.x = _player->getX();
		fixPos.y = _player->getY();

		isAttact[currentPhase] = true;
		isAttacting = true;

		currentPhase++;
	}
}

void finalBoss::fire()
{
}

void finalBoss::attact(int _curPhase)
{
	switch (_curPhase)
	{
	case F_STAY:
		this->stay();
		break;
	case GUIDEDMISSILE: // ����ź
		this->guidedMissile();
		break;
	case TORNADO: // ȸ����
		this->tornado();
		break;
	case SNAKE: // ������ũ
		this->snake();
		break;
	case POLYGON: // �ٰ���
		this->polygon();
		break;
	case OCTOPUS: // �����ϱ�
		this->octopus();
		break;
	case BALL: // ���乮��
		this->ball();

		break;
	default:
		break;
	}

}

void finalBoss::stay()
{
	stayCount++;
	_bState = IDLE;

	if (stayCount > 40)
	{
		isAttacting = false;
		isAttact[F_STAY] = false;
		stayCount = 0;
		for (int i = 0; i < 4; i++)
			isCharging[i] = false;
	}
}

void finalBoss::guidedMissile()
{
		if (!fixSite)
		{
			if (pos.x < WINSIZEX/2 - 10 || pos.x > WINSIZEX/2 + 10)
			{
				float moveAngle = getAngle(pos.x, pos.y, WINSIZEX/2, CAMERAMANAGER->getVCam("�÷��̾�ī�޶�")[0].rc.top + WINSIZEY/6);

				pos.x += cosf(moveAngle)*speed * 3;
				pos.y += -sinf(moveAngle)*speed * 3;
			}
			else
				fixSite = true;
		}
		else
		{
			_bState = ATTACT1;
			gauge++;
			isCharging[0] = true;

			if (gauge == 100)
			{
				_guidedBullet->fire(pos.x, pos.y, _bDir);
			}
			if (gauge == 800)
			{
				isCharging[0] = false;
				gauge = 0;
				chargeIndex = 0;
				//	isAttacting = false;
				isAttact[GUIDEDMISSILE] = false;
				isAttact[F_STAY] = true;
				fixSite = false;
			}
		}
}

void finalBoss::tornado()
{
	//pos.x += 1;
	//if (_player->getX() > pos.x)
	//	_bDir = RIGHT;
	//else if (_player->getX() < pos.x)
	//	_bDir = LEFT;

	if (!fixSite)
	{
		if (pos.x < 90 || pos.x > 110)
		{
			float moveAngle = getAngle(pos.x, pos.y, 100, 450);

			pos.x += cosf(moveAngle)*speed * 3;
			pos.y += -sinf(moveAngle)*speed * 3;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT1;
		gauge++;
		isCharging[0] = true;

		if (gauge == 100) //1
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 180) //2
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 260) //3
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 340) //4
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 420) //5
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 500) //6
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 580) //7 
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 660) //8 
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 740) //9 
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		else if (gauge == 820) //10
		{
			_tornadoBullet->fire(pos.x, pos.y, _bDir);
			SOUNDMANAGER->play("��������̵����̾�", SAVEDATA->getEffSound());

		}
		if (gauge == 1300)
		{
			isCharging[0] = false;
			gauge = 0;
			chargeIndex = 0;
			//	isAttacting = false;
			isAttact[TORNADO] = false;
			isAttact[F_STAY] = true;
			fixSite = false;
		}
	}


}

void finalBoss::snake()
{

	if (!fixSite)
	{
		if (pos.x < WINSIZEX / 2-10 || pos.x > WINSIZEX / 2 +10)
		{
			float moveAngle = getAngle(pos.x, pos.y, WINSIZEX / 2, 400);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[0] = true;

		if (gauge == 100)
		{
			_snakeBullet->fire(pos.x, pos.y, _bDir);
		}
		else if (gauge == 200)
		{
			_snakeBullet->fire(pos.x, pos.y, _bDir);
		}
		else if (gauge == 300)
		{
			_snakeBullet->fire(pos.x, pos.y, _bDir);
		}
		else if (gauge == 400)
		{
			_snakeBullet->fire(pos.x, pos.y, _bDir);
		}
		else if (gauge == 500)
		{
			_snakeBullet->fire(pos.x, pos.y, _bDir);
		}
		if (gauge == 1500)
		{
			isCharging[0] = false;
			gauge = 0;
			chargeIndex = 0;
			isAttact[SNAKE] = false;
			isAttact[F_STAY] = true;
			fixSite = false;
		}
	}
}

void finalBoss::polygon()
{
	
	if (!fixSite)
	{
		if (pos.x < WINSIZEX / 2 - 80 - 10 || pos.x > WINSIZEX / 2 - 80 + 10)
		{
			float moveAngle = getAngle(pos.x, pos.y, WINSIZEX/2 - 80, WINSIZEY/2);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[1] = true;

		if (gauge > 250)
		{
			isCharging[1] = false;
		}
		if (gauge == 250)
		{
			_polygonBullet->fire(pos.x, pos.y, _bDir);
		}

		if(gauge == 2800)
		{
			gauge = 0;
			chargeIndex = 0;
			isAttact[POLYGON] = false;
			isAttact[F_STAY] = true;
			fixSite = false;
		}
	}
}

void finalBoss::octopus()
{
	if (!fixSite)
	{
		if (pos.x < WINSIZEX / 4 - 80 - 10 || pos.x > WINSIZEX / 4 - 80 + 10)
		{
			float moveAngle = getAngle(pos.x, pos.y, WINSIZEX / 4 - 80, WINSIZEY / 2);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;
		isCharging[2] = true;
		if (gauge >= 199)
			isCharging[2] = false;
		if (gauge == 200)
		{
			_octopusBullet->fire(pos.x, pos.y, 0);
			chargeIndex = 0;
		}
		else if (gauge == 2300)
		{
			gauge = 0;
			isAttact[F_STAY] = true;
			isAttact[OCTOPUS] = false;
			fixSite = false;
		}
	}
}

void finalBoss::ball()
{
	
	if (!fixSite)
	{
		if (pos.x < 300 - 30 || pos.x > 300 + 30)
		{
			float moveAngle = getAngle(pos.x, pos.y, 300, 450);

			pos.x += cosf(moveAngle)*speed * 2;
			pos.y += -sinf(moveAngle)*speed * 2;
		}
		else
			fixSite = true;
	}
	else
	{
		_bState = ATTACT2;
		gauge++;

		isCharging[3] = true;

		if (gauge >= 199)
			isCharging[3] = false;


		if (gauge == 200)
		{
			_ballBullet->fire(pos.x, pos.y, _bDir);
			chargeIndex = 0;

		}
		else if (gauge == 1200)
		{
			gauge = 0;
			isAttact[F_STAY] = true;
			isAttact[BALL] = false;
			fixSite = false;
		}
	}

}




void finalBoss::animation()
{
	if (_bState == DEAD)
	{
		frameSpeed = 20;
		for (int i = 0; i < 4; i++)
			isCharging[i] = false;
	}
	if (_bDir == LEFT)
	{
		if (count % frameSpeed == 0)
		{
			index++;
			if (index > _image[_bState]->getMaxFrameX())
			{
				index = 0;
				if (_bState == DEAD)
					index = _image[_bState]->getMaxFrameX();
			}
		}
	}
	else
	{
		if (count % frameSpeed == 0)
		{
			index--;
			if (index < 0)
			{
				index = _image[_bState]->getMaxFrameX();
				if (_bState == DEAD)
					index = 0;
			}
		}
	}
	if (count % 5 == 0)
	{
		chargeIndex++;
		if (chargeIndex > 9)
		{
			chargeIndex = 0;
		}
	}
}
