#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::AddCamera(Camera* newCamera)
{
	if (cameraList.size() == 0) {
		mainCam = newCamera;
	}
	cameraList.push_back(newCamera);
}
