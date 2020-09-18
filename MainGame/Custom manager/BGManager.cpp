#include "stdafx.h"
#include "BGManager.h"

//
//void BGManager::addBG(string _key, float _speed)
//{
//	loopBg.insert(make_pair(_key, _speed));
//}
//
//void BGManager::loopRenderW(string _key, HDC _hdc)
//{
//	iloopBg = loopBg.begin();
//
//	for (iloopBg; iloopBg != loopBg.end(); iloopBg++)
//	{
//		if (iloopBg->first != _key) continue;
//
//		IMAGEMANAGER->loopRender(_key, _hdc, &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), iloopBg->second, 0);
//
//
//	}
//}
//
//void BGManager::loopRenderH(string _key, HDC _hdc)
//{
//	iloopBg = loopBg.begin();
//
//	for (iloopBg; iloopBg != loopBg.end(); iloopBg++)
//	{
//		if (iloopBg->first != _key) continue;
//
//		IMAGEMANAGER->loopRender(_key, _hdc, &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), 0, iloopBg->second);
//
//	}
//}
//
//void BGManager::release(void)
//{
//}