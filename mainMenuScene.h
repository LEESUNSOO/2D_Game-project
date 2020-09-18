#pragma once
#include "gameNode.h"

struct bgimage
{
	int _alpha;
	bool _isActived;
	bool _isDownAlpha;
	image* _bgImage;
};
class mainMenuScene : public gameNode
{
private:

	int _count, _index;

	bgimage _bgImage[5];
	int _bgIndex;

	RECT title;

	RECT category[5];
	int categoryY[5];
	bool _isChoice[5];
	int choiceNum;
	float lineLength[5];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void bgChange();
	void choiceCategory();
	void textSource();
	void sceneChange();

	mainMenuScene(){}
	~mainMenuScene(){}
};

