#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹�)
//=============================================================

class progressBar : public gameNode
{
private:

	float _width;				//ü�¹ٱ���
	RECT loadingRabbit;
	int _index, _count;
	image* loadRabbit_1;
	image* loadRabbit_2;


public:
	//�� �ʱ�ȭ(���̹���Ű, ���̹���Ű, x, y, ���α���, ���α���)
//	HRESULT init(const char* frontImageKey, const char* backImageKey, int x, int y, int width, int height);
	HRESULT init();

	void release(void);
	void update(void);
	void render(void);
	void rabbitSpin();

	//�� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	progressBar() {}
	~progressBar() {}
};

