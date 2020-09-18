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
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene1::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경

	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("시작씬");
	}

}

void loadingScene1::render(void)
{
	_loading->render();
}


void loadingScene1::loadingImage()
{
	//PNG안되네;

	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞동산뒷잔디", "resource/mapBG/풀맵앞동산뒷잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞잔디", "resource/mapBG/풀맵앞잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷천장풀", "resource/mapBG/풀맵뒷천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵중간천장풀", "resource/mapBG/풀맵중간천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞천장풀", "resource/mapBG/풀맵앞천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞동산뒷잔디", "resource/mapBG/풀맵앞동산뒷잔디.bmp", 1280, 720, true, MAGENTA);	
	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞동산뒷잔디", "resource/mapBG/풀맵앞동산뒷잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞잔디", "resource/mapBG/풀맵앞잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷천장풀", "resource/mapBG/풀맵뒷천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵중간천장풀", "resource/mapBG/풀맵중간천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞천장풀", "resource/mapBG/풀맵앞천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞동산뒷잔디", "resource/mapBG/풀맵앞동산뒷잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞동산뒷잔디", "resource/mapBG/풀맵앞동산뒷잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞잔디", "resource/mapBG/풀맵앞잔디.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷천장풀", "resource/mapBG/풀맵뒷천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵중간천장풀", "resource/mapBG/풀맵중간천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞천장풀", "resource/mapBG/풀맵앞천장풀.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵하늘", "resource/mapBG/풀맵하늘.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵뒷산", "resource/mapBG/풀맵뒷산.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("풀맵앞산뒷동산", "resource/mapBG/풀맵앞산뒷동산.bmp", 1280, 720, true, MAGENTA);

	
	
}

void loadingScene1::loadingSound()
{
	_loading->loadSound("스타트버튼", "resource/sound/eff/스타트버튼.wav");
	_loading->loadSound("스타트씬브금", "resource/sound/bgm/스타트씬브금.mp3", true, true);

	_loading->loadSound("메인메뉴선택", "resource/sound/eff/메인메뉴선택.wav");
	_loading->loadSound("메인메뉴최종선택", "resource/sound/eff/메인메뉴최종선택.wav");
	_loading->loadSound("메인메뉴씬브금", "resource/sound/bgm/메인메뉴씬브금.mp3", true, true);

	_loading->loadSound("타운씬브금", "resource/sound/bgm/타운씬브금.mp3", true, true);

	_loading->loadSound("스테이지1씬브금", "resource/sound/bgm/스테이지1씬브금.mp3", true, true);

	_loading->loadSound("리본보스입장브금", "resource/sound/bgm/리본보스입장브금.mp3", true, true);
	_loading->loadSound("리본보스전투브금", "resource/sound/bgm/리본보스전투브금.mp3", true, true);

	_loading->loadSound("리본보스클리어씬브금", "resource/sound/bgm/리본보스클리어씬브금.mp3", true, true);

	_loading->loadSound("스테이지2씬브금", "resource/sound/bgm/스테이지2씬브금.mp3", true, true);

	_loading->loadSound("최종보스입장브금", "resource/sound/bgm/최종보스입장브금.mp3", true, true);
	_loading->loadSound("최종보스전투브금", "resource/sound/bgm/최종보스전투브금.mp3", true, true);
	_loading->loadSound("최종보스클리어씬브금", "resource/sound/bgm/최종보스클리어씬브금.mp3", true, true);

	//////////////////////////////////////////////////


	_loading->loadSound("점프", "resource/sound/eff/점프.wav");
	_loading->loadSound("슬라이드", "resource/sound/eff/슬라이드.wav");
	_loading->loadSound("해머", "resource/sound/eff/해머.wav");
	_loading->loadSound("해머5", "resource/sound/eff/해머5.wav");
	_loading->loadSound("업해머", "resource/sound/eff/업해머.wav");
	_loading->loadSound("다운해머", "resource/sound/eff/다운해머.wav");

	_loading->loadSound("데미지", "resource/sound/eff/데미지.wav");
	_loading->loadSound("해머타격", "resource/sound/eff/해머타격.wav");
	_loading->loadSound("골드", "resource/sound/eff/골드.wav");
	_loading->loadSound("대화넘기기", "resource/sound/eff/대화넘기기.wav");
	_loading->loadSound("체력회복", "resource/sound/eff/체력회복.wav");

	_loading->loadSound("리본클리어", "resource/sound/eff/리본클리어.wav");
	_loading->loadSound("리본차징", "resource/sound/eff/리본차징.wav");
	_loading->loadSound("리본차징2", "resource/sound/eff/리본차징2.wav");
	_loading->loadSound("리본블루총알파이어", "resource/sound/eff/리본블루총알파이어.wav");
	_loading->loadSound("리본블루레인파이어", "resource/sound/eff/리본블루레인파이어.wav");
	_loading->loadSound("리본선총알파이어", "resource/sound/eff/리본선총알파이어.wav");
	_loading->loadSound("리본플라워총알파이어", "resource/sound/eff/리본플라워총알파이어.wav");
	_loading->loadSound("리본거미줄파이어", "resource/sound/eff/리본거미줄파이어.wav");

	_loading->loadSound("최종별파이어", "resource/sound/eff/최종별파이어.wav");
	_loading->loadSound("최종토네이도파이어", "resource/sound/eff/최종토네이도파이어.wav");
	_loading->loadSound("최종스네이크파이어", "resource/sound/eff/최종스네이크파이어.wav");
	_loading->loadSound("최종스네이크파이어2", "resource/sound/eff/최종스네이크파이어2.wav");
	_loading->loadSound("최종다각형파이어", "resource/sound/eff/최종다각형파이어.wav");
	_loading->loadSound("최종문어파이어", "resource/sound/eff/최종문어파이어.wav");
	_loading->loadSound("최종문어파이어2", "resource/sound/eff/최종문어파이어2.wav");
	_loading->loadSound("최종볼파이어", "resource/sound/eff/최종볼파이어.wav");


	




}


