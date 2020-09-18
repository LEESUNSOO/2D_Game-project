#pragma once
#include "gameNode.h"
class stage1_clear_Scene : public gameNode
{
private:

	int alpha, count;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stage1_clear_Scene(){}
	~stage1_clear_Scene(){}
};

