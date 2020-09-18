#include "stdafx.h"
#include "stage2_clear_Scene.h"


HRESULT stage2_clear_Scene::init(void)
{

	IMAGEMANAGER->addImage("스테이지2클리어맵", "resource/mapBG/스테이지2클리어맵.bmp", 1280, 720, true, MAGENTA);
	count = 0;
	alpha = 50;



	SOUNDMANAGER->play("최종보스클리어씬브금", SAVEDATA->getBgmSound());

	return S_OK;


}

void stage2_clear_Scene::release(void)
{
}

void stage2_clear_Scene::update(void)
{
	count++;

	if (count % 3 == 0)
	{
		alpha++;
		if (alpha > 250)
		{
			SCENEMANAGER->loadScene("타운");
			SOUNDMANAGER->stop("최종보스클리어씬브금");

		}
	}
}

void stage2_clear_Scene::render(void)
{
	IMAGEMANAGER->alphaRender("스테이지2클리어맵", getMemDC(), alpha);
}
