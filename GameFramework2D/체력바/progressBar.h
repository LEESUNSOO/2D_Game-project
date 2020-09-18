#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (프로그래스바 = 체력바)
//=============================================================

class progressBar : public gameNode
{
private:

	float _width;				//체력바길이
	RECT loadingRabbit;
	int _index, _count;
	image* loadRabbit_1;
	image* loadRabbit_2;


public:
	//바 초기화(앞이미지키, 백이미지키, x, y, 가로길이, 세로길이)
//	HRESULT init(const char* frontImageKey, const char* backImageKey, int x, int y, int width, int height);
	HRESULT init();

	void release(void);
	void update(void);
	void render(void);
	void rabbitSpin();

	//바 게이지 세팅하기
	void setGauge(float currentHp, float maxHp);

	progressBar() {}
	~progressBar() {}
};

