#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init()
{

	loadRabbit_1 = IMAGEMANAGER->addFrameImage("·ÎµùÅä³¢1", "resource/loading/·ÎµùÅä³¢2.bmp", 444, 98, 6, 1);
	loadRabbit_2 = IMAGEMANAGER->addFrameImage("·ÎµùÅä³¢2", "resource/loading/·ÎµùÅä³¢5.bmp", 444, 98, 6, 1);
	_index = _count = 0;
	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_count++;
	loadingRabbit = RectMakeCenter(WINSIZEX - 100, WINSIZEY - 100, 74, 98);
	this->rabbitSpin();
}

void progressBar::render(void)
{
	loadRabbit_1->frameRender(getMemDC(), loadingRabbit.left, loadingRabbit.top, loadRabbit_1->getFrameX(), loadRabbit_1->getFrameY());
	loadRabbit_2->frameRender(getMemDC(), loadingRabbit.left, loadingRabbit.top, loadRabbit_1->getFrameX() * loadRabbit_1->getFrameWidth(), loadRabbit_1->getY() + loadRabbit_1->getFrameHeight(), loadRabbit_1->getFrameWidth(), _width, loadRabbit_1->getFrameX(), loadRabbit_1->getFrameY());
}

void progressBar::rabbitSpin()
{
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > loadRabbit_1->getMaxFrameX())
		{
			_index = 0;
		}

		loadRabbit_1->setFrameX(_index);

	}
	loadRabbit_1->setFrameY(0);
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * loadRabbit_2->getHeight();
}
