#include "stdafx.h"
#include "bgChoiceScene1.h"

HRESULT bgChoiceScene1::init(void)
{
	
	_bg._x = 0;
	_bg._y = 0;
	_bg._rc = RectMake(_bg._x, _bg._y, WINSIZEX, WINSIZEY);
	_bg._image = IMAGEMANAGER->addImage("배경선택배경", "resource/bgChoice/배경선택배경1.bmp", 1280, 720);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			_bgSelect[i * 5 + j]._x = 100 + 220 * j;
			_bgSelect[i * 5 + j]._y = 60 + 157 * i;
			_bgSelect[i * 5 + j]._rc = RectMake(_bgSelect[i * 5 + j]._x, _bgSelect[i * 5 + j]._y, 200, 137);
			_bgSelect[i * 5 + j]._index = i * 5 + j; // 0~19
			_bgSelect[i * 5 + j]._alpha = 110;
		}
	}

	_bgFairy._image = IMAGEMANAGER->addFrameImage("배경선택요정", "resource/bgChoice/배경선택요정.bmp", 1280, 128, 10, 1);
	_bgFairy._isActived = false;

	IMAGEMANAGER->addImage("배경항목", "resource/bgChoice/배경항목.bmp", 1000, 548);
	
	_count = _index = loofSpeed = 0;
	isSelected = false;

	return S_OK;
}

void bgChoiceScene1::release(void)
{

}

void bgChoiceScene1::update(void)
{
	_count++;

	loofSpeed += 3;
	
	for (int i = 0; i < MAPKIND; ++i)
	{
		if (PtInRect(&_bgSelect[i]._rc, _ptMouse))
		{
			_bgSelect[i]._alpha = 255;

		}
		else
		{
			_bgSelect[i]._alpha = 110;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAPKIND; ++i)
		{
			if (PtInRect(&_bgSelect[i]._rc, _ptMouse))
			{
				selectNum = _bgSelect[i]._index;
				SAVEDATA->setSelectNum(_bgSelect[i]._index);
				isSelected = true;
				if (isSelected)
				{
					_bgFairy._isActived = true;
					_bgFairy._x = _bgSelect[selectNum]._x + 30;
					_bgFairy._y = _bgSelect[selectNum]._y;
					_bgFairy._rc = RectMake(_bgFairy._x, _bgFairy._y, 64, 64);
				}
				//SCENEMANAGER->loadScene("맵툴씬");
			}
			else
			{
				selectNum = NULL;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SCENEMANAGER->loadScene("메인메뉴");
		SOUNDMANAGER->play("메인메뉴선택", SAVEDATA->getEffSound());

	}

	if (_bgFairy._isActived)
	{
		if (_count % 2 == 0)
		{
			_index++;
			if (_index > _bgFairy._image->getMaxFrameX())
			{
				_index = 0;
				SCENEMANAGER->loadScene("맵툴씬");
			}
			_bgFairy._image->setFrameX(_index);
		}
	}


}

void bgChoiceScene1::render(void)
{
	//IMAGEMANAGER->render("배경선택배경", getMemDC(), _bg._rc.left, _bg._rc.top, 10 + _bg._x, 10 + _bg._y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("배경선택배경", getMemDC(), &_bg._rc, loofSpeed, -loofSpeed);

	for (int i = 0; i < MAPKIND; ++i)
	{
		//Rectangle(getMemDC(), _bgSelect[i]._rc);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{	
			//IMAGEMANAGER->alphaRender("배경항목", getMemDC(), _bgSelect[i * 5 + j]._rc.left + 5, _bgSelect[i * 5 + j]._rc.top - 5, j * 200, i * 137, 200, 137, _bgSelect[i * 5 + j]._alpha);
			IMAGEMANAGER->alphaRender("배경항목", getMemDC(), _bgSelect[i * 5 + j]._rc.left, _bgSelect[i * 5 + j]._rc.top, j * 200, i * 137, 200, 137, _bgSelect[i * 5 + j]._alpha);

		}
	}
	
	if (isSelected)
	{
		//Rectangle(getMemDC(), _bgFairy._rc);
	}

	if (_bgFairy._isActived)
	{
		IMAGEMANAGER->frameRender("배경선택요정", getMemDC(), _bgFairy._rc.left , _bgFairy._rc.top, _bgFairy._image->getFrameX(), 0);
	}


	HFONT myFont = CreateFont(55, 20, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	char title1[128] = "MAP SELECT";
	TextOut(getMemDC(), WINSIZEX / 2 - 155, 20, title1, strlen(title1));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	HFONT myFont1 = CreateFont(50, 19, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont1 = (HFONT)SelectObject(getMemDC(), myFont1);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	char title[128] = "MAP SELECT";
	TextOut(getMemDC(), WINSIZEX/2 - 155, 20, title, strlen(title));
	SelectObject(getMemDC(), oldFont1);
	DeleteObject(myFont1);


}

void bgChoiceScene1::bgMove()
{

}
