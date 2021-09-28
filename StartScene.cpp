#include "stdafx.h"
#include "StartScene.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

HRESULT StartScene::Init()
{
    //인트로
    //레이저 수직이동
    //특정지점에 도달하면 록맨생성
    //록맨은 인트로스테이트로 시작
    //인트로 스테이트 조작불가능.
    //일정시간이후 아이들 스테이트로 전환

    timeStack = 0;
    _mapWidth = 10224;
    _mapHeight = 1494;
    mainCam = new Cam();
    mainCam->camera->SetMapSize(_mapWidth, _mapHeight);
    mainCam->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);

    warning.Init();
    warning.AddComponent(new Warning());
    warning.GetComponent<Warning>()->Init();
    warning.SetActive(false);

    whiteFadeOut.Init();
    whiteFadeOut.uiRenderer->Resize(640, 480);
    whiteFadeOut.uiRenderer->SetAlpha(0);
    whiteFadeOut.uiRenderer->FillColor(RGB(255, 255, 255));
    whiteFadeOut.SetActive(false);

    BackgroundInit();
    RockmanInit();
    ColonelInit();
    MapInit();
    EffectInit();
    ShadowInit();
    ProjectileInit();
    TrapInit();
    EnemyInit();
    rockman.GetComponent<RockMan>()->warning = &warning;

    fadeOut.transform->SetPosition(0, 0);
    fadeOut.uiRenderer->Init();
    fadeOut.uiRenderer->Resize(WINSIZEX, WINSIZEY);
    fadeOut.uiRenderer->SetAlpha(0);

    hpBar.uiRenderer->Init("ui/hp_bar.bmp", 70, 108);
    hpBar.transform->SetPosition(-260, -60);
    hpBar.AddComponent(new HPBar());
    hpBar.GetComponent<HPBar>()->Init(62, rockman.GetComponent<ObjectInfo>());
    hpBar.GetComponent<HPBar>()->SetDelta(11, 13);

    rockman.transform->AddChild(deathBubble.transform);

    FragmentManager::GetInstacne()->Init();
    shadowManager.AddComponent(new ShadowManager());
    shadowManager.GetComponent<ShadowManager>()->Init(rockman.GetComponent<RockMan>());
    for (int i = 0; i < 3; i++) {
        shadowManager.GetComponent<ShadowManager>()->shadow[i] = shadow[i].GetComponent<Shadow>();
    }

    cameraMovement.Init();
    cameraMovement.AddComponent(new CameraMovement());
    cameraMovement.GetComponent<CameraMovement>()->Init(&rockman);

    return S_OK;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    backgroundControl.Update();
    if (hpBar.GetComponent<HPBar>()->GetIsHeal() == false) {
		for (int i = 0; i < TRAP_NUM; i++) {
			trap[i].Update();
		}
    }
    //ui를 최우선을 업데이트
    cameraMovement.Update();
    hpBar.Update();
    warning.Update();

    //체력이 회복중일 경우 업데이트를 중지
    if (hpBar.GetComponent<HPBar>()->GetIsHeal() == true)
        return;
    //인트로 업데이트
    {
		introLazer.transform->position.y += 300 * TIMEMANAGER->getElapsedTime();
		if (introLazer.transform->position.y >= 400) {
			rockman.SetActive(true);
			introLazer.SetActive(false);
		}
		introLazer.Update();
    }

    for (int i = 0; i < BACKGROUND_NUM; i++) {
        background[i].Update();
    }
    holeBackground.Update();
    healPack.Update();
    colonel.Update();

    //록맨 업데이트
    {
		rockman.Update();
		for (int i = 0; i < 3; i++) {
			shadow[i].Update();
		}
		shadowManager.Update();
		chargeOverlap.Update();
		deathBubble.Update();
		wallSparkEffect.Update();
		wallSmokeEffect.Update();
		dashEffect.Update();
		dashSmokeEffect.Update();
		basicAttackEffect.Update();
		middleAttackEffect.Update();
		fullAttackEffect.Update();
		middleChargeEffect.Update();
		fullChargeEffect.Update();
    }

    //지형지물 업데이트
    {
        for (int i = 0; i < GROUND_NUM; i++) {
            ground[i].Update();
        }
        for (int i = 0; i < WALL_NUM; i++) {
            wall[i].Update();
        }
        for (int i = 0; i < FOUNDATION_NUM; i++) {
            foundation[i].Update();
        }
        for (int i = 0; i < FOUNDATION_DOWN_NUM; i++) {
            foundationDown[i].Update();
        }
        for (int i = 0; i < ROCK_NUM; i++) {
            rock[i].Update();
        }
        for (int i = 0; i < SINKHALL_NUM; i++) {
            sinkhole[i].Update();
        }
    }
    //적 오브젝트 업데이트
    {
        for (int i = 0; i < TRAPBLAST_NUM; i++) {
            trapBlast[i].Update();
        }
        for (int i = 0; i < PRIVATE_NUM; i++) {
            soldier[i].Update();
        }
        itemCarrierSpawner.Update();
		itemCarrier.Update();
    }

    for (int i = 0; i < 2; i++) {
        trapWall[i].Update();
    }

    //탄환 업데이트
    {
        for (int i = 0; i < BASIC_PROJECTILE_NUM; i++) {
            basicProjectile[i].Update();
        }
        for (int i = 0; i < TRAPBLAST_PROJECTILE_NUM; i++) {
            trapBlastProjectile[i].Update();
        }
        for (int i = 0; i < PRIVATE_PROJECTILE_NUM; i++) {
            privateProjectile[i].Update();
        }
        for (int i = 0; i < PRIVATE_BOMB_NUM; i++) {
            privateBomb[i].Update();
        }
        middleProjectile.Update();
        fullProjectile.Update();
    }

    for (int i = 0; i < FRONT_NUM; i++) {
        frontObj[i].Update();
    }
    EffectManager::getInstance()->Update();
    FragmentManager::GetInstacne()->Update();
    //mainCam->Update();
    //sprintf_s(debug[0], "%f, %f", mainCam->transform->GetX(), mainCam->transform->GetY());

}

void StartScene::Render()
{
    for (int i = 0; i < BACKGROUND_NUM; i++) {
        background[i].Render();
    }
    holeBackground.Render();
    introLazer.Render();
    //map 지형지물 렌더
    {
        for (int i = 0; i < GROUND_NUM; i++) {
            ground[i].Render();
        }
        for (int i = 0; i < WALL_NUM; i++) {
            wall[i].Render();
        }
        for (int i = 0; i < FOUNDATION_NUM; i++) {
            foundation[i].Render();
        }
        for (int i = 0; i < FOUNDATION_DOWN_NUM; i++) {
            foundationDown[i].Render();
        }
        for (int i = 0; i < SINKHALL_NUM; i++) {
            sinkhole[i].Render();
        }
        for (int i = 0; i < ROCK_NUM; i++) {
            rock[i].Render();
        }
    }


    for (int i = 0; i < 2; i++) {
        trapWall[i].Render();
    }
    //적 오브젝트 렌더
    {
        for (int i = 0; i < TRAPBLAST_NUM; i++) {
            trapBlast[i].Render();
        }
        for (int i = 0; i < PRIVATE_NUM; i++) {
            soldier[i].Render();
        }
		itemCarrier.Render();
    }
    healPack.Render();
    colonel.Render();

    //록맨 렌더
    {
		deathBubble.Render();
		for (int i = 0; i < 3; i++) {
			shadow[i].Render();
		}
		rockman.Render();
		chargeOverlap.Render();
        shadowManager.Render();
        wallSparkEffect.Render();
        wallSmokeEffect.Render();
        dashEffect.Render();
        dashSmokeEffect.Render();
        basicAttackEffect.Render();
        middleAttackEffect.Render();
        fullAttackEffect.Render();
        middleChargeEffect.Render();
        fullChargeEffect.Render();
    }

    //탄환 렌더
    {
        for (int i = 0; i < BASIC_PROJECTILE_NUM; i++) {
            basicProjectile[i].Render();
        }
        for (int i = 0; i < TRAPBLAST_PROJECTILE_NUM; i++) {
            trapBlastProjectile[i].Render();
        }
        for (int i = 0; i < PRIVATE_PROJECTILE_NUM; i++) {
            privateProjectile[i].Render();
        }
        for (int i = 0; i < PRIVATE_BOMB_NUM; i++) {
            privateBomb[i].Render();
        }
        middleProjectile.Render();
        fullProjectile.Render();
    }

    EffectManager::getInstance()->Render();
    FragmentManager::GetInstacne()->Render();
    for (int i = 0; i < FRONT_NUM; i++) {
        frontObj[i].Render();
    }

    //ui 렌더
    {
        hpBar.Render();
        warning.Render();
        whiteFadeOut.Render();
		fadeOut.Render();
    }

    //탭을 누르면 경사면 렌더링
    if (!KEYMANAGER->isToggleKey(VK_TAB)) {
        for (int i = 0; i < 2; i++) {
			LineMake(_backBuffer->getMemDC(),
				slope[i].GetComponent<Slope>()->startX,
				slope[i].GetComponent<Slope>()->y1,
				slope[i].GetComponent<Slope>()->x1,
				slope[i].GetComponent<Slope>()->y1);
			LineMake(_backBuffer->getMemDC(),
				slope[i].GetComponent<Slope>()->x1,
				slope[i].GetComponent<Slope>()->y1,
				slope[i].GetComponent<Slope>()->x2,
				slope[i].GetComponent<Slope>()->y2);
			LineMake(_backBuffer->getMemDC(),
				slope[i].GetComponent<Slope>()->x2,
				slope[i].GetComponent<Slope>()->y2,
				slope[i].GetComponent<Slope>()->endX,
				slope[i].GetComponent<Slope>()->y2);
        }
    }

    //디버그문 출력
    {
		sprintf_s(debug[1], "frame : %f", TIMEMANAGER->getFramePerSec());
		TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, mainCam->transform->GetY() - 220, debug[0], strlen(debug[0]));
		TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, mainCam->transform->GetY() - 200, debug[1], strlen(debug[1]));
		TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, mainCam->transform->GetY() - 180, debug[2], strlen(debug[2]));
		TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, mainCam->transform->GetY() - 160, error, strlen(error));
    }

    mainCam->Update();
    mainCam->camera->Render(_hdc);
}

void StartScene::BackgroundInit()
{
    char fileName[32];
    int startX = 320;
    for (int i = 0; i < BACKGROUND_NUM; i++) {
        background[i].name = "background";
        background[i].SetActive(false);
        sprintf_s(fileName, "map/map%d.bmp", i + 1);
        background[i].renderer->Init(fileName, 639, 485);
        background[i].transform->SetPosition(320 + i * 639, 240);
    }

    holeBackground.name = "background";
    holeBackground.SetActive(false);
    holeBackground.renderer->Init("map/map_hole.bmp", 1540, 1006);
    holeBackground.transform->SetPosition(7736, 981);

    backgroundControl.AddComponent(new BackgroundControl());
    backgroundControl.GetComponent<BackgroundControl>()->Init(&rockman);
    for (int i = 0; i < BACKGROUND_NUM; i++) {
        backgroundControl.GetComponent<BackgroundControl>()->background[i] = &background[i];
    }
    backgroundControl.GetComponent<BackgroundControl>()->holeBackground = &holeBackground;
}

void StartScene::RockmanInit()
{
    introLazer.Init();
    introLazer.renderer->Init("other/intro_lazer.bmp", 42, 128);
    introLazer.transform->SetPosition(280, -100);

    rockman.Init();
    rockman.name = "rockman";
    rockman.tag = TAGMANAGER->GetTag("player");

    rockman.transform->SetPosition(280, 385);
    //rockman.transform->SetPosition(9600, 300);
    rockman.SetActive(false);
    rockman.AddComponent(new RockMan());
    rockman.AddComponent(new Renderer());
    rockman.AddComponent(new BoxCollider());
    rockman.AddComponent(new Animator());
    rockman.AddComponent(new PlayerControler());
    rockman.AddComponent(new ObjectInfo());


    rockman.GetComponent<Renderer>()->Init();

    rockman.GetComponent<BoxCollider>()->Init();
    rockman.GetComponent<BoxCollider>()->SetSize(74, 90);

    rockman.GetComponent<Animator>()->Init();

    rockman.GetComponent<PlayerControler>()->Init();
    rockman.GetComponent<PlayerControler>()->SetRockman(rockman.GetComponent<RockMan>());

    rockman.GetComponent<RockMan>()->Init();
    rockman.GetComponent<RockMan>()->shadowManager = &shadowManager;
    rockman.GetComponent<RockMan>()->hpBar = &hpBar;

    rockman.GetComponent<ObjectInfo>()->Init(100, 0, 3);
    rockman.GetComponent<ObjectInfo>()->SetOverlapTime(4.0f);
}

void StartScene::ColonelInit()
{
    colonel.tag = TAGMANAGER->GetTag("enemy");
    colonel.transform->SetPosition(9900 + WINSIZEX / 2 - 80, 355);
    //colonel.AddComponent(new Overlap());
    //colonel.GetComponent<Overlap>()->Init();
    //colonel.GetComponent<Overlap>()->SetAlpha(170);
    //colonel.GetComponent<Overlap>()->SetColor(RGB(255, 255, 255));
    colonel.AddComponent(new ObjectInfo());
    colonel.GetComponent<ObjectInfo>()->Init(600, 0, 5);
    colonel.GetComponent<ObjectInfo>()->SetOverlapTime(4.0f);
    colonel.AddComponent(new Colonel());
    colonel.GetComponent<Colonel>()->Init(&rockman);
    colonel.GetComponent<Colonel>()->whiteFadeOut = &whiteFadeOut;
    colonel.SetActive(false);
    colonel.collider->isTrigger = true;
    colonel.collider->SetSize(120, 110);
    rockman.GetComponent<RockMan>()->colonel = &colonel;
    warning.GetComponent<Warning>()->colonel = &colonel;
}

void StartScene::MapInit()
{
    for (int i = 0; i < FRONT_NUM; i++) {
        frontObj[i].Init();
    }
    frontObj[0].renderer->Init("map/front_object.bmp", 400, 449);
    frontObj[0].transform->SetPosition(153, 252);

    frontObj[1].renderer->Init("map/front_object2.bmp", 349, 119);
    frontObj[1].transform->SetPosition(2994, 416);

    frontObj[2].renderer->Init("map/front_object3.bmp", 278, 376);
    frontObj[2].transform->SetPosition(3595, 186);

    frontObj[3].renderer->Init("map/front_object.bmp", 400, 449);
    frontObj[3].transform->SetPosition(5656, 252);

    frontObj[4].renderer->Init("map/front_object2.bmp", 349, 119);
    frontObj[4].transform->SetPosition(6194, 416);

    frontObj[5].renderer->Init("map/front_object4.bmp", 343, 323);
    frontObj[5].transform->SetPosition(7092, 495);

    frontObj[6].renderer->Init("map/front_object5.bmp", 324, 311);
    frontObj[6].transform->SetPosition(7873, 515);

    frontObj[7].renderer->Init("map/front_object.bmp", 400, 449);
    frontObj[7].transform->SetPosition(8859, 252);

    frontObj[8].renderer->Init("map/front_object6.bmp", 156, 162);
    frontObj[8].transform->SetPosition(9262, 393);
    for (int i = 0; i < GROUND_NUM; i++) {
        char groundName[16];
        sprintf_s(groundName, "ground%d", i);
        ground[i].tag = TAGMANAGER->GetTag("ground");
        ground[i].name = groundName;
        ground[i].collider->weight = INT_MAX;
    }
    ground[0].renderer->Init();
    ground[0].collider->SetSize(1700, 100);
    ground[0].transform->SetPosition(1700 / 2, WINSIZEY / 2 + 240);

    ground[1].renderer->Init();
    ground[1].collider->SetSize(930, 100);
    ground[1].transform->SetPosition(1920 + 930/2, 430);

    ground[2].renderer->Init();
    ground[2].collider->SetSize(350, 60);
    ground[2].transform->SetPosition(3070 + 350 / 2, 480 - 60 / 2);

    ground[3].renderer->Init();
    ground[3].collider->SetSize(280, 200);
    ground[3].transform->SetPosition(3747 + 280 / 2, 480 - 200 / 2);

    ground[4].renderer->Init();
    ground[4].collider->SetSize(190, 70);
    ground[4].transform->SetPosition(4030 + 190 / 2, 480 - 70 / 2);

    ground[5].renderer->Init();
    ground[5].collider->SetSize(900, 70);
    ground[5].transform->SetPosition(4420 + 900 / 2, 480 - 70 / 2);

    ground[6].renderer->Init();
    ground[6].collider->SetSize(510, 36);
    ground[6].transform->SetPosition(5310 + 510 / 2, 480 - 36 / 2);

    ground[7].renderer->Init();
    ground[7].collider->SetSize(130, 60);
    ground[7].transform->SetPosition(5820 + 130 / 2, 480 - 60 / 2);

    ground[8].renderer->Init();
    ground[8].collider->SetSize(1050, 60);
    ground[8].transform->SetPosition(6200 + 1050 / 2, 480 - 60 / 2);

    ground[9].renderer->Init();
    ground[9].collider->SetSize(2510, 60);
    ground[9].transform->SetPosition(7720 + 2510 / 2, 480 - 60 / 2);

    ground[10].renderer->Init();
    ground[10].collider->SetSize(450, 114);
    ground[10].transform->SetPosition(7489, 1494);

    sinkhole[0].renderer->Init("map/sinkhole1.bmp", 192, 115);
    sinkhole[0].collider->SetSize(192, 27);
    sinkhole[0].transform->SetPosition(4318, 480 - 115/2);
    sinkhole[0].name = "sinkhole0";

    sinkhole[1].renderer->Init("map/sinkhole2.bmp", 455, 95);
    sinkhole[1].collider->SetSize(455, 20);
    sinkhole[1].transform->SetPosition(7484, 437);
    sinkhole[1].name = "sinkhole1";

    for (int i = 0; i < WALL_NUM; i++) {
        char wallName[16];
        sprintf_s(wallName, "wall%d", i);
        wall[i].name = wallName;
        wall[i].collider->weight = INT_MAX;
    }
    wall[0].renderer->Init();
    wall[0].collider->SetSize(30, 248);
    wall[0].transform->SetPosition(960 + 30 / 2, 300);

    wall[1].renderer->Init();
    wall[1].collider->SetSize(30, 250);
    wall[1].transform->SetPosition(1260, 370);

    wall[2].renderer->Init();
    wall[2].collider->SetSize(50, 120);
    wall[2].transform->SetPosition(1690, 400);

    wall[3].renderer->Init();
    wall[3].collider->SetSize(220, 390);
    wall[3].transform->SetPosition(2850 + 220 / 2, 480 - 390 / 2);

    wall[4].renderer->Init();
    wall[4].collider->SetSize(250, 190);
    wall[4].transform->SetPosition(4930 + 250 / 2, 315);

    wall[5].renderer->Init();
    wall[5].collider->SetSize(250, 350);
    wall[5].transform->SetPosition(5950 + 250 / 2, 480 - 350 / 2);

    wall[6].renderer->Init();
    wall[6].collider->SetSize(250, 290);
    wall[6].transform->SetPosition(6340 + 250 / 2, 290 / 2);

    wall[7].renderer->Init();
    wall[7].collider->SetSize(320, 170);
    wall[7].transform->SetPosition(6850 + 320 / 2, 480 - 60 - 170 / 2);

    wall[8].renderer->Init();
    wall[8].collider->SetSize(320, 126);
    wall[8].transform->SetPosition(6850 + 320 / 2, 126 / 2);

    trapWall[0].renderer->Init("map/trap_wall_right.bmp", 513, 954);
    trapWall[0].collider->SetSize(500, 954);
    trapWall[0].collider->weight = 2;
    trapWall[0].transform->SetPosition(7969, 957);
    trapWall[0].name = "trapWall0";

    trapWall[1].renderer->Init("map/trap_wall_left.bmp", 513, 954);
    trapWall[1].collider->SetSize(500, 954);
    trapWall[1].collider->weight = 2;
    trapWall[1].transform->SetPosition(7006, 957);
    trapWall[1].name = "trapWall1";

    slope[0].Init();
    slope[0].AddComponent(new Slope());
    slope[0].GetComponent<Slope>()->Init(940, 1280, 990, 165, 1280, 250);
    rockman.GetComponent<RockMan>()->slope[0] = &slope[0];
    slope[1].Init();
    slope[1].AddComponent(new Slope());
    slope[1].GetComponent<Slope>()->Init(3420, 3747, 3460, 420, 3710, 280);
    rockman.GetComponent<RockMan>()->slope[1] = &slope[1];

    for (int i = 0; i < FOUNDATION_NUM; i++) {
        foundation[i].renderer->Init("map/foundation.bmp", 192, 161);
        foundation[i].collider->SetSize(192, 161);
    }
    foundation[0].transform->SetPosition(1502, -52);
    foundation[0].name = "foundation0";

    for (int i = 0; i < FOUNDATION_DOWN_NUM; i++) {
        foundationDown[i].renderer->Init("map/foundation_down.bmp", 192, 190);
        foundationDown[i].collider->SetSize(192, 160);
    }
    foundationDown[0].transform->SetPosition(1824, -82);
    foundationDown[0].collider->weight = 2;
    foundationDown[0].name = "foundationDown0";

    for (int i = 0; i < ROCK_NUM; i++) {
		rock[i].tag = TAGMANAGER->GetTag("enemy");
		rock[i].renderer->Init("map/rock.bmp", 192, 161);
		rock[i].collider->SetSize(192, 161);
		rock[i].AddComponent(new ObjectInfo());
		rock[i].GetComponent<ObjectInfo>()->Init(100, 7, 0);
        rock[i].GetComponent<ObjectInfo>()->SetExplosionRange(100, 100);
        rock[i].collider->weight = 2;
        char rockName[16];
        sprintf_s(rockName, "rock%d", i);
        rock[i].name = rockName;
    }
	rock[0].transform->SetPosition(1120, -82);
    rock[1].transform->SetPosition(1504, 109);
    rock[2].transform->SetPosition(2146, 144);
    rock[3].transform->SetPosition(2464, 144);
    rock[4].transform->SetPosition(4318, -82);
}

void StartScene::EnemyInit()
{
    for (int i = 0; i < TRAPBLAST_NUM; i++) {
        trapBlast[i].tag = TAGMANAGER->GetTag("enemy");
        trapBlast[i].SetActive(false);
        trapBlast[i].AddComponent(new Renderer());
        trapBlast[i].GetComponent<Renderer>()->Init();
        trapBlast[i].AddComponent(new BoxCollider());
        trapBlast[i].GetComponent<BoxCollider>()->Init();
        trapBlast[i].GetComponent<BoxCollider>()->isTrigger = true;
        trapBlast[i].AddComponent(new Animator());
        trapBlast[i].GetComponent<Animator>()->Init();
        trapBlast[i].AddComponent(new TrapBlast());
        trapBlast[i].AddComponent(new ObjectInfo());
        trapBlast[i].GetComponent<ObjectInfo>()->Init(40, 1, 1);
        trapBlast[i].GetComponent<ObjectInfo>()->SetExplosionRange(0, 0);
    }
    trapBlast[0].transform->SetPosition(939, 254);
    trapBlast[0].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[1].transform->SetPosition(939, 354);
    trapBlast[1].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[2].transform->SetPosition(1297, 354);
    trapBlast[2].GetComponent<TrapBlast>()->Init(&rockman, false);

    trapBlast[3].transform->SetPosition(2821, 169);
    trapBlast[3].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[4].transform->SetPosition(2821, 249);
    trapBlast[4].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[5].transform->SetPosition(2821, 329);
    trapBlast[5].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[6].transform->SetPosition(4052, 368);
    trapBlast[6].GetComponent<TrapBlast>()->Init(&rockman, false);

    trapBlast[7].transform->SetPosition(6313, 69);
    trapBlast[7].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[8].transform->SetPosition(6313, 149);
    trapBlast[8].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[9].transform->SetPosition(6819, 62);
    trapBlast[9].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[10].transform->SetPosition(6819, 354);
    trapBlast[10].GetComponent<TrapBlast>()->Init(&rockman, true);

    trapBlast[11].transform->SetPosition(6608, 194);
    trapBlast[11].GetComponent<TrapBlast>()->Init(&rockman, false);

    for (int i = 0; i < PRIVATE_NUM; i++) {
        soldier[i].tag = TAGMANAGER->GetTag("enemy");
        soldier[i].AddComponent(new Renderer());
        soldier[i].GetComponent<Renderer>()->Init();
        soldier[i].AddComponent(new BoxCollider());
        soldier[i].GetComponent<BoxCollider>()->Init();
        soldier[i].GetComponent<BoxCollider>()->isTrigger = true;
        soldier[i].AddComponent(new Animator());
        soldier[i].GetComponent<Animator>()->Init();
        soldier[i].AddComponent(new Soldier());
        soldier[i].AddComponent(new ObjectInfo());
        soldier[i].GetComponent<ObjectInfo>()->Init(100, 1, 2);
        soldier[i].GetComponent<ObjectInfo>()->SetExplosionRange(0, 0);
    }

    soldier[0].transform->SetPosition(1694, 269);
    soldier[0].GetComponent<Soldier>()->Init(&rockman, true);

    soldier[1].transform->SetPosition(2687, 321);
    soldier[1].GetComponent<Soldier>()->Init(&rockman, true);

    soldier[2].transform->SetPosition(3878, 224);
    soldier[2].GetComponent<Soldier>()->Init(&rockman, true);

    soldier[3].transform->SetPosition(5066, 169);
    soldier[3].GetComponent<Soldier>()->Init(&rockman, true);

    itemCarrier.tag = TAGMANAGER->GetTag("enemy");
	itemCarrier.AddComponent(new Renderer());
	itemCarrier.GetComponent<Renderer>()->Init();
	itemCarrier.AddComponent(new BoxCollider());
	itemCarrier.GetComponent<BoxCollider>()->Init();
    itemCarrier.GetComponent<BoxCollider>()->isTrigger = true;
	itemCarrier.AddComponent(new Animator());
	itemCarrier.GetComponent<Animator>()->Init();
	itemCarrier.AddComponent(new ItemCarrier());
	itemCarrier.GetComponent<ItemCarrier>()->Init();
    itemCarrier.GetComponent<ItemCarrier>()->healPack = &healPack;
	itemCarrier.AddComponent(new ObjectInfo());
	itemCarrier.GetComponent<ObjectInfo>()->Init(50, 1, 4);
    itemCarrier.SetActive(false);

    itemCarrierSpawner.AddComponent(new ItemCarrierSpawner());
    itemCarrierSpawner.GetComponent<ItemCarrierSpawner>()->Init();
    itemCarrierSpawner.GetComponent<ItemCarrierSpawner>()->SetItemCarrier(&itemCarrier);
    itemCarrierSpawner.GetComponent<ItemCarrierSpawner>()->SetRockmanInfo(rockman.GetComponent<ObjectInfo>());

    healPack.tag = TAGMANAGER->GetTag("heal");
    healPack.AddComponent(new Animator());
    healPack.GetComponent<Animator>()->Init();
    healPack.AddComponent(new HealPack());
    healPack.GetComponent<HealPack>()->Init();
    healPack.collider->SetSize(44, 26);
    healPack.collider->isTrigger = true;
    healPack.SetActive(false);
}

void StartScene::EffectInit()
{
    AnimationClip fireExplosion, dustExplosion, hitEffect, bigHitEffectRight, bigHitEffectLeft;
    AnimationClip blockHitEffectRight, blockHitEffectLeft;
    fireExplosion.Init("effect/big_explode.bmp", 2304, 124, 18, 0.06f);
    dustExplosion.Init("effect/small_explode.bmp", 2048, 124, 16, 0.06f);
    hitEffect.Init("effect/hit_effect.bmp", 160, 62, 4, 0.06f);
    bigHitEffectRight.Init("effect/big_hit_effect_left.bmp", 480, 176, 4, 0.06f);
    bigHitEffectLeft.Init("effect/big_hit_effect_right.bmp", 480, 176, 4, 0.06f);
    blockHitEffectRight.Init("effect/block_hit_effect_left.bmp", 400, 132, 5, 0.08f);
    blockHitEffectLeft.Init("effect/block_hit_effect_right.bmp", 400, 132, 5, 0.08f);

    EffectManager::getInstance()->Init();
	EffectManager::getInstance()->AddEffect("fire_explosion", fireExplosion);
	EffectManager::getInstance()->AddEffect("dust_explosion", dustExplosion);
	EffectManager::getInstance()->AddEffect("hit_effect", hitEffect);
	EffectManager::getInstance()->AddEffect("big_hit_effect_right", bigHitEffectRight);
	EffectManager::getInstance()->AddEffect("big_hit_effect_left", bigHitEffectLeft);
    EffectManager::getInstance()->AddEffect("block_hit_right", blockHitEffectRight);
    EffectManager::getInstance()->AddEffect("block_hit_left", blockHitEffectLeft);

    dashSmokeEffect.Init(0.64f);
    dashSmokeEffect.AddClip("effect/dash_smoke_right.bmp", 928, 72, 8, 0.08f, EffectObj::START, false);
    dashSmokeEffect.AddClip("effect/dash_smoke_left.bmp", 928, 72, 8, 0.08f, EffectObj::START, true);
    rockman.GetComponent<RockMan>()->dashSmokeEffect = &dashSmokeEffect;

    dashEffect.Init(0.70f);
    dashEffect.AddClip("effect/dash_effect_right.bmp", 574, 60, 7, 0.10f, EffectObj::START, false);
    dashEffect.AddClip("effect/dash_effect_left.bmp", 574, 60, 7, 0.10f, EffectObj::START, true);
    rockman.GetComponent<RockMan>()->dashEffect = &dashEffect;

    wallSmokeEffect.Init(0.29f);
    wallSmokeEffect.AddClip("effect/wall_smoke_intro_right.bmp", 80, 78, 2, 0.1f, EffectObj::START, false);
    wallSmokeEffect.AddClip("effect/wall_smoke_intro_left.bmp", 80, 78, 2, 0.1f, EffectObj::START, true);
    wallSmokeEffect.AddClip("effect/wall_smoke_idle_right.bmp", 120, 78, 3, 0.1f, EffectObj::IDLE, false);
    wallSmokeEffect.AddClip("effect/wall_smoke_idle_left.bmp", 120, 78, 3, 0.1f, EffectObj::IDLE, true);
    wallSmokeEffect.AddClip("effect/wall_smoke_end_right.bmp", 120, 78, 3, 0.1f, EffectObj::END, false);
    wallSmokeEffect.AddClip("effect/wall_smoke_end_left.bmp", 120, 78, 3, 0.1f, EffectObj::END, true);
    rockman.GetComponent<RockMan>()->wallSmokeEffect = &wallSmokeEffect;

    wallSparkEffect.Init(0.32f);
    wallSparkEffect.AddClip("effect/wall_spark.bmp", 272, 68, 4, 0.08f, EffectObj::START, false);
    rockman.GetComponent<RockMan>()->wallSparkEffect = &wallSparkEffect;

    basicAttackEffect.Init(0.44f);
    basicAttackEffect.AddClip("projectile/basic_attack_effect_right.bmp", 200, 52, 5, 0.08f, EffectObj::START, false);
    basicAttackEffect.AddClip("projectile/basic_attack_effect_left.bmp", 200, 52, 5, 0.08f, EffectObj::START, true);
    rockman.GetComponent<RockMan>()->basicAttackEffect = &basicAttackEffect;

    middleAttackEffect.Init(0.35f);
    middleAttackEffect.AddClip("projectile/middle_attack_effect_right.bmp", 192, 48, 4, 0.08f, EffectObj::START, false);
    middleAttackEffect.AddClip("projectile/middle_attack_effect_left.bmp", 192, 48, 4, 0.08f, EffectObj::START, true);
    rockman.GetComponent<RockMan>()->middleAttackEffect = &middleAttackEffect;

    fullAttackEffect.Init(0.50f);
    fullAttackEffect.AddClip("projectile/full_attack_effect_right.bmp", 552, 156, 6, 0.08f, EffectObj::START, false);
    fullAttackEffect.AddClip("projectile/full_attack_effect_left.bmp", 552, 156, 6, 0.08f, EffectObj::START, true);
    rockman.GetComponent<RockMan>()->fullAttackEffect = &fullAttackEffect;

    middleChargeEffect.Init(0);
    middleChargeEffect.AddClip("effect/middle_charge_effect.bmp", 1800, 180, 10, 0.06f, EffectObj::START, false);
    middleChargeEffect.AddClip("effect/middle_charge_effect.bmp", 1800, 180, 10, 0.06f, EffectObj::IDLE, false);
    middleChargeEffect.AddClip("effect/middle_charge_effect.bmp", 1800, 180, 10, 0.06f, EffectObj::END, false);
    middleChargeEffect.transform->SetPosition(rockman.transform->GetX(), rockman.transform->GetY());

    rockman.GetComponent<RockMan>()->middleChargeEffect = &middleChargeEffect;
    rockman.transform->AddChild(middleChargeEffect.transform);

    fullChargeEffect.Init(0);
    fullChargeEffect.AddClip("effect/full_charge_effect.bmp", 640, 116, 5, 0.06f, EffectObj::START, false);
    fullChargeEffect.AddClip("effect/full_charge_effect.bmp", 640, 116, 5, 0.06f, EffectObj::IDLE, false);
    fullChargeEffect.AddClip("effect/full_charge_effect.bmp", 640, 116, 5, 0.06f, EffectObj::END, false);
    fullChargeEffect.transform->SetPosition(rockman.transform->GetX(), rockman.transform->GetY());

    rockman.GetComponent<RockMan>()->fullChargeEffect = &fullChargeEffect;
    rockman.transform->AddChild(fullChargeEffect.transform);

    chargeOverlap.Init();
    chargeOverlap.AddComponent(new ChargeOverlap());
    chargeOverlap.GetComponent<ChargeOverlap>()->Init(rockman.GetComponent<Renderer>(), RGB(107, 200, 231));
    chargeOverlap.SetActive(false);
    chargeOverlap.transform->SetPosition(rockman.transform->GetX(), rockman.transform->GetY());
    rockman.GetComponent<RockMan>()->chargeOverlap = &chargeOverlap;
    rockman.transform->AddChild(chargeOverlap.transform);

    deathBubble.Init();
    deathBubble.AddComponent(new DeathBubble());
    deathBubble.GetComponent<DeathBubble>()->Init();
    deathBubble.GetComponent<DeathBubble>()->fadeOut = fadeOut.GetComponent<UIRenderer>();
    deathBubble.SetActive(false);
    deathBubble.transform->SetPosition(rockman.transform->GetX(), rockman.transform->GetY());
}

void StartScene::ShadowInit()
{
    for (int i = 0; i < 3; i++) {
        shadow[i].Init();
        shadow[i].AddComponent(new Shadow());
        shadow[i].GetComponent<Shadow>()->Init(rockman.GetComponent<Renderer>());
        shadow[i].SetActive(false);
    }
}

void StartScene::ProjectileInit()
{
    AnimationClip* basicClipRight = new AnimationClip();
    AnimationClip* basicClipLeft = new AnimationClip();
    basicClipRight->Init("projectile/basic_attack_projectile_right.bmp", 150, 16, 5, 0.15f);
    basicClipLeft->Init("projectile/basic_attack_projectile_left.bmp", 150, 16, 5, 0.15f);
    for (int i = 0; i < BASIC_PROJECTILE_NUM; i++) {
        basicProjectile[i].Init();
        basicProjectile[i].AddComponent(new StraightProjectile());
        basicProjectile[i].GetComponent<StraightProjectile>()->Init("enemy", "hit_effect", 10, 3.0f);
        basicProjectile[i].GetComponent<StraightProjectile>()->SetNeedEffectDir(false);
        basicProjectile[i].GetComponent<StraightProjectile>()->SetSpeed(400);
        basicProjectile[i].animator->AddClip("right", basicClipRight);
        basicProjectile[i].animator->AddClip("left", basicClipLeft);
        basicProjectile[i].collider->SetSize(30, 16);
        basicProjectile[i].collider->isTrigger = true;
        basicProjectile[i].SetActive(false);
        ProjectileManager::GetInstance()->basicProjectile[i] = &basicProjectile[i];
    }

    AnimationClip* middleClipRight = new AnimationClip();
    AnimationClip* middleClipLeft = new AnimationClip();
    middleClipRight->Init("projectile/middle_attack_projectile_right.bmp", 208, 36, 4, 0.15f);
    middleClipLeft->Init("projectile/middle_attack_projectile_left.bmp", 208, 36, 4, 0.15f);

    middleProjectile.Init();
    middleProjectile.AddComponent(new StraightProjectile());
    middleProjectile.GetComponent<StraightProjectile>()->Init("enemy", "hit_effect", 20, 3.0f);
    middleProjectile.GetComponent<StraightProjectile>()->SetNeedEffectDir(false);
    middleProjectile.GetComponent<StraightProjectile>()->SetSpeed(400);
    middleProjectile.animator->AddClip("right", middleClipRight);
    middleProjectile.animator->AddClip("left", middleClipLeft);
    middleProjectile.collider->SetSize(52, 36);
    middleProjectile.collider->isTrigger = true;
    middleProjectile.SetActive(false);
    ProjectileManager::GetInstance()->middleProjectile = &middleProjectile;


    AnimationClip* fullClipRight = new AnimationClip();
    AnimationClip* fullClipLeft = new AnimationClip();
    fullClipRight->Init("projectile/full_attack_projectile_right.bmp", 348, 58, 3, 0.15f);
    fullClipLeft->Init("projectile/full_attack_projectile_left.bmp", 348, 58, 3, 0.15f);

    fullProjectile.Init();
    fullProjectile.AddComponent(new StraightProjectile());
    fullProjectile.GetComponent<StraightProjectile>()->Init("enemy", "big_hit_effect", 50, 3.0f);
    fullProjectile.GetComponent<StraightProjectile>()->SetNeedEffectDir(true);
    fullProjectile.GetComponent<StraightProjectile>()->SetSpeed(400);
    fullProjectile.animator->AddClip("right", fullClipRight);
    fullProjectile.animator->AddClip("left", fullClipLeft);
    fullProjectile.collider->SetSize(116, 58);
    fullProjectile.collider->isTrigger = true;
    fullProjectile.SetActive(false);
    ProjectileManager::GetInstance()->fullProjectile = &fullProjectile;

    AnimationClip* trapBlastClip = new AnimationClip();
    trapBlastClip->Init("projectile/trap_blast_projectile.bmp", 168, 50, 4, 0.15f);

    for (int i = 0; i < TRAPBLAST_PROJECTILE_NUM; i++) {
        trapBlastProjectile[i].Init();
        trapBlastProjectile[i].AddComponent(new TrapBlastProjectile());
        trapBlastProjectile[i].GetComponent<TrapBlastProjectile>()->Init("player", "none", 10, 3.0f);
        trapBlastProjectile[i].GetComponent<TrapBlastProjectile>()->SetNeedEffectDir(false);
        trapBlastProjectile[i].GetComponent<TrapBlastProjectile>()->SetSpeed(100);
        trapBlastProjectile[i].GetComponent<TrapBlastProjectile>()->SetRockman(&rockman);
        trapBlastProjectile[i].animator->AddClip("right", trapBlastClip);
        trapBlastProjectile[i].collider->SetSize(25, 25);
        trapBlastProjectile[i].collider->isTrigger = true;
        trapBlastProjectile[i].SetActive(false);
        ProjectileManager::GetInstance()->trapBlastProjectile[i] = &trapBlastProjectile[i];
    }

    AnimationClip* privateClip = new AnimationClip();
    privateClip->Init("projectile/private_projectile.bmp", 96, 22, 4, 0.30f);
    for (int i = 0; i < PRIVATE_PROJECTILE_NUM; i++) {
        privateProjectile[i].Init();
        privateProjectile[i].AddComponent(new StraightProjectile());
        privateProjectile[i].GetComponent<StraightProjectile>()->Init("player", "none", 10, 3.0f);
        privateProjectile[i].GetComponent<StraightProjectile>()->SetNeedEffectDir(false);
        privateProjectile[i].GetComponent<StraightProjectile>()->SetSpeed(150);
        privateProjectile[i].animator->AddClip("right", privateClip);
        privateProjectile[i].animator->AddClip("left", privateClip);
        privateProjectile[i].collider->SetSize(24, 22);
        privateProjectile[i].collider->isTrigger = true;
        privateProjectile[i].SetActive(false);
        ProjectileManager::GetInstance()->privateProjectile[i] = &privateProjectile[i];
    }

    AnimationClip* privateBombClip = new AnimationClip();
    privateBombClip->isLoop = false;
    privateBombClip->Init("projectile/private_throw_projectile.bmp", 24, 20, 1, 0.0f);
    for (int i = 0; i < PRIVATE_BOMB_NUM; i++) {
        privateBomb[i].Init();
        privateBomb[i].AddComponent(new PrivateBomb());
        privateBomb[i].GetComponent<PrivateBomb>()->Init("player", "fire_explosion", 15, 5.0f);
        privateBomb[i].GetComponent<PrivateBomb>()->SetNeedEffectDir(false);
        privateBomb[i].GetComponent<PrivateBomb>()->SetSpeed(150);
        privateBomb[i].animator->AddClip("right", privateBombClip);
        privateBomb[i].animator->AddClip("left", privateBombClip);
        privateBomb[i].collider->SetSize(24, 20);
        privateBomb[i].collider->isTrigger = true;
        privateBomb[i].SetActive(false);
        ProjectileManager::GetInstance()->privateBomb[i] = &privateBomb[i];
    }
}

void StartScene::TrapInit()
{
    for (int i = 0; i < TRAP_NUM; i++) {
        trap[i].AddComponent(new TrapBehavior());
    }
    TrapBehavior* trapBehavior;
    trapBehavior = trap[0].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 995, 0);
    trapBehavior->AddMoveBehavior(true, { &rock[0] }, MoveBehavior::DOWN, 150, 20, 200, { -28 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 4, { 1040, 1240 }, { 0, 50 });

    trapBehavior = trap[1].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 1250, 0);
    trapBehavior->AddMoveBehavior(true, { &rock[1], &foundation[0] }, MoveBehavior::DOWN, 100, 100, 300, { 242, 80 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 4, { 1430, 1630 }, { 0, 50 });

    trapBehavior = trap[2].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 1700, 0);
    trapBehavior->AddMoveBehavior(true, { &foundationDown[0] }, MoveBehavior::DOWN, 100, 150, 300, { 393 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 4, { 1744, 1944 }, { 460, 461 });

    trapBehavior = trap[3].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 2300, 0);
    trapBehavior->AddMoveBehavior(true, { &rock[2]}, MoveBehavior::DOWN, 100, 150, 300, { 295 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 4, { 2086, 2286 }, { 380, 381 });

    trapBehavior = trap[4].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 2300, 0);
    trapBehavior->AddMoveBehavior(true, { &rock[3] }, MoveBehavior::DOWN, 100, 150, 300, { 295 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 4, { 2384, 2584 }, { 380, 381 });

    trapBehavior = trap[5].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 4100, 0);
    trapBehavior->AddMoveBehavior(true, { &rock[4] }, MoveBehavior::DOWN, 100, 150, 300, { 288 });
    trapBehavior->AddEffectBehavior(false, "dust_explosion", 10, { 4238, 4438 }, { 400, 430 });
    trapBehavior->AddSpawnBehavior(false, { false }, { &sinkhole[0] });
    trapBehavior->AddMoveBehavior(false, { &rock[4] }, MoveBehavior::DOWN, 50, 150, 300, { 650 });

    trapBehavior = trap[6].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 7489, 0);
	trapBehavior->AddMoveBehavior(true, { &sinkhole[1] }, MoveBehavior::DOWN, 300, 12, 300, { 1420 });
	trapBehavior->AddEffectBehavior(true, "dust_explosion", 12, { 7265, 7720 }, { 450, 470 });
	trapBehavior->AddSpawnBehavior(false, { false }, { &sinkhole[1] });
	trapBehavior->AddEffectBehavior(false, "dust_explosion", 12, { 7265, 7720 }, { 1400, 1410 });

    trapBehavior = trap[7].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 7486, 1390);
    trapBehavior->AddMoveBehavior(true, { &trapWall[0] }, MoveBehavior::LEFT, 20, 0, 20, { 7746 });
    trapBehavior->AddMoveBehavior(true, { &trapWall[1] }, MoveBehavior::RIGHT, 20, 0, 20, { 7226 });

    trapBehavior = trap[8].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 750, 0);
    trapBehavior->AddSpawnBehavior(true, { true, true }, { &trapBlast[0], &trapBlast[1] });

    trapBehavior = trap[9].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 1240, 0);
    trapBehavior->AddSpawnBehavior(true, { true }, { &trapBlast[2] });

    trapBehavior = trap[10].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 2570, 0);
    trapBehavior->AddSpawnBehavior(true, { true, true, true }, { &trapBlast[3], &trapBlast[4], &trapBlast[5] });

    trapBehavior = trap[11].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 3940, 0);
    trapBehavior->AddSpawnBehavior(true, { true }, { &trapBlast[6] });

    trapBehavior = trap[12].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 6110, 0);
    trapBehavior->AddSpawnBehavior(true, { true, true }, { &trapBlast[7], &trapBlast[8] });

    trapBehavior = trap[13].GetComponent<TrapBehavior>();
    trapBehavior->Init(&rockman, 6654, 0);
    trapBehavior->AddSpawnBehavior(true, { true, true, true }, { &trapBlast[9], &trapBlast[10], &trapBlast[11] });
}

