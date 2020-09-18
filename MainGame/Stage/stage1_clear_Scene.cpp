#include "stdafx.h"
#include "stage1_clear_Scene.h"



HRESULT stage1_clear_Scene::init(void)
{
	IMAGEMANAGER->addImage("스테이지1클리어맵", "resource/mapBG/스테이지1클리어맵.bmp", 1280, 720, true, MAGENTA);
	count = 0;
	alpha = 50;
	
	

	SOUNDMANAGER->play("리본보스클리어씬브금", SAVEDATA->getBgmSound());

	return S_OK;


}

void stage1_clear_Scene::release(void)
{
}

void stage1_clear_Scene::update(void)
{
	count++;

	if (count % 3 == 0)
	{
		alpha++;
		if (alpha > 250)
		{
			SCENEMANAGER->loadScene("타운");
			SOUNDMANAGER->stop("리본보스클리어씬브금");

		}
	}
}

void stage1_clear_Scene::render(void)
{
	IMAGEMANAGER->alphaRender("스테이지1클리어맵", getMemDC(), alpha);
}
