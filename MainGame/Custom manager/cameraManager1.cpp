#include "stdafx.h"
#include "cameraManager1.h"

HRESULT cameraManager1::init(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY)
{
	CAM _cam;

	_cam._posX = posX;
	_cam._posY = posY;
	_cam._oldPosX = oldposX;
	_cam._oldPosY = oldposY;
	_cam._sizeX = SizeX;
	_cam._sizeY = SizeY;
	_cam.rc = RectMakeCenter(_cam._posX, _cam._posY, _cam._sizeX, _cam._sizeY);
	_cam._intensity = 0;
	_cam._scale = 0;
	_cam._time = 0;
	_cam._isVibrated = false;
	_cam._isZoomed = false;

	_vCam.push_back(_cam);
	_camList.insert(make_pair(cameraName, _vCam));


	return S_OK;
}

HRESULT cameraManager1::initVibrate(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY, float intensity, float time)
{
	CAM _cam;

	_cam._posX = posX;
	_cam._posY = posY;
	_cam._oldPosX = oldposX;
	_cam._oldPosY = oldposY;
	_cam._sizeX = SizeX;
	_cam._sizeY = SizeY;
	_cam.rc = RectMakeCenter(_cam._posX, _cam._posY, _cam._sizeX, _cam._sizeY);
	_cam._intensity = intensity;
	_cam._isVibrated = true;

	_cam._time = time;
	_cam._scale = 0;
	_cam._isZoomed = false;

	_vCam.push_back(_cam);

	_camList.insert(make_pair(cameraName, _vCam));


	return S_OK;

}

HRESULT cameraManager1::initZoom(string cameraName, float posX, float posY, float oldposX, float oldposY, float SizeX, float SizeY, float scale, float time)
{
	CAM _cam;

	_cam._posX = posX;
	_cam._posY = posY;
	_cam._oldPosX = oldposX;
	_cam._oldPosY = oldposY;
	_cam._sizeX = SizeX;
	_cam._sizeY = SizeY;
	_cam.rc = RectMakeCenter(_cam._posX, _cam._posY, _cam._sizeX, _cam._sizeY);
	_cam._intensity = 0;
	_cam._isVibrated = false;

	_cam._time = time;
	_cam._scale = scale;
	_cam._isZoomed = true;

	_vCam.push_back(_cam);

	_camList.insert(make_pair(cameraName, _vCam));


	return S_OK;
}

void cameraManager1::release(void)
{
}

void cameraManager1::bgCameraUpdate(string cameraName, float posX, float posY, float mapSizeX, float mapSizeY)
{

	if (posX - WINSIZEX / 2 < 0)
	{
		posX = WINSIZEX / 2;
	}
	if (posX + WINSIZEX / 2 > mapSizeX-1)
	{
		posX = mapSizeX - WINSIZEX / 2 - 1;
	}
	if (posY - WINSIZEY / 2 < 0)
	{
		posY = WINSIZEY / 2;
	}
	if (posY + WINSIZEY / 2 > mapSizeY )
	{
		posY = mapSizeY - WINSIZEY / 2 ;
	}

	miCam _miCam;

	for (_miCam = _camList.begin(); _miCam != _camList.end(); ++_miCam)
	{
		if (!(_miCam->first == cameraName)) continue;

		//이펙트키와 일치하면 이펙트 실행
		for (int i = 0; i < _miCam->second.size(); i++)
		{
			//if (_miCam->second[i]) continue;

			_miCam->second[i].rc = RectMakeCenter(_miCam->second[i]._posX + (posX - _miCam->second[i]._oldPosX), _miCam->second[i]._posY + (posY - _miCam->second[i]._oldPosY), _miCam->second[i]._sizeX, _miCam->second[i]._sizeY );

		}

	}

	return;
}

void cameraManager1::vibrateCameraUpdate(string cameraName, float posX, float posY, float intensity, float time)
{
}

void cameraManager1::zoomCameraUpdate(string cameraName, float posX, float posY, float mapSizeX, float scale, float time)
{
}

void cameraManager1::focusOn(float posX, float posY)
{
}



void cameraManager1::vibrateSwitch(bool _isVibrated)
{
}

void cameraManager1::zoomSwitch(bool _isZoomed)
{
}
