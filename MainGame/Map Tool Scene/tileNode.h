#pragma once

//게임화면타일 (화면 왼쪽) 
#define TILESIZE 64
#define TILEX 80
#define TILEY 45
// #define TILEY 33 fps 38

#define TILEXBASE 80


#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//이미지타일 (화면 오른쪽상단)
#define SAMPLETILEX 7
#define SAMPLETILEY 30

//지형속성을 내맘대로 정의하기
//비트연산을 할경우 속도가 빠르기때문에 사용한다
//하지만 사용안하고 불변수로 처리해도 된다

//||(or), &&(and)
//|(or), &(and)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
//#define ATTR_UNMOVAL 0x00000001
//#define ATTR_POISON	0x00000002


//맵툴에서 사용할 이넘문
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_DONTPASS, CTRL_DOPASS, CTRL_ERASER, CTRL_CLEAR,
	CTRL_DIAGONAL, CTRL_REVERSE,
	CTRL_ADDBG, CTRL_SAVEFILE,
	CTRL_SELECT_TYPE,
	TYPE_GRASS, TYPE_DESERT, TYPE_ICE, TYPE_OBJECT,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

enum SELECT_TYPE
{
	CANT, CAN, DUOBLECAN, END
};
//지형
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER,TR_DIAGONAL,
	TR_NONE, TR_DOPASS, TR_ROOF, TR_BOMB, TR_END
};

//오브젝트
enum OBJECT
{
	OBJECT_BLOCK1, OBJECT_BLOCK3, OBJECT_BLOCKS,
	OBJECT_TANK1, OBJECT_TANK2,
	OBJECT_FLAG1, OBJECT_FLAG2,
	ALLOBJECT,
	OBJECT_NONE,
	OBJECT_DOPASS,
	OBJECT_DONTPASS,
	OBJECT_BGTILE
};

enum RABIMOB
{
	A, B, C, D, E, F, G, H, I , J, K , L , MOBEND

};

//위치좌표
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

/*타일구조체*/
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int tileType;
	int objectType;

	int reverse;

	bool isPreView;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//이미지 타일구조체
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	
};

//에너미 타일 구조체
struct tagEnemySampleTile
{
	
	RECT rc;
	image* _image;
	int _typeNum; //enum과 연계
	bool _isTouched;
	int _index;


};

//현재타일 구조체
struct tagCurrentTile
{
	int x, y;
};

//몬스터 타일
struct tagMobTile
{
	RECT rc;
	int x, y;
	RABIMOB _type;


};

