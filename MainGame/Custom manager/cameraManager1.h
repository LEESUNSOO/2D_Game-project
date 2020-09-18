#pragma once
#include "singletonBase.h"

struct CAM
{
	float _posX, _posY;
	float _oldPosX, _oldPosY;
	float _sizeX, _sizeY;
	float _intensity;
	float _time;
	float _scale;
	bool _isVibrated;
	bool _isZoomed;
	RECT rc;
};
class cameraManager1 : public singletonBase<cameraManager1>
{
private:
	

	typedef vector<CAM> vCam;
	typedef vector<CAM>::iterator viCam;

	vCam _vCam;
	typedef map<string, vCam> mCam;
	typedef map<string, vCam>::iterator miCam;

	mCam _camList;

public:

	HRESULT init(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY);
	HRESULT initVibrate(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY, float intensity = 1.f, float time = 10.f);
	HRESULT initZoom(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY, float scale = 0.5f, float time = 5.f);

	void release(void);
	//void update(void);
	//void render(void);

	//경우에 맞는 카메라(렉트)를 형성해준다 생각하기
	void bgCameraUpdate(string cameraName,float posX, float posY, float mapSizeX, float mapSizeY);
	void vibrateCameraUpdate(string cameraName, float posX, float posY, float intensity = 1.f, float time = 10.f); // 상황에 따라 수정하고 싶을때 사용하라고 인자 추가
	void zoomCameraUpdate(string cameraName, float posX, float posY, float mapSizeX, float scale = 0.5f, float time = 5.f); // 상황에 따라 수정하고 싶을때 사용하라고 인자 추가
	
	//
	void focusOn(float posX, float posY);

	//함수가 발동될 때 마다 렉트에 움직임을 줌
	void vibrateSwitch(bool _isVibrated);
	void zoomSwitch(bool _isZoomed);

	//카메라 정보주기
	vector<CAM> getVCam(string cameraName)
	{
		//1과 2의 차이가 있나?
		//1)
		//miCam _miCam;
		//
		//for (_miCam = _camList.begin(); _miCam != _camList.end(); ++_miCam)
		//{
		//	if (!(_miCam->first == cameraName)) continue;
		//
		//	//이펙트키와 일치하면 이펙트 실행
		//	return _miCam->second;		
		//}

		//2)
		//해당키 검색
		miCam key = _camList.find(cameraName);
		
		//검색한 키를 찾았다면 백터 리턴
		if (key != _camList.end())
		{
			return key->second;
		}
		
		////검색한 키로 이미지를 못찾았다면 NULL;
		//return; 
	}



	cameraManager1(){}
	~cameraManager1(){}
};

