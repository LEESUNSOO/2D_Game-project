#include "stdafx.h"
#include "mainMenuScene.h"

HRESULT mainMenuScene::init(void)
{
	_bgImage[0]._bgImage = IMAGEMANAGER->addImage("메인메뉴배경1", "resource/mainmenu/메인메뉴배경1.bmp", 1280, 720);
	_bgImage[1]._bgImage = IMAGEMANAGER->addImage("메인메뉴배경2", "resource/mainmenu/메인메뉴배경2.bmp", 1280, 720);
	_bgImage[2]._bgImage = IMAGEMANAGER->addImage("메인메뉴배경3", "resource/mainmenu/메인메뉴배경3.bmp", 1280, 720);
	_bgImage[3]._bgImage = IMAGEMANAGER->addImage("메인메뉴배경4", "resource/mainmenu/메인메뉴배경4.bmp", 1280, 720);
	_bgImage[4]._bgImage = IMAGEMANAGER->addImage("메인메뉴배경5", "resource/mainmenu/메인메뉴배경5.bmp", 1280, 720);

	IMAGEMANAGER->addImage("밑줄", "resource/mainmenu/categoryLine.bmp", 130, 3);
	IMAGEMANAGER->addImage("메뉴에리나", "resource/mainmenu/에리나.bmp", 934, 1050, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴리본", "resource/mainmenu/리본.bmp", 596, 784, true, RGB(255, 0, 255));
	GDIPLUS->addImage("프레임", "resource/mainmenu/시작배경프레임4.png");

	for (int i = 0; i < 5; i++)
	{
		_bgImage[i]._alpha = 0;
		_bgImage[i]._isActived = false;
		_bgImage[i]._isDownAlpha = false;
		//
		category[i] = RectMake(60 + i * 240, 600, 200, 50);
		//
		_isChoice[i] = false;
		categoryY[i] = 570;
		lineLength[i] = 1;
	}
	

	_count = _index = _bgIndex = choiceNum = 0;
	title = RectMake(50, 50, 400, 100);



	SOUNDMANAGER->play("메인메뉴씬브금", SAVEDATA->getBgmSound());

	return S_OK;
}

void mainMenuScene::release(void)
{

}

void mainMenuScene::update(void)
{
	_count++;

	this->bgChange();
	this->choiceCategory();
	this->sceneChange();
}

void mainMenuScene::render(void)
{
	for (int i = 0; i < 5; ++i)
	{
		if(_bgImage[i]._isActived|| _bgImage[i]._isDownAlpha)
			_bgImage[i]._bgImage->alphaRender(getMemDC(), _bgImage[i]._alpha);
	}

	IMAGEMANAGER->alphaRender("메뉴에리나", getMemDC(), 450,-100, 150);
	IMAGEMANAGER->alphaRender("메뉴리본", getMemDC(), 500, 50, 150);

	GDIPLUS->gdiRender("프레임", getMemDC());


	for (int i = 0; i < 5; ++i)
	{
		if(i==choiceNum)
			IMAGEMANAGER->render("밑줄", getMemDC(), 180 + choiceNum * 220, 583, 0,0,lineLength[i],5);
	}
	
	this->textSource();
}

void mainMenuScene::bgChange()
{
	for (int i = _bgIndex; i < 5; ++i)
	{
		if (!_bgImage[i]._isActived && _count % 130 == 1)
		{
			_bgImage[i]._isActived = true;
			_bgIndex++;
			break;
		}

	}
	if (_bgIndex > 4)
	{
		_bgIndex = 0;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (_bgImage[i]._isActived && !_bgImage[i]._isDownAlpha)
		{
			_bgImage[i]._alpha += 2;
			if (_bgImage[i]._alpha > 250)
			{
				_bgImage[i]._isDownAlpha = true;

			}
		}

	}

	for (int i = 0; i < 5; ++i)
	{
		if (_bgImage[i]._isDownAlpha)
		{
			_bgImage[i]._alpha -= 2;
			{
				if (_bgImage[i]._alpha < 0)
				{
					_bgImage[i]._isActived = false;
					_bgImage[i]._isDownAlpha = false;

				}
			}
		}

	}
}

void mainMenuScene::choiceCategory()
{
	for (int i = 0; i < 5; ++i)
	{
		if (i != choiceNum)
		{
			_isChoice[i] = false;
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		if (_isChoice[i])
		{
			if (categoryY[i] > 555)
				categoryY[i]--;
			if (lineLength[i] < 140)
				lineLength[i] *= 1.2f;
		}
		else
		{
			categoryY[i] = 570;
			lineLength[i] = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && choiceNum < 4)
	{
		choiceNum++;
		SOUNDMANAGER->play("메인메뉴선택", SAVEDATA->getEffSound());
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && choiceNum > 0)
	{
		choiceNum--;
		SOUNDMANAGER->play("메인메뉴선택", SAVEDATA->getEffSound());

	}

	_isChoice[choiceNum] = true;
}

void mainMenuScene::textSource()
{
	//Harrington FONT
	HFONT myFont = CreateFont(50, 19, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(0, 120, 120));
	char title[128] = "MAIN MENU";
	TextOut(getMemDC(), 70, 60, title, strlen(title));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);


	//
	HFONT myFont1 = CreateFont(23, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont1 = (HFONT)SelectObject(getMemDC(), myFont1);
	SetTextColor(getMemDC(), RGB(150, 150, 150));
	if (choiceNum == 0)
		SetTextColor(getMemDC(), RGB(0, 0, 0));

	char category_1[128] = "STORY MODE";
	TextOut(getMemDC(), 180, categoryY[0], category_1, strlen(category_1));
	SelectObject(getMemDC(), oldFont1);
	DeleteObject(myFont1);
	//

	HFONT myFont2 = CreateFont(23, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), myFont2);
	SetTextColor(getMemDC(), RGB(150, 150, 150));
	if (choiceNum == 1)
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	char category_2[128] = "BOSS RUSH";
	TextOut(getMemDC(), 180 + 220, categoryY[1], category_2, strlen(category_2));
	SelectObject(getMemDC(), oldFont2);
	DeleteObject(myFont2);
	//

	HFONT myFont3 = CreateFont(23, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), myFont3);
	SetTextColor(getMemDC(), RGB(150, 150, 150));
	if (choiceNum == 2)
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	char category_3[128] = "MAP TOOL";
	TextOut(getMemDC(), 180 + 220 + 220, categoryY[2], category_3, strlen(category_3));
	SelectObject(getMemDC(), oldFont3);
	DeleteObject(myFont3);
	//

	HFONT myFont4 = CreateFont(23, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont4 = (HFONT)SelectObject(getMemDC(), myFont4);
	SetTextColor(getMemDC(), RGB(150, 150, 150));
	if (choiceNum == 3)
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	char category_4[128] = "OPTION";
	TextOut(getMemDC(), 180 + 220 + 220 + 220, categoryY[3], category_4, strlen(category_4));
	SelectObject(getMemDC(), oldFont4);
	DeleteObject(myFont4);
	//

	HFONT myFont5 = CreateFont(23, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont5 = (HFONT)SelectObject(getMemDC(), myFont5);
	SetTextColor(getMemDC(), RGB(150, 150, 150));
	if (choiceNum == 4)
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	char category_5[128] = "EXIT";
	TextOut(getMemDC(), 180 + 220 + 220 + 220 + 220, categoryY[4], category_5, strlen(category_5));
	SelectObject(getMemDC(), oldFont5);
	DeleteObject(myFont5);
}

void mainMenuScene::sceneChange()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->play("메인메뉴최종선택",SAVEDATA->getEffSound());
		switch (choiceNum)
		{
		case 0:
			SCENEMANAGER->loadScene("타운");
			SOUNDMANAGER->stop("메인메뉴씬브금");
			break;
		case 1:
			break;
		case 2:
			SCENEMANAGER->loadScene("배경선택");
			break;
		case 3:
			break;
		case 4:
			break;
		}

	}
}
