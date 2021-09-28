#pragma once
#include "Camera.h"
class CameraManager : public singletonBase<CameraManager>
{
public:
	CameraManager();
	~CameraManager();
	vector<Camera*> cameraList;
	Camera* mainCam;
	Camera* GetMainCam() { return mainCam; }
	void AddCamera(Camera* newCamera);
};

