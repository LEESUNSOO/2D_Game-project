#pragma once
#include "gameNode.h"

struct BAR
{

	float x, y;
	float speed;
	RECT rc;
	image* _image[5];
	gdipImage* _pngImage[3];
	int _Index[3];
	bool _isActive;

};

class yerinaT;
class RBenemyManager;


class UIT : public gameNode
{
private:

	yerinaT* _player;
	RBenemyManager* _eMG;

	BAR _playerBar;
	BAR _playerHp;
	BAR _ribbonBar;
	BAR _BossBar;
	BAR _yerinaRibbon;
	BAR _goldInf;
	BAR _minimap;
	BAR _minimi;

	//½º¸ô¹Ù
	BAR _playerSmallHp;
	BAR _playerSmallEnergy;
	BAR _ribbonSmallMp;

	int count;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void playerHp();
	void minimiSite();
	void goldInformation();


	void setPlayerLink(yerinaT* player) { _player = player; }
	void setEnemyMGLink(RBenemyManager* eMG) { _eMG = eMG; }


	UIT(){}
	~UIT(){}
};

