#include "stdafx.h"
#include "SecondScene.h"

SecondScene::SecondScene()
{
}

SecondScene::~SecondScene()
{
}

HRESULT SecondScene::Init()
{
    mainCam = new Cam();
    mainCam->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);

    background.Init();
    background.renderer->Init("ui/title.bmp", 640, 480);
    background.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);

    start.Init();
    start.renderer->Init("ui/start.bmp", 288, 24);
    start.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 + 60);

    fadeOut.Init();
    fadeOut.renderer->Init();
    fadeOut.renderer->Resize(640, 480);
    fadeOut.renderer->SetAlpha(0);

    alpha = 0;
    fadeOutTime = 0;
    isStart = 0;
    return S_OK;
}

void SecondScene::Release()
{
}

void SecondScene::Update()
{
    twinkleTime += TIMEMANAGER->getElapsedTime();
    if (twinkleTime >= 0.8f) {
        start.SetActive(!start.isActive);
        twinkleTime = 0;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
        isStart = true;
    }
    if (isStart == true) {
        fadeOutTime += TIMEMANAGER->getElapsedTime();
        if (fadeOutTime >= 0.1f) {
            fadeOut.renderer->SetAlpha(alpha);
            alpha += 2;
            if (alpha >= 255) {
                SCENEMANAGER->LoadScene("start");
                SCENEMANAGER->GetCurScene()->Init();
            }
        }
    }
    background.Update();
    start.Update();
}

void SecondScene::Render()
{
    background.Render();
    start.Render();
    fadeOut.Render();
    mainCam->camera->Render(_hdc);
}
