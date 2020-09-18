#include "stdafx.h"
#include "maptoolScene1.h"

HRESULT maptoolScene1::init(void)
{
	//Ÿ�ϸ� �̹��� �ʱ�ȭ
	//�� ��Ʈ�� �߰�
	IMAGEMANAGER->addImage("���Ʈ��", "resource/maptool/���Ʈ��.bmp", 6400, 3200, true, MAGENTA);// , true, MAGENTA);

	//������
	_sampleTile[0][0] = IMAGEMANAGER->addFrameImage("grass", "resource/maptool/grass_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[1][0] = IMAGEMANAGER->addFrameImage("desert", "resource/maptool/desert_tiles.bmp", 448, 1920, 7, 30);
	_sampleTile[2][0] = IMAGEMANAGER->addFrameImage("ice", "resource/maptool/ice_tiles.bmp", 448, 1280, 7, 20);
	_sampleTile[3][0] = IMAGEMANAGER->addFrameImage("object", "resource/maptool/object_tiles.bmp", 448, 1280, 7, 20);
	//������
	_sampleTile[0][1] = IMAGEMANAGER->addFrameImage("grassR", "resource/maptool/grass_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[1][1] = IMAGEMANAGER->addFrameImage("desertR", "resource/maptool/desert_tilesR.bmp", 448, 1920, 7, 30);
	_sampleTile[2][1] = IMAGEMANAGER->addFrameImage("iceR", "resource/maptool/ice_tilesR.bmp", 448, 1280, 7, 20);
	_sampleTile[3][1] = IMAGEMANAGER->addFrameImage("objectR", "resource/maptool/object_tilesR.bmp", 448, 1280, 7, 20);

	//���͸�
	//���
	//IMAGEMANAGER->addImage("���ʹ��", "resource/maptool/����2.bmp", 448, 256);

	//�̹������� ����
	_selectTileType = _selectObjectType = typeNum = 0;
	_selectTileDir = 0;
	_sampleTileX = _sampleTileY = 0;

	_bgImage[0] = IMAGEMANAGER->addImage("Ǯ��", "resource/maptool/Ǯ��.bmp", 1280, 720);
	_bgImage[1] = IMAGEMANAGER->addImage("Ǯ��2", "resource/maptool/Ǯ��2.bmp", 1280, 720);

	_bgNum = TILEXBASE / 20;

	//�����̹���
	IMAGEMANAGER->addImage("�������", "resource/maptool/�������1.bmp", 572, 406);
	_mapAni[0] = IMAGEMANAGER->addFrameImage("����������", "resource/maptool/������濹����.bmp", 384, 64, 6, 1);
	_mapAni[1] = IMAGEMANAGER->addFrameImage("���ʵ����", "resource/maptool/���ʵ����2.bmp", 768, 128, 6, 1);

	IMAGEMANAGER->addImage("����Ÿ��Ʋ", "resource/maptool/����Ÿ��Ʋ.bmp", 602, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����Ʋ", "resource/maptool/����Ʋ2.bmp", 602, 406, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������Ʋ", "resource/maptool/��������Ʋ.bmp", 462, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "resource/maptool/����.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ҷ�����", "resource/maptool/�ҷ�����.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ġ��", "resource/maptool/��ġ��.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "resource/maptool/����.bmp", 54, 34, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ƕ�̵�", "resource/maptool/�Ƕ�̵�.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "resource/maptool/��.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����", "resource/maptool/�����.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "resource/maptool/������Ʈ.bmp", 54, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "resource/maptool/����.bmp", 108, 34, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Ÿ���浹", "resource/maptool/Ÿ���浹.bmp", 54, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���浹", "resource/maptool/���浹.bmp", 54, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�缱", "resource/maptool/�缱.bmp", 54, 54, true, RGB(255, 0, 255));
	reverseButton = IMAGEMANAGER->addFrameImage("������", "resource/maptool/reverse.bmp", 648, 54,12,1);
	addBgButton = IMAGEMANAGER->addImage("�ֻ���", "resource/maptool/�ֻ���.bmp", 96, 20, true, MAGENTA);

	//���ù����̹���
	IMAGEMANAGER->addImage("���ù���", "resource/maptool/���ù���.bmp", 64, 64);
	IMAGEMANAGER->addImage("���ù���2", "resource/maptool/���ù���2.bmp", 64, 64, true, MAGENTA);

	//���� ���� ����
	_saveFilespaceImage[0] = IMAGEMANAGER->addImage("empty", "resource/maptool/����empty.bmp", 70, 50);
	_saveFilespaceImage[1] = IMAGEMANAGER->addImage("saved", "resource/maptool/����saved.bmp", 70, 50);

	IMAGEMANAGER->addFrameImage("savedNum", "resource/maptool/saveFileNum.bmp", 420, 20, 15, 1);
	_saveFileNum = 1;


	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//{
	//
	//	//atoi => ���ڸ� ���ڷ�
	//	_rocket->setX();
	//	_rocket->setY(atoi(vStr[1].c_str()));
	//	_currentHp = (atoi(vStr[2].c_str()));
	//}

	vector<string> vStr;
	vStr = TXTDATA->loadTXT("if_file_saved.txt");
	for (int i = 0; i < SAVEFILES; ++i)
	{
		_isSaved[i] = atoi(vStr[i].c_str());
	}

	//for (int i = 0; i < SAVEFILES ; ++i)
	//{
	//	_isSaved[i] = false;
	//}


	//����ȭ���� ��� ��ȭ������ �⺻Ÿ�� �����ϱ�
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = TR_NONE;
		_tiles[i].obj = OBJECT_NONE;
		_tiles[i].tileType = 0;
		_tiles[i].objectType = 0;
		_tiles[i].reverse = 0;
		_tiles[i].isPreView = false;
	}

	//���� ����ȭ�� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

		}
	}

	//�����׸��� ��ư���� �ʱ�ȭ
	_ctrlSelect = CTRL_DONTPASS;

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;

	_isDraw = true;

	_mapT.x = 650;
	_mapT.y = 20;
	_mapT.rc = RectMake(_mapT.x, _mapT.y, 512 + 60 + 30, 406); // 602, 406

	_selectCheck.x = _mapT.x + 30;
	_selectCheck.y = _mapT.y + 30;
	_selectCheck.rc = RectMake(_selectCheck.x, _selectCheck.y, 448, 256);

	_tileScroll.x = _mapT.x + 30;
	_tileScroll.y = _mapT.y + 30 ;

	_title.x = _mapT.x;
	_title.y = _mapT.y - 16;
	_title.rc = RectMake(_title.x, _title.y, 602, 20);

	loopSpeed = _index = _count = _indexReverse = 0;
	renderX = renderY = 0;



	////////////////////////////////���ʹ̻���Ÿ��//////////////////////////////////
	_mobMap.x = _selectCheck.rc.left;
	_mobMap.y = -350;
	//_mobMap.rc = RectMake(_mobMap.x, _mobMap.y, 448, 256);
	IMAGEMANAGER->addImage("���ʹ̻���Ÿ�Ϲ��", "resource/maptool/����2.bmp", 448, 256, true , MAGENTA);
	IMAGEMANAGER->addImage("����", "resource/maptool/����1.bmp", 448, 256, true, MAGENTA);

	_enemySampleTiles[0]._image = IMAGEMANAGER->addFrameImage("1","resource/enemy/����MOVE.bmp", 210, 140, 3, 2);
	_enemySampleTiles[1]._image = IMAGEMANAGER->addFrameImage("2", "resource/enemy/������MOVE.bmp", 320, 140
		, 4, 2);
	_enemySampleTiles[2]._image = IMAGEMANAGER->addFrameImage("3", "resource/enemy/�䳢MOVE.bmp", 350, 140, 5, 2);
	_enemySampleTiles[3]._image = IMAGEMANAGER->addFrameImage("4", "resource/enemy/���Ƹ�MOVE.bmp", 400, 160, 5, 2);
	_enemySampleTiles[4]._image = IMAGEMANAGER->addFrameImage("5","resource/enemy/�ٶ���MOVE.bmp", 600, 150, 8, 2);
	_enemySampleTiles[5]._image = IMAGEMANAGER->addFrameImage("6","resource/enemy/��MOVE.bmp", 280, 140, 4, 2);
	_enemySampleTiles[6]._image = IMAGEMANAGER->addFrameImage("7","resource/enemy/��IDLE.bmp", 400, 160, 5, 2);
	_enemySampleTiles[7]._image = IMAGEMANAGER->addFrameImage("8","resource/enemy/������ATTACT.bmp", 64, 64, 1, 1);
	_enemySampleTiles[8]._image = IMAGEMANAGER->addFrameImage("9","resource/enemy/����MOVE.bmp", 300, 150, 4, 2);
	_enemySampleTiles[9]._image = IMAGEMANAGER->addFrameImage("10","resource/enemy/�����MOVE.bmp", 400, 160, 5, 2);
	_enemySampleTiles[10]._image = IMAGEMANAGER->addFrameImage("11","resource/enemy/ĸ��MOVE.bmp", 500, 200, 5, 2);
	_enemySampleTiles[11]._image = IMAGEMANAGER->addFrameImage("12","resource/enemy/������MOVE.bmp", 375, 150, 5, 2);

	for (int j = 0; j < 12; ++j)
	{
		_enemySampleTiles[j]._isTouched = false;
		_enemySampleTiles[j]._index = 0;

	}

	_isMobMapChecked = false;
	_addEnemy = false;
	crazyDogRotateRate = PI*2/8;
	_choiceEnemyType = 0;


	strEnemy = "enemyInf" + to_string(_saveFileNum) + ".txt";

	_vEnemyInf = TXTDATA->loadTXT(strEnemy.c_str());


	for (int i = 0; i<_vEnemyInf.size(); i+=3)
	{
		_enemyRc.type = atoi(_vEnemyInf[i].c_str());
		_enemyRc.x = atoi(_vEnemyInf[i + 1].c_str());
		_enemyRc.y = atoi(_vEnemyInf[i + 2].c_str());
		_enemyRc.rc = RectMakeCenter(_enemyRc.x, _enemyRc.y, 100, 100);

		_vEnemyRc.push_back(_enemyRc);

		/*_vEnemyRc[i].type = atoi(_vEnemyInf[i].c_str());
		_vEnemyRc[i].x = atoi(_vEnemyInf[i + 1].c_str());
		_vEnemyRc[i].y = atoi(_vEnemyInf[i + 2].c_str());
		_vEnemyRc[i].rc = RectMakeCenter(_vEnemyRc[i].x, _vEnemyRc[i].y, 100, 100);*/
	}

	this->load(_saveFileNum);



	//ī�޶�Ŵ��� ����
	CAMERAMANAGER->init("����ķ", WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);




	return S_OK;
}

void maptoolScene1::release(void)
{
}

void maptoolScene1::update(void)
{
	loopSpeed++;
	_count++;

	_sampleTileX = _sampleTile[typeNum][_selectTileDir]->getWidth() / _sampleTile[typeNum][_selectTileDir]->getFrameWidth();
	_sampleTileY = _sampleTile[typeNum][_selectTileDir]->getHeight() / _sampleTile[typeNum][_selectTileDir]->getFrameHeight();

	this->enemySampleTile();

	this->animation();
	this->mapToolOnOff();		
	this->mouseWheel();
	if(!_isMobMapChecked && !_addEnemy)
		this->setMap();
	this->cameraClipping();




}

void maptoolScene1::render(void)
{
	//�ش� ��� ����
	for (int i = 0; i < _bgNum; ++i) // ��漱�ÿ��� ���õ� ��ȣ�� savedata�� ���� ������
	{
		_bgImage[SAVEDATA->getSelectNum()]->render(getMemDC(), WINSIZEX * i - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, -CAMERAMANAGER->getVCam("����ķ")[0].rc.top);
	}
	
	//_bgImage[SAVEDATA->getSelectNum()]->render(getMemDC(), WINSIZEX - CAMERAMANAGER->getVCam("����ķ")[0].rc.left , -CAMERAMANAGER->getVCam("����ķ")[0].rc.top);

	// 1)�κз���	
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 20; j++)
		{
			if (_tiles[i * TILEXBASE + j].obj == OBJECT_NONE) continue;
			_sampleTile[_tiles[i * TILEXBASE + j].objectType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, _tiles[i * TILEXBASE + j].objFrameX, _tiles[i * TILEXBASE + j].objFrameY);

		}
	}
	
	for (int i = renderY; i < renderY + 11; i++)
	{
		for (int j = renderX; j < renderX + 20; j++)
		{
			if (_tiles[i * TILEXBASE + j].terrain == TR_NONE) continue;
				_sampleTile[_tiles[i * TILEXBASE + j].tileType][_tiles[i * TILEXBASE + j].reverse]->frameRender(getMemDC(), _tiles[i * TILEXBASE + j].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _tiles[i * TILEXBASE + j].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, _tiles[i * TILEXBASE + j].terrainFrameX, _tiles[i * TILEXBASE + j].terrainFrameY);

		}
	}


	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//Rectangle(getMemDC(), CAMERAMANAGER->getVCam("����ķ")[0].rc); //ī�޶�Ŵ��� Ȯ�ο�

		//����Ÿ�� ��Ʈ ����
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, _tiles[i].rc.right - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _tiles[i].rc.bottom - CAMERAMANAGER->getVCam("����ķ")[0].rc.top);
		}
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		//�̹���Ÿ�� ��Ʈ ����
		//for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//{
		//	Rectangle(getMemDC(), _sampleTiles[i].rc);
		//}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].isPreView)
			IMAGEMANAGER->alphaRender("���ù���", getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _tiles[i].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, 130);
	}

	//Rectangle(getMemDC(), _rct);

	
	//���ʹ� ���� ���Ͱ�����

	for (int i = 0; i < _vEnemyInf.size(); i++)
	{
		char checkck[128];
		wsprintf(checkck, "%d", _vEnemyInf[i]);
		TextOut(getMemDC(), 20 , 200 + i * 20, checkck, strlen(checkck));

	}

	//if (!_vEnemyRc.empty())
	//{
		for (int i = 0; i < _vEnemyRc.size(); i++)
		{
			Rectangle(getMemDC(), _vEnemyRc[i].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _vEnemyRc[i].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, _vEnemyRc[i].rc.right - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _vEnemyRc[i].rc.bottom - CAMERAMANAGER->getVCam("����ķ")[0].rc.top);
		}

		for (int i = 0; i < _vEnemyRc.size(); i++)
		{
			_enemySampleTiles[_vEnemyRc[i].type]._image->frameRender(getMemDC(), _vEnemyRc[i].rc.left - CAMERAMANAGER->getVCam("����ķ")[0].rc.left, _vEnemyRc[i].rc.top - CAMERAMANAGER->getVCam("����ķ")[0].rc.top, 0, 0);

		}

	//}

	


	//Ÿ�ϸ� �̹��� ����
	if (KEYMANAGER->isToggleKey('M'))
	{
		//Rectangle(getMemDC(), _mapT.rc);
		//Rectangle(getMemDC(), _tileScroll.rc);
		//Rectangle(getMemDC(), _selectCheck.rc);

		IMAGEMANAGER->loopRender("�������", getMemDC(), &_mapT.rc, -loopSpeed, 0);

		IMAGEMANAGER->frameRender("����������", getMemDC(), _mapT.rc.right -65 , _mapT.rc.top + 170, _mapAni[0]->getFrameX(), 0);

		//����Ÿ��Ÿ�Ժ� �̹���
			_sampleTile[typeNum][_selectTileDir]->render(getMemDC(), _mapT.rc.left + 30, _mapT.rc.top + 30, 0, _mapT.rc.top - _tileScroll.rc.top + 30,
			_tileScroll.rc.right - _tileScroll.rc.left, 256);
	


		IMAGEMANAGER->alphaRender("���ù���2", getMemDC(), _selectCheck.rc.left + _currentSampleTile.x * 64, _selectCheck.rc.top + _currentSampleTile.y * 64 + _tileScroll.y / 64 * 64 - 50, 80);

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			//Rectangle(getMemDC(), _sampleTiles[i].rc);
		}

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);


		IMAGEMANAGER->render("����Ʋ", getMemDC(), _mapT.rc.left, _mapT.rc.top);
		IMAGEMANAGER->render("��������Ʋ", getMemDC(), _mapT.rc.left+23, _mapT.rc.top+23);
		IMAGEMANAGER->loopAlphaRender("����Ÿ��Ʋ", getMemDC(), &_title.rc, -loopSpeed, 0, 150);

		IMAGEMANAGER->render("����", getMemDC(), _rcSave.left - 2, _rcSave.top - 2);
		IMAGEMANAGER->render("�ҷ�����", getMemDC(), _rcLoad.left - 2, _rcLoad.top - 2);
		IMAGEMANAGER->render("��ġ��", getMemDC(), _rcEraser.left - 2, _rcEraser.top - 2);
		IMAGEMANAGER->render("����", getMemDC(), _rcClear.left - 2, _rcClear.top - 2);

		IMAGEMANAGER->render("��", getMemDC(), _selectTile[0].rc.left - 2, _selectTile[0].rc.top - 2);
		IMAGEMANAGER->render("�Ƕ�̵�", getMemDC(), _selectTile[1].rc.left - 2, _selectTile[1].rc.top - 2);
		IMAGEMANAGER->render("�����", getMemDC(), _selectTile[2].rc.left - 2, _selectTile[2].rc.top - 2);
		IMAGEMANAGER->render("������Ʈ", getMemDC(), _selectTile[3].rc.left - 2, _selectTile[3].rc.top - 2);
		IMAGEMANAGER->render("��", getMemDC(), _mobButton.rc.left - 2, _mobButton.rc.top - 2);

		IMAGEMANAGER->render("Ÿ���浹", getMemDC(), _rcTerrain.left - 2, _rcTerrain.top - 2);
		IMAGEMANAGER->render("���浹", getMemDC(), _rcObject.left - 2, _rcObject.top - 2);
		IMAGEMANAGER->render("�缱", getMemDC(), _rcDiagonal.left - 2, _rcDiagonal.top - 2);
		IMAGEMANAGER->frameRender("������", getMemDC(), _rcReverse.left - 2, _rcReverse.top - 2, _indexReverse, 0);

		//IMAGEMANAGER->render("saved", getMemDC(), _rcSaveFile.left, _rcSaveFile.top);

		_saveFilespaceImage[_isSaved[_saveFileNum-1]]->render(getMemDC(), _rcSaveFile.left, _rcSaveFile.top);

		//���������ư
		addBgButton->render(getMemDC(), _rcAddBg.left, _rcAddBg.top, _bgNum * 16, 0, 16,20);
		IMAGEMANAGER->frameRender("savedNum", getMemDC(), _rcSaveFile.right - 28, _rcSaveFile.top, _saveFileNum-1, 0);

		//���ʹ�Ÿ�ϰ���............////////////////////
		IMAGEMANAGER->loopRender("����", getMemDC(), &_mobMap.rc, _count, 0);
		IMAGEMANAGER->render("���ʹ̻���Ÿ�Ϲ��", getMemDC(), _mobMap.rc.left, _mobMap.rc.top);
		//_mapAni[1]->rotateFrameRender(getMemDC(), _crazyDog.rc.left + 70, _crazyDog.rc.top + 45, crazyDogRotateRate);
		//_mapAni[1]->rotateFrameRender(getMemDC(), _mobMap.rc.right - 70, _mobMap.rc.top , crazyDogRotateRate);



		//��ư��Ʈ ����
		//Rectangle(getMemDC(), _rcSave);
		//Rectangle(getMemDC(), _rcLoad);
		//Rectangle(getMemDC(), _rcClear);
		//Rectangle(getMemDC(), _rcEraser);

		//Rectangle(getMemDC(), _rcTerrain);
		//Rectangle(getMemDC(), _rcObject);
		//Rectangle(getMemDC(), _rcDiagonal);
		//Rectangle(getMemDC(), _rcReverse);

		//Rectangle(getMemDC(), _rcAddBg);
		//Rectangle(getMemDC(), _rcSaveFile);
		//Rectangle(getMemDC(), _mobMap.rc);
		//Rectangle(getMemDC(), _mobTile.rc);
		//Rectangle(getMemDC(), _crazyDog.rc);

		for (int i = 0; i < 12; ++i)
		{
			//Rectangle(getMemDC(), _enemySampleTiles[i].rc);
		}

		for (int i = 0; i < TILEKIND; ++i)
		{
			//Rectangle(getMemDC(), _selectTile[i].rc);
		}

		for (int i = 0; i < 12; ++i)
		{

			_enemySampleTiles[i]._image->frameRender(getMemDC(), _enemySampleTiles[i].rc.left + 19, _enemySampleTiles[i].rc.top -5 , _enemySampleTiles[i]._index, 0);

		}

	
		

		//��ư��Ʈ �۾�
		//SetBkMode(getMemDC(), TRANSPARENT);
		//TextOut(getMemDC(), _rcSave.left + 5, _rcSave.top + 10, "SAVE", strlen("SAVE"));
		//TextOut(getMemDC(), _rcSave.left + 5, _rcSave.top + 10, "SAVE", 3); // ���̰� ���� ������ �׸�ŭ ���Գ��´�
		//TextOut(getMemDC(), _rcLoad.left + 5, _rcLoad.top + 10, "LOAD", strlen("LOAD"));
		//TextOut(getMemDC(), _rcClear.left + 5, _rcClear.top + 10, "CLEAR", strlen("CLEAR"));
		//TextOut(getMemDC(), _rcEraser.left + 5, _rcEraser.top + 10, "ERASER", strlen("ERASER"));
		//TextOut(getMemDC(), _rcTerrain.left + 5, _rcTerrain.top + 10, "TERRAIN", strlen("TERRAIN"));
		//TextOut(getMemDC(), _rcObject.left + 5, _rcObject.top + 10, "OBJECT", strlen("OBJECT"));
		//TextOut(getMemDC(), _rcDiagonal.left + 5, _rcDiagonal.top + 10, "DIAGONAL", strlen("DIAGONAL"));
		//TextOut(getMemDC(), _rcReverse.left + 5, _rcReverse.top + 10, "REVERSE", strlen("REVERSE"));

		//TextOut(getMemDC(), _rcAddBg.left + 5, _rcAddBg.top + 10, "ADDBG", strlen("ADDBG"));


		HFONT myFont1 = CreateFont(20, 8, 0, 0, 600, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Harrington");
		HFONT oldFont1 = (HFONT)SelectObject(getMemDC(), myFont1);
		SetTextColor(getMemDC(), RGB(255,255,255));
		TextOut(getMemDC(), _title.rc.left + 5, _title.rc.top, "MapTool", strlen("MapTool"));
		SelectObject(getMemDC(), oldFont1); 
		DeleteObject(myFont1);
	
	}

}

void maptoolScene1::maptoolSetup(void)
{
	//��Ʈ��ġ �ʱ�ȭ
	_rcSave = RectMake(_mapT.rc.right - 50 - 30, _mapT.rc.bottom - 170, 50, 30);
	_rcLoad = RectMake(_mapT.rc.right - 50 - 30, _mapT.rc.bottom - 140 + 5, 50, 30);
	_rcClear = RectMake(_mapT.rc.right - 50 - 30, _mapT.rc.bottom - 110 + 5 + 5, 50, 30);
	_rcEraser = RectMake(_mapT.rc.right - 50 - 30, _mapT.rc.bottom - 80 + 5 + 5 + 5, 50, 30);
	//
	_rcTerrain = RectMake(_mapT.rc.left	+ 30, _mapT.rc.bottom - 85, 50, 50);
	_rcObject = RectMake(_mapT.rc.left + 30 + 70, _mapT.rc.bottom - 85, 50, 50);
	_rcDiagonal = RectMake(_mapT.rc.left + 30 + 70 + 70, _mapT.rc.bottom - 85, 50, 50);
	_rcReverse = RectMake(_mapT.rc.left + 30 + 70 + 70 + 70, _mapT.rc.bottom - 85, 50, 50);
	//��� �ø���
	_rcAddBg = RectMake(_mapT.rc.right - 50 - 30 - 30, _mapT.rc.bottom - 170 + 35, 20, 20);
	//����Ҽ���
	_rcSaveFile = RectMake(_mapT.rc.left + 30 + 70 + 70 + 70 + 70, _mapT.rc.bottom - 85, 70, 50);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; j++)
		{

			_selectTile[i * 2 + j].x = _mapT.rc.right - 115 + 55 * i;
			_selectTile[i * 2 + j].y = _mapT.rc.top + 30 + 35 * j;
			_selectTile[i * 2 + j].rc = RectMake(_selectTile[i * 2 + j].x, _selectTile[i * 2 + j].y, 50, 30);
		}

	}

	//��Ÿ�Ϲ�ư///////////////////////////////////////
	_mobButton.rc = RectMake(_mapT.rc.right - 115 , _mapT.rc.top + 30 + 35 * 2, 100, 30);


	//������ ����Ÿ�� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < _sampleTileY; i++)
	{
		for (int j = 0; j < _sampleTileX; j++)
		{
			_sampleTiles[i * _sampleTileX + j].rc = RectMake(_tileScroll.rc.left + j * TILESIZE, _tileScroll.rc.top+ i * TILESIZE , TILESIZE, TILESIZE );

			//��������
			_sampleTiles[i * _sampleTileX + j].terrainFrameX = j;
			_sampleTiles[i * _sampleTileX + j].terrainFrameY = i;
		}
	}


}

void maptoolScene1::setMap(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _isDraw )
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				_preX = _ptMouse.x + CAMERAMANAGER->getVCam("����ķ")[0].rc.left;
				_preY = _ptMouse.y + CAMERAMANAGER->getVCam("����ķ")[0].rc.top;

			}
		}
	}



	if (KEYMANAGER->isToggleKey('M'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_isDraw)// && !_isMobMapChecked)
		{
			for (int i = 0; i < _sampleTileX * _sampleTileY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rc, _ptMouse) && PtInRect(&_selectCheck.rc, _ptMouse))
				{
					_currentTile.x = _sampleTiles[i].terrainFrameX;
					_currentTile.y = _sampleTiles[i].terrainFrameY;
					break;
				}
			}
		}

		for (int i = 0; i < _sampleTileX * _sampleTileY; i++)
		{
			if (PtInRect(&_sampleTiles[i].rc, _ptMouse) && PtInRect(&_selectCheck.rc, _ptMouse))
			{
				_currentSampleTile.x = _sampleTiles[i].terrainFrameX;
				_currentSampleTile.y = _sampleTiles[i].terrainFrameY;
				break;
			}
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _isDraw)
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				_endX = _ptMouse.x + CAMERAMANAGER->getVCam("����ķ")[0].rc.left;
				_endY = _ptMouse.y + CAMERAMANAGER->getVCam("����ķ")[0].rc.top;
			}
		}

		if (_preX < _endX && _preY < _endY)
			_rct = RectMake(_preX, _preY, sqrtf((_endX - _preX)*(_endX - _preX)), sqrtf((_endY - _preY)*(_endY - _preY)));
		else if (_preX < _endX && _preY > _endY)
			_rct = RectMake(_preX, _endY, sqrtf((_endX - _preX)*(_endX - _preX)), sqrtf((_endY - _preY)*(_endY - _preY)));
		else if (_preX > _endX && _preY < _endY)
			_rct = RectMake(_endX, _preY, sqrtf((_endX - _preX)*(_endX - _preX)), sqrtf((_endY - _preY)*(_endY - _preY)));
		else if (_preX > _endX && _preY > _endY)
			_rct = RectMake(_endX, _endY, sqrtf((_endX - _preX)*(_endX - _preX)), sqrtf((_endY - _preY)*(_endY - _preY)));

		for (int i = 0; i < TILEX*TILEY; ++i)
		{

			if (IntersectRect(&_rct2, &_rct, &_tiles[i].rc))
			{
				_tiles[i].isPreView = true;
			}
			else
			{
				_tiles[i].isPreView = false;
			}
		}
	}


	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _isDraw)
	{
		for (int i = 0; i < TILEX*TILEY; ++i)
		{

			if (_tiles[i].isPreView)
			{
				//�����ư�� �����̳�?
				if (_ctrlSelect == CTRL_DONTPASS)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					//_tiles[i].obj = OBJECT_NONE;
					_tiles[i].tileType = _selectTileType;
					_tiles[i].objectType = _selectObjectType;
					_tiles[i].reverse = _selectTileDir;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			
				}
				//�����ư�� ������Ʈ��?
				if (_ctrlSelect == CTRL_DOPASS)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;
					//_tiles[i].terrain = TR_NONE;
					_tiles[i].tileType = _selectTileType;
					_tiles[i].objectType = _selectObjectType;
					_tiles[i].reverse = _selectTileDir;
					_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
				}
				//�����ư�� ���찳��?
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tiles[i].objFrameX = 3;
					_tiles[i].objFrameY = 0;
					_tiles[i].tileType = _selectTileType;
					_tiles[i].objectType = _selectObjectType;
					_tiles[i].reverse = _selectTileDir;
					_tiles[i].obj = OBJECT_NONE;
					_tiles[i].terrain = TR_NONE;
				}
				//�����ư�� �밢���̳�?
				if (_ctrlSelect == CTRL_DIAGONAL)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].tileType = _selectTileType;
					_tiles[i].objectType = _selectObjectType;
					_tiles[i].reverse = _selectTileDir;
					//_tiles[i].obj = OBJECT_NONE;
					_tiles[i].terrain = TR_DIAGONAL;
				}
			}

		}
		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			_tiles[i].isPreView = false;
		}
		_rct = RectMake(-1000, -1000, 1, 1);

	}
	
}

void maptoolScene1::save(int saveFileNum)
{
	_isSaved[saveFileNum -1] = true;


	///////////////////////////////////////
	string str;
	str = "save" + to_string(saveFileNum) + ".map";

	HANDLE file;
	DWORD write;

	file = CreateFile(str.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL); // ������ ��ü�� ũ�� �־���⶧���� ���⼱ ������ �ȳ��� �־���!

	CloseHandle(file);
	
	///////////////////////////////////////

	
	//itoa => ������ ���ڷ�

	string strEnemy;
	strEnemy = "enemyInf" + to_string(saveFileNum) + ".txt";
	TXTDATA->saveTXT(strEnemy.c_str(), _vEnemyInf);
	


	///////////////////////////////////////
	char temp[128];
	vector<string> vStr;
	//itoa => ������ ���ڷ�

	for (int fileNum = 0; fileNum < SAVEFILES ; ++fileNum)
	{
		vStr.push_back(itoa(_isSaved[fileNum], temp, 20));
	}

	TXTDATA->saveTXT("if_file_saved.txt", vStr);

	




}

void maptoolScene1::load(int saveFileNum)
{
	string str;
	str = "save" + to_string(saveFileNum) + ".map";

	HANDLE file;
	DWORD read;

	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);


	strEnemy = "enemyInf" + to_string(saveFileNum) + ".txt";
	_vEnemyInf = TXTDATA->loadTXT(strEnemy.c_str());

	if (!_vEnemyInf.empty())
	{
		for (int i = 0; i < _vEnemyInf.size(); i += 3)
		{
			mapToolRc _enemyRc;
			_enemyRc.type = atoi(_vEnemyInf[i].c_str());
			_enemyRc.x = atoi(_vEnemyInf[i + 1].c_str());
			_enemyRc.y = atoi(_vEnemyInf[i + 2].c_str());
			_enemyRc.rc = RectMakeCenter(_enemyRc.x, _enemyRc.y, 100, 100);

			_vEnemyRc.push_back(_enemyRc);

			/*_vEnemyRc[i].type = atoi(_vEnemyInf[i].c_str());
			_vEnemyRc[i].x = atoi(_vEnemyInf[i + 1].c_str());
			_vEnemyRc[i].y = atoi(_vEnemyInf[i + 2].c_str());
			_vEnemyRc[i].rc = RectMakeCenter(_vEnemyRc[i].x, _vEnemyRc[i].y, 100, 100);*/
		}

	}
	
}

void maptoolScene1::clear()
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		_tiles[i].obj = OBJECT_NONE;
		_tiles[i].terrain = TR_NONE;
		_tiles[i].tileType = _selectTileType;
		_tiles[i].objectType = _selectObjectType;
		_tiles[i].objFrameX = 10;
		_tiles[i].objFrameY = 13;
	}
}

void maptoolScene1::reverse()
{
	if (_selectTileDir == 0)
	{
		_selectTileDir = 1;
	}
	else if(_selectTileDir == 1)
	{
		_selectTileDir = 0;
	}


}

void maptoolScene1::animation()
{
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > _mapAni[0]->getMaxFrameX())
		{
			_index = 0;
		}
		_mapAni[0]->setFrameX(_index);
	}
	if (_count % 3 == 0)
	{
		_index++;
		if (_index > _mapAni[1]->getMaxFrameX())
		{
			_index = 0;
		}
		_mapAni[1]->setFrameX(_index);
	}

	if (_count % 10 == 0)
	{
		_indexReverse++;
		if (_indexReverse > reverseButton->getMaxFrameX())
		{
			_indexReverse = 0;
		}
		reverseButton->setFrameX(_indexReverse);
	}
}

void maptoolScene1::mapToolOnOff()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (!_isDraw)
		{
			_isDraw = true;
			_isMobMapChecked = false;
		}
		else
			_isDraw = false;
	}

	//��������
	if (!_isDraw)
	{
		this->maptoolSetup();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rcSave, _ptMouse))
			{
				_ctrlSelect = CTRL_SAVE;
				this->save(_saveFileNum);
			}
			if (PtInRect(&_rcLoad, _ptMouse))
			{
				_ctrlSelect = CTRL_LOAD;
				_vEnemyInf.clear();
				_vEnemyRc.clear();
				this->load(_saveFileNum);
			}
			if (PtInRect(&_rcClear, _ptMouse))
			{
				_ctrlSelect = CTRL_CLEAR;
				this->clear();
			}
			if (PtInRect(&_rcEraser, _ptMouse))
			{
				_ctrlSelect = CTRL_ERASER;
			}
			if (PtInRect(&_rcTerrain, _ptMouse))
			{
				_ctrlSelect = CTRL_DONTPASS;
				_selectTileType = typeNum;

			}
			if (PtInRect(&_rcObject, _ptMouse))
			{
				_ctrlSelect = CTRL_DOPASS;
				_selectObjectType = typeNum;
			}
			if (PtInRect(&_rcDiagonal, _ptMouse))
			{
				_ctrlSelect = CTRL_DIAGONAL;
			}
			if (PtInRect(&_rcReverse, _ptMouse))
			{
				_ctrlSelect = CTRL_REVERSE;
				this->reverse();
			}
			if (PtInRect(&_rcAddBg, _ptMouse))
			{
				_ctrlSelect = CTRL_ADDBG;
				_bgNum++;
				if (_bgNum == 6)
					_bgNum = 0;
			}
			if (PtInRect(&_rcSaveFile, _ptMouse))
			{
				//_ctrlSelect = CTRL_ADDBG;
				_saveFileNum++;
				if (_saveFileNum > SAVEFILES)
				{
					_saveFileNum = 1;
				}
				_vEnemyInf.clear();
			}
			//if (PtInRect(&_rcSaveFile, _ptMouse))
			//{
			//	_ctrlSelect = CTRL_SAVEFILE;
			//	//this->reverse();
			//}
			if (PtInRect(&_mobButton.rc, _ptMouse))
			{
				if (!_isMobMapChecked)
					_isMobMapChecked = true;
				else
					_isMobMapChecked = false;

			}

			for (int i = 0; i < TILEKIND; ++i)
			{
				if (PtInRect(&_selectTile[i].rc, _ptMouse))
				{
					typeNum = i;
				}
			}

			for (int i = 0; i < 12; ++i)
			{
				if (PtInRect(&_enemySampleTiles[i].rc, _ptMouse))
				{
					_choiceEnemyType = _enemySampleTiles[i]._typeNum;
					_addEnemy = true;
				}
			}
		}
	}
}

void maptoolScene1::mouseWheel()
{
	if (_Mwheel > 0)
	{
		if (_tileScroll.y < _mapT.y + 30)
			_tileScroll.y += 64;
		_Mwheel = 0;
	}
	else if (_Mwheel < 0)
	{
		if (_tileScroll.y + _sampleTile[typeNum][_selectTileDir]->getHeight() > _mapT.y + 30 + 256)
			_tileScroll.y -= 64;
		_Mwheel = 0;
	}

	_tileScroll.rc = RectMake(_tileScroll.x, _tileScroll.y, 448, _sampleTile[_selectTileType][_selectTileDir]->getHeight());
}

void maptoolScene1::cameraClipping()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && x > 0 + WINSIZEX / 2)
	{
		x -= 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && x < TILEXBASE*TILESIZE - WINSIZEX / 2)
	{
		x += 20;

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && y > 0 + WINSIZEY / 2)
	{
		y -= 20;

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && y < TILEY*TILESIZE - WINSIZEY / 2)
	{
		y += 20;

	}

	CAMERAMANAGER->bgCameraUpdate("����ķ", x, y, 1280 * 4, 720 * 4);
	renderX = CAMERAMANAGER->getVCam("����ķ")[0].rc.left / TILESIZE;
	renderY = CAMERAMANAGER->getVCam("����ķ")[0].rc.top / TILESIZE;
}



TERRAIN maptoolScene1::terrainSelect(int frameX, int frameY)
{

	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 1; j < 12; ++j)
		{
			if (frameX == i && frameY == j)
				return TR_DOPASS;
		}
	}

	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 14; j < 16; ++j)
		{
			if (frameX == i && frameY == j)
				return TR_ROOF;

		}
	}

	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 16; j < 18; ++j)
		{
			if (frameX == i && frameY == j)
				return TR_BOMB;
		}
	}

	return TR_GROUND;
}

OBJECT maptoolScene1::objectSelect(int frameX, int frameY)
{
	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 1; j < 12; ++j)
		{
			if (frameX == i && frameY == j)
				return OBJECT_DOPASS;
		}
	}

	for (int i = 0; i < SAMPLETILEX; ++i)
	{
		for (int j = 12; j < 14; ++j)
		{
			if (frameX == i && frameY == j)
				return OBJECT_BGTILE;
		}
	}

	if (frameX == 3 && frameY == 11)
	{
		return OBJECT_DONTPASS;
	}

	return ALLOBJECT;
}

void maptoolScene1::enemySampleTile()
{

	//����Ÿ��
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			_enemySampleTiles[i * 4 + j].rc = RectMake(_mobMap.rc.left + 112 * j, _mobMap.rc.top + 85 * i, 112, 85);
			_enemySampleTiles[i * 4 + j]._typeNum = i * 4 + j;
		}
	}

	if (_isMobMapChecked)
	{
		if (_mobMap.y < _selectCheck.rc.bottom - 258)
		{
			_mobMap.y += 6;
		}
	}
	else
	{
		if(_mobMap.y > -350)
			_mobMap.y -= 6;
	}
	_mobMap.rc = RectMake(_mobMap.x, _mobMap.y, 448, 256);
	_crazyDog.rc = RectMake(_mobMap.rc.left +20 , _mobMap.rc.top , 128, 128);


	for (int i = 0; i < 12; ++i)
	{
		if (_enemySampleTiles[i]._isTouched)
		{
			if (_count % 5 == 0)
			{
				_enemySampleTiles[i]._index++;
				if (_enemySampleTiles[i]._index > _enemySampleTiles[i]._image->getMaxFrameX())
				{
					_enemySampleTiles[i]._index = 0;
				}



			}

			_enemySampleTiles[i]._image->setFrameX(_enemySampleTiles[i]._index);

		}

	}
	for (int i = 0; i < 12; ++i)
	{
		if (PtInRect(&_enemySampleTiles[i].rc, _ptMouse))
		{
			_enemySampleTiles[i]._isTouched = true;
		}
		else
			_enemySampleTiles[i]._isTouched = false;
	}
	

	if(_count%100<50)
		crazyDogRotateRate += 0.008f;
	else
		crazyDogRotateRate -= 0.008f;


	//���ʹ� ����

	/*if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _isMobMapChecked)
	{
		
		
	}*/
	
	if (KEYMANAGER->isOnceKeyDown('A') && _addEnemy && _isDraw)
	{


		char temp[200];

		_vEnemyInf.push_back(itoa(_choiceEnemyType, temp, 10));
		_vEnemyInf.push_back(itoa(_ptMouse.x + CAMERAMANAGER->getVCam("����ķ")[0].rc.left, temp, 10));
		_vEnemyInf.push_back(itoa(_ptMouse.y + CAMERAMANAGER->getVCam("����ķ")[0].rc.top, temp, 10));

		
		
		_enemyRc.x = _ptMouse.x + CAMERAMANAGER->getVCam("����ķ")[0].rc.left;
		_enemyRc.y = _ptMouse.y + CAMERAMANAGER->getVCam("����ķ")[0].rc.top;
		_enemyRc.rc = RectMakeCenter(_enemyRc.x, _enemyRc.y, 100, 100);
		_enemyRc.type = _choiceEnemyType;

		_vEnemyRc.push_back(_enemyRc);
	}

	if (KEYMANAGER->isOnceKeyDown('D'))// && _addEnemy && _isDraw)
	{
		if (!_vEnemyInf.empty() && !_vEnemyRc.empty())
		{
			_vEnemyInf.pop_back();
			_vEnemyInf.pop_back();
			_vEnemyInf.pop_back();

			_vEnemyRc.pop_back();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _addEnemy && _isDraw)
	{
		_addEnemy = false;

	}





}