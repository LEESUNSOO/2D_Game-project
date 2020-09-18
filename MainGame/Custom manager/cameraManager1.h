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

	//��쿡 �´� ī�޶�(��Ʈ)�� �������ش� �����ϱ�
	void bgCameraUpdate(string cameraName,float posX, float posY, float mapSizeX, float mapSizeY);
	void vibrateCameraUpdate(string cameraName, float posX, float posY, float intensity = 1.f, float time = 10.f); // ��Ȳ�� ���� �����ϰ� ������ ����϶�� ���� �߰�
	void zoomCameraUpdate(string cameraName, float posX, float posY, float mapSizeX, float scale = 0.5f, float time = 5.f); // ��Ȳ�� ���� �����ϰ� ������ ����϶�� ���� �߰�
	
	//
	void focusOn(float posX, float posY);

	//�Լ��� �ߵ��� �� ���� ��Ʈ�� �������� ��
	void vibrateSwitch(bool _isVibrated);
	void zoomSwitch(bool _isZoomed);

	//ī�޶� �����ֱ�
	vector<CAM> getVCam(string cameraName)
	{
		//1�� 2�� ���̰� �ֳ�?
		//1)
		//miCam _miCam;
		//
		//for (_miCam = _camList.begin(); _miCam != _camList.end(); ++_miCam)
		//{
		//	if (!(_miCam->first == cameraName)) continue;
		//
		//	//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		//	return _miCam->second;		
		//}

		//2)
		//�ش�Ű �˻�
		miCam key = _camList.find(cameraName);
		
		//�˻��� Ű�� ã�Ҵٸ� ���� ����
		if (key != _camList.end())
		{
			return key->second;
		}
		
		////�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL;
		//return; 
	}



	cameraManager1(){}
	~cameraManager1(){}
};

