#include "stdafx.h"
#include "startScene1.h"


HRESULT startScene1::init(void)
{
	ZeroMemory(&_bg, sizeof(startRc));
	//ZeroMemory(&_title, sizeof(startRc));
	ZeroMemory(&_startButton, sizeof(startRc));
	ZeroMemory(&_reference, sizeof(startRc));

	GDIPLUS->addImage("������", "resource/start/���۹��������4.png");

	_bg.x = 0;
	_bg.y = 0;
	_bg.rc = RectMake(_bg.x, _bg.y, WINSIZEX, WINSIZEY);
	_bg._image = IMAGEMANAGER->addImage("���۹��", "resource/start/���۹��.bmp", 2000, 1125);

	_title.x = -400;
	_title.y = 70;
	_title._gdiImage = GDIPLUS->addFrameImage("����Ÿ��Ʋ������", "resource/start/����Ÿ��Ʋ������3.png",-400,70, 8, 1);


	_startButton.x = 100;
	_startButton.y = 500;
	_startButton.rc = RectMake(_startButton.x, _startButton.y, 354, 29);
	_startButton._image = IMAGEMANAGER->addImage("��ŸƮ��ư", "resource/start/��ŸƮ��ư.bmp", 354,29,true, RGB(255,0,255));

	_reference.rc = RectMake(130, 550, 276, 54);
	_reference._image = IMAGEMANAGER->addImage("��������", "resource/start/��������.bmp", 276, 54, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��ŸƮ������", "resource/start/������.bmp", 934, 1050,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ŸƮ����", "resource/start/����.bmp", 596, 784, true, RGB(255, 0, 255));


	SOUNDMANAGER->play("��ŸƮ�����", SAVEDATA->getBgmSound());
	
	_index = _count = alpha = _sceneChange = 0;
	_isZDown = false;
	return S_OK;
}

void startScene1::release(void)
{
}

void startScene1::update(void)
{
	_count++;


	this->bgMove();
	this->titleMove();
	this->animation();
	this->sceneChange();

}

void startScene1::render(void)
{
	IMAGEMANAGER->render("���۹��",getMemDC(), _bg.rc.left, _bg.rc.top, 10 + _bg.x, 10 + _bg.y ,WINSIZEX,WINSIZEY);
	GDIPLUS->gdiRender("������", getMemDC());
	//GDIPLUS->gdiRender("������", getMemDC(), 600, 300, 200, 200, 200, 200, 45); (ȸ������)
	GDIPLUS->gdiFrameRender("����Ÿ��Ʋ������", getMemDC(), _title.rc.left, _title.rc.top, _title._gdiImage->getFrameX(), 0);
	IMAGEMANAGER->alphaRender("��ŸƮ��ư", getMemDC(), _startButton.rc.left, _startButton.rc.top, alpha);
	IMAGEMANAGER->render("��������", getMemDC(), _reference.rc.left, _reference.rc.top);
	IMAGEMANAGER->render("��ŸƮ������", getMemDC(), 450, -100);
	IMAGEMANAGER->render("��ŸƮ����", getMemDC(), 500, 50);

}

void startScene1::bgMove()
{
	if (_count % 2000 < 500)
	{
		_bg.x += 0.6f;
	}
	else if (_count % 2000 < 1000)
	{
		_bg.y += 0.6f;
	}
	else if (_count % 2000 < 1500)
	{
		_bg.x -= 0.6f;
	}
	else if (_count % 2000 < 2000)
	{
		_bg.y -= 0.6f;
	}
}

void startScene1::titleMove()
{
	if (_title.x < 100)
		_title.x += 50;

	_title.rc = RectMake(_title.x, _title.y, 512, 351);
}

void startScene1::animation()
{
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
		_title._gdiImage->setFrameX(_index);
	}



	if (_count % 100 < 50 && alpha < 255)
	{
		alpha += 4;
	}
	else if (_count % 100 < 100 && alpha > 50)
	{
		alpha -= 4;
	}
}

void startScene1::sceneChange()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_isZDown = true;
		SOUNDMANAGER->play("��ŸƮ��ư", SAVEDATA->getEffSound());
		SOUNDMANAGER->stop("��ŸƮ�����");
	}

	if (_isZDown)
	{
		alpha += 80;
		if(alpha > 2400)
			SCENEMANAGER->loadScene("���θ޴�");
	}
}
