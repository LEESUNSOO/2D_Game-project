#pragma once

//����ȭ��Ÿ�� (ȭ�� ����) 
#define TILESIZE 64
#define TILEX 80
#define TILEY 45
// #define TILEY 33 fps 38

#define TILEXBASE 80


#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//�̹���Ÿ�� (ȭ�� �����ʻ��)
#define SAMPLETILEX 7
#define SAMPLETILEY 30

//�����Ӽ��� ������� �����ϱ�
//��Ʈ������ �Ұ�� �ӵ��� �����⶧���� ����Ѵ�
//������ �����ϰ� �Һ����� ó���ص� �ȴ�

//||(or), &&(and)
//|(or), &(and)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
//#define ATTR_UNMOVAL 0x00000001
//#define ATTR_POISON	0x00000002


//�������� ����� �̳ѹ�
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
//����
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER,TR_DIAGONAL,
	TR_NONE, TR_DOPASS, TR_ROOF, TR_BOMB, TR_END
};

//������Ʈ
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

//��ġ��ǥ
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

/*Ÿ�ϱ���ü*/
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

//�̹��� Ÿ�ϱ���ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	
};

//���ʹ� Ÿ�� ����ü
struct tagEnemySampleTile
{
	
	RECT rc;
	image* _image;
	int _typeNum; //enum�� ����
	bool _isTouched;
	int _index;


};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};

//���� Ÿ��
struct tagMobTile
{
	RECT rc;
	int x, y;
	RABIMOB _type;


};

