#pragma once
#include "gameNode.h"
#include "rabiribiBullet.h"

#define RIBBONAFTERIMAGES 10


struct RIBBONINF
{
	float x, y;
	float oldX, oldY;
	float speed;
	float jumpSpeed;
	float angle;
	float gravity;

	float maxMp;
	float curMp;
	int charge;
	int skillPower;

	float maxBooster;
	float curBooster;

	RECT rc;
	tagRc afterImageRc[RIBBONAFTERIMAGES];
	RIBBONSTATE state;
	DIRECTION dir;
	image* image[RIBBONEND];

	bool isFire;
	bool isCharging;

};

class ribbonT : public gameNode
{
private:

	ribbonBlueBullet* _bbyororong;

	RIBBONINF _ribbon;
	int _index, _count;
	int _ribbonBackIndex[RIBBONAFTERIMAGES];
	int _bulletIndex;
	int _chargingIndex;

public:


	HRESULT init();
	void release();
	void update(float yerinaX, float yerinaY, float yerinaSpeed, DIRECTION _dir);
	void render();

	void move(float yerinaX, float yerinaY, float yerinaSpeed, DIRECTION _dir);
	void animation(DIRECTION _dir);
	void makingAfterImageRc();
	void fire(float x, float y, DIRECTION _dir);
	void manaCharge();



	float getX() { return _ribbon.x; }
	void setX(float _x) { _ribbon.x = _x; }

	float getY() { return _ribbon.y; }
	void setY(float _y) { _ribbon.y = _y; }

	float getMaxMp() { return _ribbon.maxMp; }
	void setMaxMp(float maxMp) { _ribbon.maxMp = maxMp; }

	float getCurMp() { return _ribbon.curMp; }
	void setCurMp(float curMp) { _ribbon.curMp = curMp; }

	int getCharge() { return _ribbon.charge; }
	void setCharge(int charge) { _ribbon.charge = charge; }

	int getSkillPower() { return _ribbon.skillPower; }
	void setSkillPower(int skillPower) { _ribbon.skillPower = skillPower; }

	float getSpeed() { return _ribbon.speed; }
	void setSpeed(float _speed) { _ribbon.speed = _speed; }

	bool getIscharging() { return _ribbon.isCharging; }
	void setIscharging(bool _ischarging) { _ribbon.isCharging = _ischarging; }

	void setChargingIndex(int index) { _chargingIndex = index; }

	ribbonBlueBullet* getBullet() { return _bbyororong; }

	ribbonT(){}
	~ribbonT(){}
};

