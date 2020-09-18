#include "stdafx.h"
#include "stage2_clear_Scene.h"


HRESULT stage2_clear_Scene::init(void)
{

	IMAGEMANAGER->addImage("��������2Ŭ�����", "resource/mapBG/��������2Ŭ�����.bmp", 1280, 720, true, MAGENTA);
	count = 0;
	alpha = 50;



	SOUNDMANAGER->play("��������Ŭ��������", SAVEDATA->getBgmSound());

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
			SCENEMANAGER->loadScene("Ÿ��");
			SOUNDMANAGER->stop("��������Ŭ��������");

		}
	}
}

void stage2_clear_Scene::render(void)
{
	IMAGEMANAGER->alphaRender("��������2Ŭ�����", getMemDC(), alpha);
}
