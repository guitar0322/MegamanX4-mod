#pragma once
class Scene
{
private:
protected:
	int _mapWidth;
	int _mapHeight;
public:
	Scene();
	~Scene();
	Cam* mainCam;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int GetWidth() { return _mapWidth; }
	int GetHeight() { return _mapHeight; }
};

