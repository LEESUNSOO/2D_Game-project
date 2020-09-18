#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "rabiribiBullet.h"
#include "stage_MAPt.h"
#include "ribbonT.h"

//class stage1_MAPt;

class RBenemyManager;
#define YERINASIZE 128
#define CHECKTILEINDEX 11
#define YERINAJUMPSPEED 12.f
#define AFTERIMAGES 10

struct rabiribiPlayer
{


	float x, y;
	float oldX, oldY;
	float speed;
	float jumpSpeed;
	float angle;
	float gravity;

	float maxHp;
	float curHp;

	float maxEnergy;
	float curEnergy;

	int gold;

	//Ŀ���
	int commandNum;
	int commandCount;
	bool isActiveCommand;
	bool isCommanding;
	bool isAttacting[HAMMER_END];
	int strikingPower[HAMMER_END];
	int strikingPower_upCount[HAMMER_END];
	int strikingPower_upRange[HAMMER_END];

	//�浹����
	bool _isClimb;
	bool _isFall;
	bool _isHeadCollide;
	bool _isLRCollide;

	//�Ʒ���ư
	bool _isPushDownKey;
	bool _isAttactDown;

	//�����̵�
	bool _isSlde;

	//����ư
	bool _isPushUpkey;
	bool _isAttactUp;

	//������
	bool _isSpringJump;

	//��������
	bool _isStartBattle;


	//�ǰݽ�
	bool _isAttacted;
	bool _dontMove;
	int invincibleStateCount;
	int invincibleAlpha;

	RECT rc;
	RECT LRColliRc;
	RECT tileCollRc;
	RECT bottomTileCheckRc;
	RECT topTileCheckRc;
	RECT pixelRc;
	RECT beAttRc;
	RECT realSizeRc;

	tagRc afterImageRc[AFTERIMAGES]; // �ܻ�Ʈ


	RECT attackRc[HAMMER_END];


	//�������������
	bool isClearStage1;


};


class yerinaT :public gameNode
{
private:

	keyManager* _keymg;


	//�Ҵ�
	ribbonT* _ribbon;

	//typedef map<int , rabiribiPlayer> _m;

	rabiribiPlayer _yerina;
	STATE _state;
	HAMMER _hammer;
	DIRECTION _direction;
	int _bodyIndex, _count;
	int _hammerIndex;
	float _chargeCount;

	int _collisionTileIndex[CHECKTILEINDEX];
	int _currentTileX, _currentTileY;

	image* _yerinaImg[16];
	image* _yerinaHammer[8];

	float cameraX, cameraY;

	bool isSpringActive;
	bool checkckckckkcckk;
	//�ʰ� ��ȣ����(���̺굥���͸� ����� �� ����! �ٷιٷ� �������� �޾� ������Ѿ��ϴϱ�!)
	stage1_MAPt* _stage1_map;

	//�Ѿ��Ҵ�(���)

	yerinaCarrot* _carrot;
	RBenemyManager* _eMG; // ��ȣ����

public:

	HRESULT init(void);
	void release(void);
	void update(stage_MAPt* _stageMap);
	void render(void);

	void keyInPut(stage_MAPt* _stageMap);
	void move();
	void makingBodyRc();
	void makingAfterImageRc();
	void makingAttactRc();
	void tileCollision(stage_MAPt* _stageMap);
	void enemyBodyCollision();
	void BossCollision();
	void animation();
	void commandAnimation();

	void springCollision(stage_MAPt* _stageMap);
	void debug();


	float getX() { return _yerina.x; }
	void setX(float _x) { _yerina.x = _x; }

	float getY() { return _yerina.y; }
	void setY(float _y) { _yerina.y = _y; }

	float getMaxHp() { return _yerina.maxHp; }
	void setMaxHp(float _hp) { _yerina.maxHp = _hp; }

	float getCurHp() { return _yerina.curHp; }
	void setCurHp(float _hp) { _yerina.curHp = _hp; }

	float getMaxEnergy() { return _yerina.maxEnergy; }
	void setMaxEnergy(float _energy) { _yerina.maxEnergy = _energy; }

	float getCurEnergy() { return _yerina.curEnergy; }
	void setCurEnergy(float _energy) { _yerina.curEnergy = _energy; }

	int getGold() { return _yerina.gold; }
	void setGold(float _gold) { _yerina.gold = _gold; }

	float getGravity() { return _yerina.gravity; }
	void setGravity(float _gravity) { _yerina.gravity = _gravity; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	bool getIsFall() { return _yerina._isFall; }
	void setIsFall(bool _isfall) { _yerina._isFall = _isfall; }

	bool getIsAttacted() { return _yerina._isAttacted; }
	void setIsAttacted(bool _isAttacted) { _yerina._isAttacted = _isAttacted; }

	bool getIsStartBattle() { return _yerina._isStartBattle; }
	void setIsStartBattle(bool _isStartBattle) { _yerina._isStartBattle = _isStartBattle; }

	bool getIsClearStage1() { return _yerina.isClearStage1; }
	void setIsClearStage1(bool isClearStage1) { _yerina.isClearStage1 = isClearStage1; }

	RECT getRc() { return _yerina.realSizeRc; }
	float getOldX() { return _yerina.oldX; }

	DIRECTION getDir() { return _direction; }
	void setDir(DIRECTION _dir) { _direction = _dir; }

	//�ظӷ�Ʈ
	RECT* getAttactRc() { return _yerina.attackRc; }
	HAMMER getHammer() { return _hammer; }

	int* getStrikingPower() { return _yerina.strikingPower; }
	void setStrikingPower(int i , int _strikingPower) { _yerina.strikingPower[i] = _strikingPower; }

	int* getStrikingPowerUpCount() { return _yerina.strikingPower_upCount; }
	void setStrikingPowerUpCount(int i, int _strikingPower) { _yerina.strikingPower_upCount[i] = _strikingPower; }

	int* getStrikingPowerUprange() { return _yerina.strikingPower_upRange; }
	void getStrikingPowerUprange(int i, int _strikingPower) { _yerina.strikingPower_upRange[i] = _strikingPower; }

	//����
	ribbonT* getRibbon() { return _ribbon; }

	//��ȣ������ �Ϸ��� set�Լ��� ��������
	void setStage1Map(stage1_MAPt* stage1_Map) { _stage1_map = stage1_Map; }

	void setEmgLink(RBenemyManager* _emg) { _eMG = _emg; }



	yerinaT() {}
	~yerinaT() {}
};

