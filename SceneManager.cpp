#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
    startScene = new StartScene();
    secondScene = new SecondScene();
    AddScene("start", startScene);
    AddScene("second", secondScene);
    //_curScene = startScene;
    //_curScene = secondScene;
    //_curScene->Init();
    return S_OK;
}

void SceneManager::Update()
{
    _curScene->Update();
}

void SceneManager::Render()
{
    _curScene->Render();
}

void SceneManager::Release()
{
}

void SceneManager::AddScene(string sceneName, Scene* scene)
{
    sceneMap.insert(pair<string, Scene*>(sceneName, scene));
}

void SceneManager::LoadScene(string sceneName)
{
    if(_curScene != nullptr)
        _curScene->Release();
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        _curScene = sceneIter->second;
    }
}

Scene* SceneManager::GetScene(string sceneName)
{
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        return sceneIter->second;
    }
    return nullptr;
}

Scene* SceneManager::GetCurScene()
{
    return _curScene;
}
