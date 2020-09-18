#include "stdafx.h"
#include "stage_MAPt.h"

HRESULT stage_MAPt::init(void)
{
	return S_OK;
}

void stage_MAPt::release(void)
{
}

void stage_MAPt::update(void)
{
}

void stage_MAPt::render(void)
{
}

void stage_MAPt::load(void)
{
}


HRESULT town_MAP::init(void)
{
	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);


	IMAGEMANAGER->addImage("타운상점", "resource/mapBG/타운상점.bmp", 880, 500, true, MAGENTA);
	IMAGEMANAGER->addImage("타운미르네", "resource/mapBG/타운미르네.bmp", 850, 500, true, MAGENTA);
	IMAGEMANAGER->addImage("타운빈집", "resource/mapBG/타운빈집.bmp", 690, 500, true, MAGENTA);
	IMAGEMANAGER->addImage("타운나무", "resource/mapBG/타운나무.bmp", 1560, 500, true, MAGENTA);


	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.left, i * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.top, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;


	renderX = renderY = 0;
	limitedX = 1280 * 4;
	limitedY = 720;

	//건물
	store = RectMake(200, 10, 880, 500);
	mirHome = RectMake(1280 + 200, 10, 850, 500);
	restHome[0] = RectMake(1280 * 2 + 300, -10, 690, 500);
	restHome[1] = RectMake(1280 * 3 + 350, 10, 690, 500);

	GDIPLUS->addFrameImage("워프", "resource/mapBG/warp2.png", 0, 0, 30, 1);
	GDIPLUS->addFrameImage("워프테두리", "resource/mapBG/warpEdge.png", 0, 0, 3, 1);
	GDIPLUS->addImage("워프불빛", "resource/mapBG/warpLight.png");


	warp = RectMakeCenter(3800, 400, 80, 400);
	warpIndex = warpEdgeIndex = count = 0;

	return S_OK;
}

void town_MAP::release(void)
{
}

void town_MAP::update(void)
{

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;

	warpIndex++;
	if (warpIndex > 30)
		warpIndex = 0;
	warpEdgeIndex++;
	if (warpEdgeIndex > 3)
		warpEdgeIndex = 0;

}

void town_MAP::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}

	IMAGEMANAGER->render("타운상점", getMemDC(), store.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, store.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	IMAGEMANAGER->render("타운미르네", getMemDC(), mirHome.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, mirHome.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	IMAGEMANAGER->render("타운빈집", getMemDC(), restHome[0].left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, restHome[0].top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	IMAGEMANAGER->render("타운빈집", getMemDC(), restHome[1].left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, restHome[1].top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);
	IMAGEMANAGER->render("타운나무", getMemDC(), 1280 + 640 - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);


	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}

	//GDIPLUS->gdiFrameRender("워프", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, warpIndex, 0);

	//for (int i = 0; i < 3; i++)
	//	GDIPLUS->gdiFrameRender("워프테두리", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * (120 * i + count) * 2) * 50 + 30, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top + sinf(PI / 180 * (120 * i + count)) * 50 + 35, warpEdgeIndex, 0);

	//GDIPLUS->gdiRender("워프불빛", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 110, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);


}

void town_MAP::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save15.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{

		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
	}
}

HRESULT stage1_MAPt::init(void)
{
	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);


	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280 * 4;
	limitedY = 720;

	return S_OK;
}

void stage1_MAPt::release(void)
{
}

void stage1_MAPt::update(void)
{

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;
}

void stage1_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left- CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}


}

void stage1_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
		if (_tiles[i].terrain == TR_BOMB) _canPass[i] = false;
	}
}


HRESULT stage1_1_MAPt::init(void)
{
	
	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

		//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.left, i * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.top, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280*4;
	limitedY = 720;


	return S_OK;
}

void stage1_1_MAPt::release(void)
{
}

void stage1_1_MAPt::update(void)
{

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;
}

void stage1_1_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}


}

void stage1_1_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save2.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
		if (_tiles[i].terrain == TR_BOMB) _canPass[i] = false;
	}
}

HRESULT stage1_2_MAPt::init(void)
{

	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280 * 2;
	limitedY = 720;

	GDIPLUS->addFrameImage("워프", "resource/mapBG/warp2.png", 0, 0, 30, 1);
	GDIPLUS->addFrameImage("워프테두리", "resource/mapBG/warpEdge.png", 0, 0, 3, 1);
	GDIPLUS->addImage("워프불빛", "resource/mapBG/warpLight.png");

	warp = RectMakeCenter(1920, 400, 80, 300);
	warpIndex = warpEdgeIndex = count = 0;

	return S_OK;
}

void stage1_2_MAPt::release(void)
{
}

void stage1_2_MAPt::update(void)
{
	count++;

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;

	warpIndex++;
	if (warpIndex > 30)
		warpIndex = 0;
	warpEdgeIndex++;
	if (warpEdgeIndex > 3)
		warpEdgeIndex = 0;
}

void stage1_2_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}
	GDIPLUS->gdiFrameRender("워프", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, warpIndex, 0);
	
	for (int i = 0; i < 3; i++)
		GDIPLUS->gdiFrameRender("워프테두리", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * (120 * i + count) * 2) * 50 + 30, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top + sinf(PI / 180 * (120 * i + count)) * 50 + 35, warpEdgeIndex, 0);

	GDIPLUS->gdiRender("워프불빛", getMemDC(), warp.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left - 110, warp.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top );

}

void stage1_2_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save3.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{

		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
	}
}

HRESULT stage1_3_MAPt::init(void)
{

	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

	_springImg = IMAGEMANAGER->addFrameImage("스프링", "resource/maptool/스프링2.bmp", 1200, 100, 10, 1);

	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.left, i * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.top, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280 * 2;
	limitedY = 720*4;

	springX = 150;
	springY = 1504;
	springIndex = count = saveEdgeIndexX = 0;
	
	saveIndexX = 0;
	savePoint = RectMakeCenter(700, 600, 60, 400);
	GDIPLUS->addFrameImage("세이브포인트", "resource/mapBG/savePoint2.png", 0, 0, 32, 1);
	GDIPLUS->addFrameImage("세이브포인트테두리", "resource/mapBG/savePointEdge.png", 0, 0, 3, 1);

	return S_OK;
}

void stage1_3_MAPt::release(void)
{
}

void stage1_3_MAPt::update(void)
{
	count++;

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;
	//if (count % 3 == 0)
	{
		saveIndexX++;
		if (saveIndexX > 32)
			saveIndexX = 0;
	}

	if (count % 5 == 0)
	{
		saveEdgeIndexX++;
		if (saveEdgeIndexX > 3)
			saveEdgeIndexX = 0;

	}

	spring = RectMake(springX, springY, 120, 100);
}

void stage1_3_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}

	IMAGEMANAGER->frameRender("스프링", getMemDC(), spring.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, spring.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, springIndex, 0);
	GDIPLUS->gdiFrameRender("세이브포인트", getMemDC(), savePoint.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, savePoint.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, saveIndexX, 0);
	for (int i = 0; i < 3; i++)
		GDIPLUS->gdiFrameRender("세이브포인트테두리", getMemDC(), savePoint.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI/180*(120*i +count))*100 + 20, savePoint.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top + sinf(PI / 180 * (120 * i + count)) * 100 + 10, saveEdgeIndexX, 0);

}

void stage1_3_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save4.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
	}
}


HRESULT stage2_1_MAPt::init(void)
{
	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);


	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280;
	limitedY = 720;

	saveIndexX = count = saveEdgeIndexX = 0;
	savePoint = RectMakeCenter(700, 600, 60, 400);

	GDIPLUS->addFrameImage("세이브포인트", "resource/mapBG/savePoint2.png", 0, 0, 32, 1);
	GDIPLUS->addFrameImage("세이브포인트테두리", "resource/mapBG/savePointEdge.png", 0, 0, 3, 1);


	return S_OK;
}

void stage2_1_MAPt::release(void)
{
}

void stage2_1_MAPt::update(void)
{
	count++;

	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;

	//if (count % 3 == 0)
	{
		saveIndexX++;
		if (saveIndexX > 32)
			saveIndexX = 0;
	}

	if (count % 5 == 0)
	{
		saveEdgeIndexX++;
		if (saveEdgeIndexX > 3)
			saveEdgeIndexX = 0;

	}
}

void stage2_1_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}

	GDIPLUS->gdiFrameRender("세이브포인트", getMemDC(), savePoint.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, savePoint.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, saveIndexX, 0);
	for (int i = 0; i < 3; i++)
		GDIPLUS->gdiFrameRender("세이브포인트테두리", getMemDC(), savePoint.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left + cosf(PI / 180 * (120 * i + count)) * 100 + 20, savePoint.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top + sinf(PI / 180 * (120 * i + count)) * 100 + 10, saveEdgeIndexX, 0);

}

void stage2_1_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save6.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{

		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
	}
}



HRESULT stage1_BOSS_MAPt::init(void)
{

	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.left, i * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.top, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280;
	limitedY = 720;

	return S_OK;
}

void stage1_BOSS_MAPt::release(void)
{
}

void stage1_BOSS_MAPt::update(void)
{
	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;

}

void stage1_BOSS_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}

}

void stage1_BOSS_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save5.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
		if (_tiles[i].terrain == TR_BOMB) _canPass[i] = false;
	}
}



HRESULT stage_FinalBoss_MAPt::init(void)
{

	//정방향
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//역방향
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.left, i * TILESIZE - CAMERAMANAGER->getVCam("맵툴캠")[0].rc.top, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_canPass[i] = true;
	}

	//맵로드 
	this->load();

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	renderX = renderY = 0;
	limitedX = 1280;
	limitedY = 720;

	return S_OK;
}

void stage_FinalBoss_MAPt::release(void)
{
}

void stage_FinalBoss_MAPt::update(void)
{
	renderX = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top / TILESIZE;

}

void stage_FinalBoss_MAPt::render(void)
{


	//전체화면 왼쪽에 오브젝트를 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	//전체화면 왼쪽에 지형을 그린다
	for (int i = renderY; i < renderY + 12; i++)
	{
		for (int j = renderX; j < renderX + 21; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("플레이어카메라")[0].rc.top);

		}
	}

}

void stage_FinalBoss_MAPt::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save7.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == ALLOBJECT) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_DOPASS) _canPass[i] = true;
		if (_tiles[i].obj == OBJECT_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_NONE) _canPass[i] = true;
		if (_tiles[i].terrain == TR_DOPASS) _canPass[i] = true;
		if (_tiles[i].terrain == TR_ROOF) _canPass[i] = false;
		if (_tiles[i].terrain == TR_GROUND) _canPass[i] = false;
		if (_tiles[i].terrain == TR_BOMB) _canPass[i] = false;
	}
}


