#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�
	
	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 �����Ѵ�
	//�׸��� ������ ������ ���ΰ��� ������ �ϸ� �ȴ�

	/*���߰�*/
	//SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
	//SCENEMANAGER->addScene("�׽�Ʈ��", new sceneTest);
	//SCENEMANAGER->addScene("ini", new iniTestScene);
	//SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	//SCENEMANAGER->addScene("����", new soundTestScene);
	//SCENEMANAGER->addScene("�ִϸ��̼�", new aniTestScene);
	//SCENEMANAGER->addScene("����Ʈ", new effectTestScene);
	//SCENEMANAGER->addScene("������Ʈ", new rotateTestScene);
	//SCENEMANAGER->addScene("��ũ����", new tankGameScene);
	//SCENEMANAGER->addScene("����", new maptoolScene);

	//��񸮺�
	SCENEMANAGER->addScene("�ε���", new loadingScene1);
	SCENEMANAGER->addScene("���۾�", new startScene1);
	SCENEMANAGER->addScene("���θ޴�", new mainMenuScene);
	SCENEMANAGER->addScene("��漱��", new bgChoiceScene1);
	SCENEMANAGER->addScene("������", new maptoolScene1);
	SCENEMANAGER->addScene("�׽�Ʈ��������", new stage1_MAPt);
	//SCENEMANAGER->addScene("������", new yerinaT);
	SCENEMANAGER->addScene("Ÿ��", new town_SceneT);
	SCENEMANAGER->addScene("��������1-1", new stage1_SceneT);
	SCENEMANAGER->addScene("��������1-2", new stage1_1_SceneT);
	SCENEMANAGER->addScene("��������1-3", new stage1_2_SceneT);
	SCENEMANAGER->addScene("��������1-4", new stage1_3_SceneT);
	SCENEMANAGER->addScene("��������1-����", new stage1_Boss_Scene);
	SCENEMANAGER->addScene("��������1-Ŭ����", new stage1_clear_Scene);
	SCENEMANAGER->addScene("��������2-1", new stage2_1_SceneT);
	SCENEMANAGER->addScene("�����������̳κ���", new stage_FinalBoss_Scene);
	SCENEMANAGER->addScene("���̳�Ŭ����", new stage2_clear_Scene);



	/*����� ����*/
	SCENEMANAGER->loadScene("�ε���");

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void mainGame::update(void)
{
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ
	SOUNDMANAGER->update();

	//����Ʈ�Ŵ��� ������Ʈ
	EFFECTMANAGER->update();




	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene("�ε���");
		SOUNDMANAGER->stop("��ŸƮ�����");// , SAVEDATA->getBgmSound());

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene("��������1-1");
	}
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//����Ʈ�Ŵ��� ����
	EFFECTMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());



//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}
