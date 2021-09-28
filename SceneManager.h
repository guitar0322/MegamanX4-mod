#pragma once
#include "singletonBase.h"

class Scene;
class StartScene;
class SecondScene;

class SceneManager : public singletonBase<SceneManager>
{
private:
	map<string, Scene*> sceneMap;
	map<string, Scene*>::iterator sceneIter;
	Scene* _curScene;
	StartScene* startScene;
	SecondScene* secondScene;
public:
	SceneManager();
	~SceneManager();
	virtual HRESULT Init();
	void Update();
	void Render();
	void Release();
	void AddScene(string sceneName, Scene* scene);
	void LoadScene(string sceneName);
	Scene* GetScene(string sceneName);
	Scene* GetCurScene();
};

