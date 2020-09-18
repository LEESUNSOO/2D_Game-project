#pragma once
#include "singletonBase.h"

class yerinaT;
class RBenemyManager;


class saveData : public singletonBase <saveData>
{
private:

	yerinaT* _player;
	RBenemyManager* _eMG;


	int _hp = 100;
	int _selectNum; // 배경선택 -> 맵툴씬 넘어갈 때!

	int _mp = 100;

	float _playerX[12];
	float _playerY[12];
	float _playerGravity[12];
	STATE _playerState[12];

	bool _playerIsFall[12];
	bool _isWarp = false;
	bool _currentStage[12];

	bool _isClearStage1 = false;// 임시로 true@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	STAGE_NUMBER currentStage;
	STAGE_NUMBER previousStage;

	float vol_bgm = 0.6f;
	float vol_effSound = 0.4f;


public:
	HRESULT init();
	void release();


	yerinaT* getPlayer() { return _player; }
	void setPlayer(yerinaT* player) { _player = player; }

	RBenemyManager* getEnemyManager() { return _eMG; }
	void setEnemyManager(RBenemyManager* em) { _eMG = em; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	int getMp() { return _mp; }
	void setMp(int mp) { _mp = mp; }


	int getSelectNum() { return _selectNum; }
	void setSelectNum(int _num) { _selectNum = _num; }

	float* getX() { return _playerX; }
	void setX(int i, float x) { _playerX[i] = x; }

	float* getY() { return _playerY; }
	void setY(int i, float y) { _playerY[i] = y; }

	float* getGravity() { return _playerGravity; }
	void setGravity(int i, float y) { _playerGravity[i] = y; }

	STATE* getState() { return _playerState; }
	void setState(int i, STATE y) { _playerState[i] = y; }
	
	bool* getIsFall() { return _playerIsFall; }
	void setIsFall(int i , bool _isFall) { _playerIsFall[i] = _isFall; }

	bool getIsClearStage1() { return _isClearStage1; }
	void setIsClearStage1(bool isClearStage1) { _isClearStage1 = isClearStage1; }

	bool getIsWarp() { return _isWarp; }
	void setIsWarp(bool isWarp) { _isWarp = isWarp; }

	//bool* getCurrentStage() { return _currentStage; }
	//void setCurrentStage(int i, bool currentStage) { _currentStage[i] = currentStage; }

	STAGE_NUMBER getPreviousStage() { return previousStage; }
	void setPreviousStage(STAGE_NUMBER _previousStage) { previousStage = _previousStage; }

	STAGE_NUMBER getCurrentStage() { return currentStage; }
	void setCurrentStage(STAGE_NUMBER _currentStage) { currentStage = _currentStage; }


	//사운드

	float getBgmSound() { return vol_bgm; }
	void setBgmSound(float _vol) { vol_bgm = _vol;}

	float getEffSound() { return vol_effSound; }
	void setEffSound(float _vol) { vol_effSound = _vol; }


	saveData() {}
	~saveData() {}
};

