#pragma once
#include "gameNode.h"
#include "tileNode.h"
struct mapRc
{
	float x;
	float y;
	RECT rc;
	int index;


};
class stage_MAPt : public gameNode
{
protected:

	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;
	int limitedX, limitedY;

	image* _sampleTile[4][2];

	float springX;
	float springY;
	
	image* _springImg;
	RECT spring;
	int springIndex;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//타일맵 로드
	virtual void load(void);
	 
	 //타일 가져오기
	virtual tagTile* getTiles(void) { return _tiles; }
	 
	 
	 //속성 가져오기
	 //DWORD* getAttribute(void) { return _attribute; }

	virtual int getL_X() { return limitedX; }
	virtual int getL_Y() { return limitedY; }

	virtual bool* getCanPass() { return _canPass; }
	virtual void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }
	 
	virtual image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }
	 
	virtual void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	virtual void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }
	 
	virtual RECT getSpringRc() { return spring; }
	

	virtual void setSpringIndex(int _index) { springIndex = _index; }
	virtual int getSpringIndex() { return springIndex; }
	virtual void setSpringX(float _x) { springX = _x; }
	virtual void setSpringY(float _y) { springY = _y; }
	virtual image* getSpringImg() { return _springImg; }

	float getSpringX() {return springX; }
	float getSpringY() {return springY; }

	stage_MAPt(){}
	virtual ~stage_MAPt(){}
};
class town_MAP : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;

	RECT spring;
	int springIndex;
	image* _sampleTile[4][2];

	RECT store;
	RECT mirHome;
	RECT restHome[2];

	RECT warp;
	int warpIndex, warpEdgeIndex, count;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringIndex(int _index) { springIndex = _index; }

	town_MAP() {}
	~town_MAP() {}
};

class stage1_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;

	RECT spring;
	int springIndex;
	image* _sampleTile[4][2];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }


	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringIndex(int _index) { springIndex = _index; }

	stage1_MAPt() {}
	~stage1_MAPt() {}
};

class stage1_1_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;
	RECT spring;
	int springIndex;
	image* _sampleTile[4][2];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringIndex(int _index) { springIndex = _index; }

	stage1_1_MAPt() {}
	~stage1_1_MAPt() {}
};

class stage1_2_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;
	RECT warp;
	int warpIndex, warpEdgeIndex, count;

	image* _sampleTile[4][2];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringIndex(int _index) { springIndex = _index; }

	stage1_2_MAPt() {}
	~stage1_2_MAPt() {}
};

class stage1_3_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;
	int saveIndexX, count;
	int saveEdgeIndexX;
	image* _sampleTile[4][2];

	RECT spring;
	RECT savePoint;

	/*float springX;
	float springY;*/
	int springIndex;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringRc(RECT _rc) { spring = _rc; }
	void setSpringIndex(int _index) { springIndex = _index; }
	int getSpringIndex() { return springIndex; }

	RECT getSavePoint() { return savePoint; }

	void setSpringX(float _x) { springX = _x; }
	void setSpringY(float _y) { springY = _y; }

	float getSpringX() { return springX; }
	float getSpringY() { return springY; }

	image* getSpringImg() { return _springImg; }

	stage1_3_MAPt() {}
	~stage1_3_MAPt() {}
};

class stage2_1_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;
	int saveIndexX, count;
	int saveEdgeIndexX;
	image* _sampleTile[4][2];

	RECT spring;
	RECT savePoint;

	/*float springX;
	float springY;*/
	int springIndex;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringRc(RECT _rc) { spring = _rc; }
	void setSpringIndex(int _index) { springIndex = _index; }
	int getSpringIndex() { return springIndex; }

	RECT getSavePoint() { return savePoint; }

	void setSpringX(float _x) { springX = _x; }
	void setSpringY(float _y) { springY = _y; }

	float getSpringX() { return springX; }
	float getSpringY() { return springY; }

	image* getSpringImg() { return _springImg; }

	stage2_1_MAPt() {}
	~stage2_1_MAPt() {}
};

class stage1_BOSS_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;

	image* _sampleTile[4][2];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringRc(RECT _rc) { spring = _rc; }
	void setSpringIndex(int _index) { springIndex = _index; }
	int getSpringIndex() { return springIndex; }

	void setSpringX(float _x) { springX = _x; }
	void setSpringY(float _y) { springY = _y; }

	float getSpringX() { return springX; }
	float getSpringY() { return springY; }

	image* getSpringImg() { return _springImg; }

	stage1_BOSS_MAPt() {}
	~stage1_BOSS_MAPt() {}
};
class stage_FinalBoss_MAPt : public stage_MAPt
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
		//DWORD _attribute[TILEX * TILEY];	//속성
	bool _canPass[TILEX*TILEY];;	//속성 (불값)

		//카메라땜에
	float x, y;
	int renderX, renderY;

	image* _sampleTile[4][2];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일맵 로드
	void load(void);

	//타일 가져오기
	tagTile* getTiles(void) { return _tiles; }


	//속성 가져오기
	//DWORD* getAttribute(void) { return _attribute; }
	bool* getCanPass() { return _canPass; }
	void setCanPass(int index, bool _pass) { _canPass[index] = _pass; }

	image* getTileImage(int type, int reverse) { return _sampleTile[type][reverse]; }

	void setTerrain(int _index, TERRAIN _TERRAIN) { _tiles[_index].terrain = _TERRAIN; }
	void setObject(int _index, OBJECT _OBJECT) { _tiles[_index].obj = _OBJECT; }

	RECT getSpringRc() { return spring; }
	void setSpringRc(RECT _rc) { spring = _rc; }
	void setSpringIndex(int _index) { springIndex = _index; }
	int getSpringIndex() { return springIndex; }

	void setSpringX(float _x) { springX = _x; }
	void setSpringY(float _y) { springY = _y; }

	float getSpringX() { return springX; }
	float getSpringY() { return springY; }

	image* getSpringImg() { return _springImg; }

	stage_FinalBoss_MAPt() {}
	~stage_FinalBoss_MAPt() {}
};
