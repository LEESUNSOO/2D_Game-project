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
	tagTile _tiles[TILEX * TILEY];	//왼쪽화면 타일(총 400개)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽화면 타일(총 210개)
	tagCurrentTile _currentTile;	//현재타일
	tagCurrentTile _currentSampleTile;

	//버튼							
	RECT _rcSave, _rcLoad, _rcClear , _rcEraser, // 우측하단
		_rcTerrain, _rcObject, _rcDiagonal, _rcReverse, // 좌측하단
		_rcAddBg, _rcSaveFile, // 중앙부
		_rcEnemy, _rcItem; // 우측 중앙

	//이넘
	CTRL _ctrlSelect;
	SELECT_TYPE _choiceType;

	//맵툴본체
	mapToolRc _mapT;
	int loopSpeed;
	image* _mapAni[2]; // 예리나랑 
	

	//맵툴의 프레임 인덱스, 주기를 담당
	int _index, _indexReverse, _count;

	//리버스버튼
	image* reverseButton;
	//배경추가버튼
	image* addBgButton;

	//저장폴더선택
	image* _saveFilespaceImage[SAVEFILES];
	bool _isSaved[SAVEFILES];
	int _saveFileNum;



	//맵툴부속렉트
	mapToolRc _selectCheck;	//선택가능구역
	mapToolRc _tileScroll;	//타일 스크롤 구역
	mapToolRc _selectTile[TILEKIND];	//숲, 사막, 아이스, 오브젝트로 구성
	mapToolRc _title;	//말그대로 타이틀 렉트
	mapToolRc _mobButton;

	


	int typeNum;	// 숲, 사막, 아이스, 오브젝트 중 무엇인지를 가르키는 숫자


	//샘플타일종류
	image* _sampleTile[4][2]; // 타입/리버스유무를 담은 이미지
	int _sampleTileX, _sampleTileY; //샘플타일의 시작점
	int _selectTileType; // 그려줄 때 오브젝트의 숫자와 아 근데 이거 의미없는거같네?
	int _selectObjectType; // 그려줄 때 오브젝트의 숫자와 아 근데 이거 의미없는거같네?
	int _selectTileDir; // 리버스 유무 이것도 생각해보니 딱히??

	//배경
	image* _bgImage[BGIMAGEKIND]; //배경종류 >>>>>>>>>> 아마 이거는 숲1, 숲2, 마을, 해안가, 피라미드 (5개로 확장해야할 듯)
	int _bgNum; // 맵툴 배경에 이미지를 몇개 깔아줄지 결정하는 숫자네 ㅎ

	bool _isDraw; // 맵툴을 켰을때랑 껐을때 배경에 타일이 입혀지지 않도록 하게 하기위한 불값 추가

	//드래그 땜시 만든
	float _preX, _preY, _endX, _endY;
	RECT _rct, _rct2;

	//카메라 땜시
	float x, y;
	int renderX, renderY;


	////////////////////////////////에너미샘플타일//////////////////////////////////

	tagEnemySampleTile _enemySampleTiles[ENEMYS]; //12숫자 변동을 주려면 아무래도 좀 수정을 해야함 되도록 12로 ㄱㄱ
	mapToolRc _mobMap; //몬스터 샘플타일정도?
	mapToolRc _crazyDog;
	bool _isMobMapChecked;
	bool _addEnemy;
	float crazyDogRotateRate; // 생략가능
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


	//맵툴세팅
	void maptoolSetup(void); //초기화에 넣어두면 된다
	//맵세팅
	void setMap(void);
	//세이브
	void save(int saveFileNum);
	//로드
	void load(int saveFileNum);
	//클리어
	void clear();
	//리버스
	void reverse();
	//애니메이션
	void animation();
	//맵툴온오프
	void mapToolOnOff();
	//휠스크롤
	void mouseWheel();
	//카메라, 클리핑
	void cameraClipping();
	//에너미 샘플 맵
	void enemySampleTile();



	//지형, 오브젝트 셋터
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	maptoolScene1() {}
	~maptoolScene1() {}
};