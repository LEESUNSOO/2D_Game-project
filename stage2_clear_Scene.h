#pragma once
#include "gameNode.h"

class stage2_clear_Scene : public gameNode
{
private:

	int alpha, count;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stage2_clear_Scene(){}
	~stage2_clear_Scene(){}
};

