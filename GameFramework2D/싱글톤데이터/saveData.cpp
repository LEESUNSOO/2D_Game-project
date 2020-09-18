#include "stdafx.h"
#include "saveData.h"


HRESULT saveData::init()
{
	for (int i = 0; i < 12; i++)
	{
		_currentStage[i] = false;

	}
	return S_OK;
}

void saveData::release()
{
}
