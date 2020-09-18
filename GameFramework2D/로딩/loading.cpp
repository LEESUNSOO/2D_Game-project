#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (로드아이템 클래스)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//사운드 초기화
HRESULT loadItem::initForSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_SOUND;
	//사운드 구조체 초기화
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}


//=============================================================
//	## loading ## (로딩클래스)
//=============================================================
HRESULT loading::init(void)
{
	for (int i = 0; i < 10; ++i)
	{
		loadingTextRc[i].x = WINSIZEX - 500 + i * 33;
		loadingTextRc[i].y = WINSIZEY - 80;
		loadingTextRc[i].angle = 0;
		loadingTextRc[i].speed = 2.0f;
		loadingTextRc[i].isCycle = false;
		loadingTextRc[i].cycleCount = 0;
	}

	this->bgSetting();

	loadingText = IMAGEMANAGER->addImage("로딩문구", "resource/loading/로딩문구.bmp", 300, 300,true,RGB(255,0,255));
	//loadingRate =
	_index = _count = _textIndex = 0;
	bgRandNum = RND->getInt(25);


	for (int i = 0; i < 10; ++i)
	{
		addChangeY[i] = 0;
	}
	////로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init();
	_loadingBar->setGauge(0, 0);
	////현재 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}

void loading::release(void)
{
	//로딩바 클래스 해제
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//로딩바 클래스 업데이트
	_loadingBar->update();

	_count++;
	this->textColorChange();
	this->textMove();
}

void loading::render(void)
{
	_bgImage[bgRandNum]->gdiRender(getMemDC());

	for (int i = 0; i < 10; ++i)
	{
		if (loadTextChange[i] + addChangeY[i] >= 300)
			addChangeY[i] = 0;

		loadingText->alphaRender(getMemDC(), loadingTextRc[i].rc.left, loadingTextRc[i].rc.top, loadTextChange[i], loadTextChange[i] + addChangeY[i], 30, 30, 160);
	}
	////로딩바 클래스 렌더
	_loadingBar->render();
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	//로딩이 완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
	case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_2:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	//곧 사운드 배우고 난후 알아서...
	case LOAD_KIND_SOUND:
		{
			tagSoundResource soundResource = item->getSoundResource();
			SOUNDMANAGER->addSound(soundResource.keyName, soundResource.fileName, soundResource.bgm, soundResource.loop);
		}
		break;
	}

	//현재게이지 증가
	_currentGauge++;

	//로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return 0;
}

void loading::bgSetting()
{
	_bgImage[0] = GDIPLUS->addImage("로딩배경1", "resource/loading/bg/loadcg0_a.jpg");
	_bgImage[1] = GDIPLUS->addImage("로딩배경2", "resource/loading/bg/loadcg1_a.jpg");
	_bgImage[2] = GDIPLUS->addImage("로딩배경3", "resource/loading/bg/loadcg2_a.jpg");
	_bgImage[3] = GDIPLUS->addImage("로딩배경4", "resource/loading/bg/loadcg3_a.jpg");
	_bgImage[4] = GDIPLUS->addImage("로딩배경5", "resource/loading/bg/loadcg4_a.jpg");

	_bgImage[5] = GDIPLUS->addImage("로딩배경6", "resource/loading/bg/loadcg5_a.jpg");
	_bgImage[6] = GDIPLUS->addImage("로딩배경7", "resource/loading/bg/loadcg6_a.jpg");
	_bgImage[7] = GDIPLUS->addImage("로딩배경8", "resource/loading/bg/loadcg7_a.jpg");
	_bgImage[8] = GDIPLUS->addImage("로딩배경9", "resource/loading/bg/loadcg8_a.jpg");
	_bgImage[9] = GDIPLUS->addImage("로딩배경0", "resource/loading/bg/loadcg9_a.jpg");

	_bgImage[10] = GDIPLUS->addImage("로딩배경11", "resource/loading/bg/loadcg10_a.jpg");
	_bgImage[11] = GDIPLUS->addImage("로딩배경12", "resource/loading/bg/loadcg11_a.jpg");
	_bgImage[12] = GDIPLUS->addImage("로딩배경13", "resource/loading/bg/loadcg12_a.jpg");
	_bgImage[13] = GDIPLUS->addImage("로딩배경14", "resource/loading/bg/loadcg13_a.jpg");
	_bgImage[14] = GDIPLUS->addImage("로딩배경15", "resource/loading/bg/loadcg14_a.jpg");

	_bgImage[15] = GDIPLUS->addImage("로딩배경16", "resource/loading/bg/loadcg15_a.jpg");
	_bgImage[16] = GDIPLUS->addImage("로딩배경17", "resource/loading/bg/loadcg16_a.jpg");
	_bgImage[17] = GDIPLUS->addImage("로딩배경18", "resource/loading/bg/loadcg17_a.jpg");
	_bgImage[18] = GDIPLUS->addImage("로딩배경19", "resource/loading/bg/loadcg18_a.jpg");
	_bgImage[19] = GDIPLUS->addImage("로딩배경20", "resource/loading/bg/loadcg19_a.jpg");

	_bgImage[20] = GDIPLUS->addImage("로딩배경21", "resource/loading/bg/loadcg20_a.jpg");
	_bgImage[21] = GDIPLUS->addImage("로딩배경22", "resource/loading/bg/loadcg21_a.jpg");
	_bgImage[22] = GDIPLUS->addImage("로딩배경23", "resource/loading/bg/loadcg22_a.jpg");
	_bgImage[23] = GDIPLUS->addImage("로딩배경24", "resource/loading/bg/loadcg23_a.jpg");
	_bgImage[24] = GDIPLUS->addImage("로딩배경25", "resource/loading/bg/loadcg24_a.jpg");

}

//void loading::rabbitSpin()
//{
//	if (_count % 5 == 0)
//	{
//		_index++;
//		if (_index > loadRabbit_1->getMaxFrameX())
//		{
//			_index = 0;
//		}
//
//		loadRabbit_1->setFrameX(_index);
//
//	}
//	loadRabbit_1->setFrameY(0);
//}

void loading::textColorChange()
{
	if (_count % 20 == 0)
	{
		for (int i = 0; i < 10; ++i)
		{

			loadTextChange[i] = 30 * i;
			if (loadTextChange[i] >= 300)
			{
				loadTextChange[i] = 0;
			}
			addChangeY[i] += 30;
		}
	}
}

void loading::textMove()
{

	_textIndex++;
	if (_textIndex > 10)
		_textIndex = 0;

	for (int i = _textIndex; i < 10; ++i)
	{
		if (loadingTextRc[i].isCycle == false && _count % 10==0)
		{
			loadingTextRc[i].isCycle = true;
			break;			
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		if (loadingTextRc[i].isCycle)
		{
			loadingTextRc[i].angle += 0.2f;
			loadingTextRc[i].y += -sinf(loadingTextRc[i].angle)*loadingTextRc->speed;
			
		}

		if (loadingTextRc[i].y > WINSIZEY - 80)
		{
			loadingTextRc[i].angle = 0;
			loadingTextRc[i].isCycle = false;
		}

	}
	
	for (int i = 0; i < 10; ++i)
	{
		loadingTextRc[i].rc = RectMakeCenter(loadingTextRc[i].x, loadingTextRc[i].y , 30, 30);

	}
}
