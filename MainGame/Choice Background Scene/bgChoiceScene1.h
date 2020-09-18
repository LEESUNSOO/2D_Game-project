#pragma once
#include "gameNode.h"

struct BG
{
	float _x, _y;
	RECT _rc;
	int _index;
	int _alpha;
	image* _image;
	bool _isActived;

};

#define MAPKIND 20
class bgChoiceScene1 : public gameNode
{
private:

	BG _bgSelect[MAPKIND];
	BG _bg;
	BG _bgFairy;

	int _count, _index;
	int loofSpeed;
	int selectNum;
	bool isSelected;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void bgMove();


	bgChoiceScene1(){}
	~bgChoiceScene1(){}
};

