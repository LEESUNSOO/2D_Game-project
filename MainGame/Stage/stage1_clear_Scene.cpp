#include "stdafx.h"
#include "stage1_clear_Scene.h"



HRESULT stage1_clear_Scene::init(void)
{
	IMAGEMANAGER->addImage("��������1Ŭ�����", "resource/mapBG/��������1Ŭ�����.bmp", 1280, 720, true, MAGENTA);
	count = 0;
	alpha = 50;
	
	

	SOUNDMANAGER->play("��������Ŭ��������", SAVEDATA->getBgmSound());

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
			SCENEMANAGER->loadScene("Ÿ��");
			SOUNDMANAGER->stop("��������Ŭ��������");

		}
	}
}

void stage1_clear_Scene::render(void)
{
	IMAGEMANAGER->alphaRender("��������1Ŭ�����", getMemDC(), alpha);
}
