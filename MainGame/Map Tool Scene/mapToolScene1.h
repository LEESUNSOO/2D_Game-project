#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define BGIMAGEKIND 2
#define TILEKIND 4
#define SAVEFILES 15
#define ENEMYS 12
struct mapToolRc
{
	float x, y;
	RECT rc;
	image* _image;
	int type;

};
class maptoolScene1 : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//����ȭ�� Ÿ��(�� 400��)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ȭ�� Ÿ��(�� 210��)
	tagCurrentTile _currentTile;	//����Ÿ��
	tagCurrentTile _currentSampleTile;

	//��ư							
	RECT _rcSave, _rcLoad, _rcClear , _rcEraser, // �����ϴ�
		_rcTerrain, _rcObject, _rcDiagonal, _rcReverse, // �����ϴ�
		_rcAddBg, _rcSaveFile, // �߾Ӻ�
		_rcEnemy, _rcItem; // ���� �߾�

	//�̳�
	CTRL _ctrlSelect;
	SELECT_TYPE _choiceType;

	//������ü
	mapToolRc _mapT;
	int loopSpeed;
	image* _mapAni[2]; // �������� 
	

	//������ ������ �ε���, �ֱ⸦ ���
	int _index, _indexReverse, _count;

	//��������ư
	image* reverseButton;
	//����߰���ư
	image* addBgButton;

	//������������
	image* _saveFilespaceImage[SAVEFILES];
	bool _isSaved[SAVEFILES];
	int _saveFileNum;



	//�����μӷ�Ʈ
	mapToolRc _selectCheck;	//���ð��ɱ���
	mapToolRc _tileScroll;	//Ÿ�� ��ũ�� ����
	mapToolRc _selectTile[TILEKIND];	//��, �縷, ���̽�, ������Ʈ�� ����
	mapToolRc _title;	//���״�� Ÿ��Ʋ ��Ʈ
	mapToolRc _mobButton;

	


	int typeNum;	// ��, �縷, ���̽�, ������Ʈ �� ���������� ����Ű�� ����


	//����Ÿ������
	image* _sampleTile[4][2]; // Ÿ��/������������ ���� �̹���
	int _sampleTileX, _sampleTileY; //����Ÿ���� ������
	int _selectTileType; // �׷��� �� ������Ʈ�� ���ڿ� �� �ٵ� �̰� �ǹ̾��°Ű���?
	int _selectObjectType; // �׷��� �� ������Ʈ�� ���ڿ� �� �ٵ� �̰� �ǹ̾��°Ű���?
	int _selectTileDir; // ������ ���� �̰͵� �����غ��� ����??

	//���
	image* _bgImage[BGIMAGEKIND]; //������� >>>>>>>>>> �Ƹ� �̰Ŵ� ��1, ��2, ����, �ؾȰ�, �Ƕ�̵� (5���� Ȯ���ؾ��� ��)
	int _bgNum; // ���� ��濡 �̹����� � ������� �����ϴ� ���ڳ� ��

	bool _isDraw; // ������ �������� ������ ��濡 Ÿ���� �������� �ʵ��� �ϰ� �ϱ����� �Ұ� �߰�

	//�巡�� ���� ����
	float _preX, _preY, _endX, _endY;
	RECT _rct, _rct2;

	//ī�޶� ����
	float x, y;
	int renderX, renderY;


	////////////////////////////////���ʹ̻���Ÿ��//////////////////////////////////

	tagEnemySampleTile _enemySampleTiles[ENEMYS]; //12���� ������ �ַ��� �ƹ����� �� ������ �ؾ��� �ǵ��� 12�� ����
	mapToolRc _mobMap; //���� ����Ÿ������?
	mapToolRc _crazyDog;
	bool _isMobMapChecked;
	bool _addEnemy;
	float crazyDogRotateRate; // ��������
	int _choiceEnemyType;
	vector<string> _vEnemyInf;
	string strEnemy;
	mapToolRc _enemyRc;
	vector<mapToolRc> _vEnemyRc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	//��������
	void maptoolSetup(void); //�ʱ�ȭ�� �־�θ� �ȴ�
	//�ʼ���
	void setMap(void);
	//���̺�
	void save(int saveFileNum);
	//�ε�
	void load(int saveFileNum);
	//Ŭ����
	void clear();
	//������
	void reverse();
	//�ִϸ��̼�
	void animation();
	//�����¿���
	void mapToolOnOff();
	//�ٽ�ũ��
	void mouseWheel();
	//ī�޶�, Ŭ����
	void cameraClipping();
	//���ʹ� ���� ��
	void enemySampleTile();



	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	maptoolScene1() {}
	~maptoolScene1() {}
};