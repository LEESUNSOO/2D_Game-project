#pragma once
#include "rabiribiBullet.h"

class yerinaT;

class RBboss
{
protected:

	//���� ���� enum��
	BOSSTYPE _bType;
	STATE _bState;
	DIRECTION _bDir;

	//���� �⺻ ����
	tagPos pos;
	float speed;
	float jumpSpeed;
	float angle;
	float gravity;
	float maxHp;
	float currentHp;
	int index;
	int count;
	int frameSpeed;
	RECT rc;

	//�ǰݽ�
	bool _isAttacted;
	bool _dontMove;
	int invincibleStateCount;
	int invincibleAlpha;



	//���� ����(��ų) ��ġ ����
	tagPos fixPos;

	//ü�¿� ���� ��ų �ܰ� ����
	int maxPhase;
	int currentPhase;

	bool isStartBattle; // ��ȭ ���� �ο��� �ʰ� �Ϸ���
	bool isReady;
	bool isDead;


	bool isStopped;// [RIBBONSKILLEND];
	bool isAttacting;
	bool isAttact[RIBBONSKILLEND];
	bool isCharging[RIBBONSKILLEND];
	bool fixSite; 
	int stopTime;
	int skillTemp;

	//�ｺ����
	float damsX, damsY;
	RECT damsRc;

	
	//������ ��ȣ����
	yerinaT* _player;


public:

	virtual void init();
	virtual void release();
	virtual void update();


	virtual void animation();
	virtual void move();
	virtual void attactPattern();
	virtual void fire();

	//void render(); //? ���� ���⼭ ���ʿ� ������?
	RECT getRect() { return rc; }
	RECT getDamsRc() { return damsRc; }

	STATE getState() { return _bState; }
	void setState(STATE _state) { _bState = _state; }
	DIRECTION getDir() { return _bDir; }


	float getMaxHp() { return maxHp; }
	void setMaxHp(float _hp) { maxHp = _hp; }

	float getCurHp() { return currentHp; }
	void setCurHp(float _hp) { currentHp = _hp; }

	float getDamsX() { return damsX; }
	void setDamsX(float _damsX) { damsX = _damsX; }

	float getDamsY() { return damsY; }
	void setDamsY(float _damsY) { damsY = _damsY; }

	int getIndex() { return index; }
	void setIndex(int _index) { index = _index; }

	tagPos getPos() { return pos; }
	void setX(float _x) { pos.x = _x; }
	void setY(float _y) { pos.y = _y; }

	void setPlayerLink(yerinaT* player) { _player = player; }

	bool getIsStartBattle() { return isStartBattle; }
	void setIsStartBattle(bool _isStartBattle) { isStartBattle = _isStartBattle; }

	bool getIsReady() { return isReady; }
	void setIsReady(bool _isReady) { isReady = _isReady; }

	bool* getFinalSkill() { return isAttact; }

	bool getIsAttacted() { return _isAttacted; }
	void setIsAttacted(bool isAttacted) { _isAttacted = isAttacted; }

	bool getDontMove() { return _dontMove; }
	void setDontMove(bool dontMove) { _dontMove = dontMove; }

	bool getIsDead() { return isDead; }
	void setIsDead(bool _isDead) { isDead = _isDead; }

	int getInvincibleStateCount() { return invincibleStateCount; }
	void setInvincibleStateCount(int _invincibleStateCount) { invincibleStateCount = _invincibleStateCount; }

	int getMaxPhase() { return maxPhase; }
	int getCurPhase() { return currentPhase; }


	RBboss() {}
	~RBboss() {}
};




class ribbonBoss : public RBboss
{
private:

	image* _image[13];
	gdipImage* _chargingImg[RIBBONSKILLEND];
	ribbonBlueBullet* _blueBullet;
	ribbonBlueRain* _blueRain;
	ribbonYellowBlue* _sunFlower;
	ribbonSpiderWeb* _spiderWeb;


	//�Ѿ��׽�Ʈ
	int bulletIndex;
	int chargeIndex;
	int gauge;
	int chargeCount;

	//
	int stayCount;

public:

	void init();
	void release();
	void update();

	void animation();
	void move();
	void attactPattern();
	void fire();
	void attact(int _curPhase);

	void stay();
	void bodyRush();
	void bbyororong();
	void blueRain();
	void sunBeam();
	void flowerBeam();
	void spiderWeb();


	image* getImage(STATE _state) { return _image[_state]; }
	gdipImage* getChargingIMG(int i) { return _chargingImg[i]; }
	ribbonBlueBullet* getRibbonBlueBullet() { return _blueBullet; }
	ribbonBlueRain* getRibbonBlueRain() { return _blueRain; }
	ribbonYellowBlue* getSunFlowerBullet() { return _sunFlower; }
	ribbonSpiderWeb* getSpiderWebBullet() { return _spiderWeb; }


	int getBulletIndex() { return bulletIndex; }
	int getChargeIndex() { return chargeIndex; }
	void setBulletIndex(int _index) { bulletIndex = _index; }
	bool* getIsCharging() { return isCharging; }


	ribbonBoss() {}
	~ribbonBoss() {}

};

class finalBoss : public RBboss
{
private:

	image* _image[13];
	gdipImage* _chargingImg[FINALBOSSSKILLEND];
	guided_bullet* _guidedBullet;
	tornado_bullet* _tornadoBullet;
	snake_bullet* _snakeBullet;
	polygon_bullet* _polygonBullet;
	octopus_bullet* _octopusBullet;
	ball_bullet* _ballBullet;

	yerinaT* _player;

	//�Ѿ��׽�Ʈ
	int bulletIndex;
	int chargeIndex;
	int gauge;


	//
	int stayCount;

public:

	void init();
	void release();
	void update();

	void animation();
	void move();
	void attactPattern();
	void fire();
	void attact(int _curPhase);

	void stay();
	void guidedMissile();
	void tornado();
	void snake();
	void polygon();
	void octopus();
	void ball();


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�ٲܰ�
	image* getImage(STATE _state) { return _image[_state]; }
	gdipImage* getChargingIMG(int i) { return _chargingImg[i]; }
	guided_bullet* getFinalGuidedBullet() { return _guidedBullet; }
	tornado_bullet* getFinalTornadoBullet() { return _tornadoBullet; }
	snake_bullet* getFinalSnakeBullet() { return _snakeBullet; }
	polygon_bullet* getFinalPolygonBullet() { return _polygonBullet; }
	octopus_bullet* getFinalOctopusBullet() { return _octopusBullet; }
	ball_bullet* getFinalBallBullet() { return _ballBullet; }


	//ribbonBlueBullet* getRibbonBlueBullet() { return _blueBullet; }
	//ribbonBlueRain* getRibbonBlueRain() { return _blueRain; }
	//ribbonYellowBlue* getSunFlowerBullet() { return _sunFlower; }
	//ribbonSpiderWeb* getSpiderWebBullet() { return _spiderWeb; }


	int getBulletIndex() { return bulletIndex; }
	int getChargeIndex() { return chargeIndex; }
	void setBulletIndex(int _index) { bulletIndex = _index; }
	bool* getIsCharging() { return isCharging; }

	void setPlayerLink(yerinaT* player) { _player = player; }


	finalBoss() {}
	~finalBoss() {}

};