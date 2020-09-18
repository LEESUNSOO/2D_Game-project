#include "stdafx.h"
#include "loadingScene1.h"


HRESULT loadingScene1::init(void)
{

	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene1::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene1::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ������

	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("���۾�");
	}

}

void loadingScene1::render(void)
{
	_loading->render();
}


void loadingScene1::loadingImage()
{
	//PNG�ȵǳ�;

	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ��ܵ�", "resource/mapBG/Ǯ�ʾ��ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ�õ��Ǯ", "resource/mapBG/Ǯ�ʵ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���߰�õ��Ǯ", "resource/mapBG/Ǯ���߰�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ�õ��Ǯ", "resource/mapBG/Ǯ�ʾ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);	
	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ��ܵ�", "resource/mapBG/Ǯ�ʾ��ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ�õ��Ǯ", "resource/mapBG/Ǯ�ʵ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���߰�õ��Ǯ", "resource/mapBG/Ǯ���߰�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ�õ��Ǯ", "resource/mapBG/Ǯ�ʾ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾյ�����ܵ�", "resource/mapBG/Ǯ�ʾյ�����ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ��ܵ�", "resource/mapBG/Ǯ�ʾ��ܵ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ�õ��Ǯ", "resource/mapBG/Ǯ�ʵ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���߰�õ��Ǯ", "resource/mapBG/Ǯ���߰�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾ�õ��Ǯ", "resource/mapBG/Ǯ�ʾ�õ��Ǯ.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ���ϴ�", "resource/mapBG/Ǯ���ϴ�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʵ޻�", "resource/mapBG/Ǯ�ʵ޻�.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("Ǯ�ʾջ�޵���", "resource/mapBG/Ǯ�ʾջ�޵���.bmp", 1280, 720, true, MAGENTA);

	
	
}

void loadingScene1::loadingSound()
{
	_loading->loadSound("��ŸƮ��ư", "resource/sound/eff/��ŸƮ��ư.wav");
	_loading->loadSound("��ŸƮ�����", "resource/sound/bgm/��ŸƮ�����.mp3", true, true);

	_loading->loadSound("���θ޴�����", "resource/sound/eff/���θ޴�����.wav");
	_loading->loadSound("���θ޴���������", "resource/sound/eff/���θ޴���������.wav");
	_loading->loadSound("���θ޴������", "resource/sound/bgm/���θ޴������.mp3", true, true);

	_loading->loadSound("Ÿ������", "resource/sound/bgm/Ÿ������.mp3", true, true);

	_loading->loadSound("��������1�����", "resource/sound/bgm/��������1�����.mp3", true, true);

	_loading->loadSound("��������������", "resource/sound/bgm/��������������.mp3", true, true);
	_loading->loadSound("���������������", "resource/sound/bgm/���������������.mp3", true, true);

	_loading->loadSound("��������Ŭ��������", "resource/sound/bgm/��������Ŭ��������.mp3", true, true);

	_loading->loadSound("��������2�����", "resource/sound/bgm/��������2�����.mp3", true, true);

	_loading->loadSound("��������������", "resource/sound/bgm/��������������.mp3", true, true);
	_loading->loadSound("���������������", "resource/sound/bgm/���������������.mp3", true, true);
	_loading->loadSound("��������Ŭ��������", "resource/sound/bgm/��������Ŭ��������.mp3", true, true);

	//////////////////////////////////////////////////


	_loading->loadSound("����", "resource/sound/eff/����.wav");
	_loading->loadSound("�����̵�", "resource/sound/eff/�����̵�.wav");
	_loading->loadSound("�ظ�", "resource/sound/eff/�ظ�.wav");
	_loading->loadSound("�ظ�5", "resource/sound/eff/�ظ�5.wav");
	_loading->loadSound("���ظ�", "resource/sound/eff/���ظ�.wav");
	_loading->loadSound("�ٿ��ظ�", "resource/sound/eff/�ٿ��ظ�.wav");

	_loading->loadSound("������", "resource/sound/eff/������.wav");
	_loading->loadSound("�ظ�Ÿ��", "resource/sound/eff/�ظ�Ÿ��.wav");
	_loading->loadSound("���", "resource/sound/eff/���.wav");
	_loading->loadSound("��ȭ�ѱ��", "resource/sound/eff/��ȭ�ѱ��.wav");
	_loading->loadSound("ü��ȸ��", "resource/sound/eff/ü��ȸ��.wav");

	_loading->loadSound("����Ŭ����", "resource/sound/eff/����Ŭ����.wav");
	_loading->loadSound("������¡", "resource/sound/eff/������¡.wav");
	_loading->loadSound("������¡2", "resource/sound/eff/������¡2.wav");
	_loading->loadSound("��������Ѿ����̾�", "resource/sound/eff/��������Ѿ����̾�.wav");
	_loading->loadSound("������緹�����̾�", "resource/sound/eff/������緹�����̾�.wav");
	_loading->loadSound("�������Ѿ����̾�", "resource/sound/eff/�������Ѿ����̾�.wav");
	_loading->loadSound("�����ö���Ѿ����̾�", "resource/sound/eff/�����ö���Ѿ����̾�.wav");
	_loading->loadSound("�����Ź������̾�", "resource/sound/eff/�����Ź������̾�.wav");

	_loading->loadSound("���������̾�", "resource/sound/eff/���������̾�.wav");
	_loading->loadSound("��������̵����̾�", "resource/sound/eff/��������̵����̾�.wav");
	_loading->loadSound("����������ũ���̾�", "resource/sound/eff/����������ũ���̾�.wav");
	_loading->loadSound("����������ũ���̾�2", "resource/sound/eff/����������ũ���̾�2.wav");
	_loading->loadSound("�����ٰ������̾�", "resource/sound/eff/�����ٰ������̾�.wav");
	_loading->loadSound("�����������̾�", "resource/sound/eff/�����������̾�.wav");
	_loading->loadSound("�����������̾�2", "resource/sound/eff/�����������̾�2.wav");
	_loading->loadSound("���������̾�", "resource/sound/eff/���������̾�.wav");


	




}


