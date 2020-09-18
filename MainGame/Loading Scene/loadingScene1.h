#pragma once
#include "gameNode.h"
#include "loading.h"

//#include "image.h"

class loadingScene1 : public gameNode
{
private:

	loading * _loading;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadingImage();
	void loadingSound();


	loadingScene1() {}
	~loadingScene1() {}
};

