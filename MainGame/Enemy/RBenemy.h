#pragma once
#include "tileNode.h"
#include "stage_MAPt.h"


class RBenemy
{
protected:
	ENEMY_TYPE _eType;
	ENEMY_STATE _eState;
	ENEMY_DIRECT _eDir;

	tagPos pos;
	float speed;
	float jumpSpeed;
	float angle;
	float gravity;

	int hp;

	int index, count, indexY;
	int frameSpeed;
	int jumpCount;


	image* _image[8];

	// 타일맵 충돌처리

	int _collisionTileIndex[11];
	int _currentTileX, _currentTileY;

	//피격시
	bool _isAttacted;
	bool _dontMove;
	int invincibleStateCount;
	int invincibleAlpha;

	RECT rc;;
	RECT realSizeRc;
	RECT tileCollRc;
	RECT bottomTileCheckRc;
	RECT topTileCheckRc;
	RECT pixelRc;
	RECT beAttRc;

	//댐스관련
	float damsX, damsY;
	RECT damsRc;

	bool isFall;
	bool _isHeadCollide;
	bool _isLRCollide;

	bool isTrace;
	bool isActived; //활성 여부
	bool isDead;
	// bool isFire; // 총알 및 스킬 발사여부(모든 몹에게 필수가 아니므로 주석)


public:

	virtual void init();
	virtual void update(stage_MAPt* _maps);
	virtual void animation();
	virtual void tileMapCollision(stage_MAPt* _maps);
	virtual void makingRc();
	virtual void move(stage_MAPt* _maps);


	void setPosition(float _x, float _y) { pos.x = _x; pos.y = _y; }



	RECT getRealSizeRc() { return realSizeRc; }
	RECT getBottomRc() { return bottomTileCheckRc; }
	RECT getPixelRc() { return pixelRc; }
	RECT getTopRc() { return topTileCheckRc; }
	RECT getTileRc() { return tileCollRc; }
	RECT getDamsRc() { return damsRc; }

	image* getImage(ENEMY_STATE _state) { return _image[_state]; }
	ENEMY_STATE getState() { return _eState; }
	void setState(ENEMY_STATE eState) { _eState = eState; }
	ENEMY_DIRECT getDirection() { return _eDir; }
	void setDirection(ENEMY_DIRECT eDir) { _eDir = eDir; }

	tagPos getPos() { return pos; }
	void setPos(tagPos _pos) { pos = _pos; }
	void setX(float _x) { pos.x = _x; }
	void setY(float _y) { pos.y = _y; }

	float getHp() { return hp; }
	void setHp(float _hp) { hp = _hp; }

	float getAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	float getDamsX() { return damsX; }
	void setDamsX(float _damsX) { damsX = _damsX; }

	float getDamsY() { return damsY; }
	void setDamsY(float _damsY) { damsY = _damsY; }

	int getIndexX() { return index; }
	int getindexY() { return indexY; }

	bool getIsActive() { return isActived; }
	void setIsActive(bool _isActived) { isActived = _isActived; }

	bool getIsDead() { return isDead; }
	void setIsDead(bool _isDead) { isDead = _isDead; }

	bool getIsTrace() { return isTrace; }
	void setIsTrace(bool _isTrace) { isTrace = _isTrace; }

	int* getCollisionTile() { return _collisionTileIndex; }

	bool getIsAttacted() { return _isAttacted; }
	void setIsAttacted(bool isAttacted) { _isAttacted = isAttacted; }

	bool getDontMove() { return _dontMove; }
	void setDontMove(bool dontMove) { _dontMove = dontMove; }


	int getInvincibleStateCount() { return invincibleStateCount; }
	void setInvincibleStateCount(int _invincibleStateCount) { invincibleStateCount = _invincibleStateCount; }

	////피격시
	//_isAttacted = false;
	//_dontMove = false;
	//invincibleStateCount = 0;
	//invincibleAlpha = 0;

};

class mushRoom : public RBenemy
{
private:

public:

	void init();
	mushRoom(){}
	~mushRoom() {}

};

class puppy : public RBenemy
{
private:

public:

	void init();
	puppy() {}
	~puppy() {}
};

class rabbit : public RBenemy
{
private:

public:

	void init();
	//void makingRc();


	rabbit() {}
	~rabbit() {}
};

class chick : public RBenemy
{
private:

public:

	void init();
	chick() {}
	~chick() {}
};

class chipmunk : public RBenemy
{
private:

public:

	void init();

	chipmunk() {}
	~chipmunk() {}
};

class bee : public RBenemy
{
private:

public:

	void init();
	bee() {}
	~bee() {}
};

class flower : public RBenemy
{
private:

public:

	void init();
	flower() {}
	~flower() {}
};

class eyes : public RBenemy
{
private:

public:

	void init();
	eyes() {}
	~eyes() {}
};

class pig : public RBenemy
{
private:

public:

	void init();
	pig() {}
	~pig() {}
};

class cat : public RBenemy
{
private:

public:

	void init();
	cat() {}
	~cat() {}
};

class capsule : public RBenemy
{
private:

public:

	void init();
	capsule() {}
	~capsule() {}
};

class magicStick : public RBenemy
{
private:

public:

	void init();
	magicStick() {}
	~magicStick() {}
};

