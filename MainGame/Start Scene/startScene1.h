#pragma once
#include "gameNode.h"

struct startRc
{
	float x;
	float y;
	float speed;
	float angle;
	RECT rc;
	image* _image;
	gdipImage* _gdiImage;

};
class startScene1 : public gameNode
{
private:

	startRc _bg;
	startRc _title;
	startRc _startButton;
	startRc _reference;

	int _index, _count, alpha;
	int _sceneChange;
	bool _isZDown;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void bgMove();
	void titleMove();
	void animation();
	void sceneChange();



	startScene1() {}
	~startScene1() {}
};

