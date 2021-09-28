#include "stdafx.h"
#include "FragmentManager.h"

void FragmentManager::Init()
{
    trapBlastFrag[0].Init("trap_blast/trap_blast_particle1.bmp", 18, 52, 1, INT_MAX);
    trapBlastFrag[1].Init("trap_blast/trap_blast_particle2.bmp", 26, 16, 1, INT_MAX);
    trapBlastFrag[2].Init("trap_blast/trap_blast_particle3.bmp", 30, 32, 1, INT_MAX);

    privateFrag[0].Init("private/private_particle1.bmp", 32, 22, 1, INT_MAX);
    privateFrag[1].Init("private/private_particle2.bmp", 54, 40, 1, INT_MAX);
    privateFrag[2].Init("private/private_particle3.bmp", 32, 32, 1, INT_MAX);
    privateFrag[3].Init("private/private_particle4.bmp", 32, 52, 1, INT_MAX);
    privateFrag[4].Init("private/private_particle5.bmp", 36, 36, 1, INT_MAX);

    rockFrag[0].Init("map/rock_particle1.bmp", 77, 75, 1, 1);
    rockFrag[1].Init("map/rock_particle2.bmp", 76, 64, 1, 1);
    rockFrag[2].Init("map/rock_particle3.bmp", 97, 78, 1, 1);

    carrierFrag[0].Init("enemy/item_carrier_particle1.bmp", 40, 40, 1, INT_MAX);
    carrierFrag[1].Init("enemy/item_carrier_particle2.bmp", 32, 32, 1, INT_MAX);
    carrierFrag[2].Init("enemy/item_carrier_particle3.bmp", 28, 26, 1, INT_MAX);

    _gravity = 200;
}

void FragmentManager::Update()
{
    for (int i = 0; i < FRAG_MAX; i++) {
        if (fragList[i].isActive == false) continue;
        fragList[i].x += fragList[i].speedX * TIMEMANAGER->getElapsedTime();
        fragList[i].y += fragList[i].speedY * TIMEMANAGER->getElapsedTime();
        fragList[i].speedY += _gravity * TIMEMANAGER->getElapsedTime();
        if (fragList[i].y >= WINSIZEY) {
            fragList[i].isActive = false;
        }
    }
}

void FragmentManager::Render()
{
    for (int i = 0; i < FRAG_MAX; i++) {
        if (fragList[i].isActive == false) continue;
        switch (fragList[i].type) {
        case ROCK:
            GdiTransparentBlt(_backBuffer->getMemDC(),
                fragList[i].x - rockFrag[i % 3].frameWidth / 2, fragList[i].y - rockFrag[i % 3].frameHeight / 2,
                rockFrag[i % 3].frameWidth, rockFrag[i % 3].frameHeight,
                rockFrag[i % 3].wholeDC,
                0, 0,
                rockFrag[i % 3].frameWidth, rockFrag[i % 3].frameHeight,
                RGB(255, 0, 255));
            break;
        case BLAST:
            GdiTransparentBlt(_backBuffer->getMemDC(),
                fragList[i].x - trapBlastFrag[i % 3].frameWidth / 2, fragList[i].y - trapBlastFrag[i % 3].frameHeight / 2,
                trapBlastFrag[i % 3].frameWidth, trapBlastFrag[i % 3].frameHeight,
                trapBlastFrag[i % 3].wholeDC,
                0, 0,
                trapBlastFrag[i % 3].frameWidth, trapBlastFrag[i % 3].frameHeight,
                RGB(255, 0, 255));
            break;
        case PRIVATE:
            GdiTransparentBlt(_backBuffer->getMemDC(),
                fragList[i].x - privateFrag[i % 5].frameWidth / 2, fragList[i].y - privateFrag[i % 5].frameHeight / 2,
                privateFrag[i % 5].frameWidth, privateFrag[i % 5].frameHeight,
                privateFrag[i % 5].wholeDC,
                0, 0,
                privateFrag[i % 5].frameWidth, privateFrag[i % 5].frameHeight,
                RGB(255, 0, 255));
            break;
        case CARRIER:
            GdiTransparentBlt(_backBuffer->getMemDC(),
                fragList[i].x - carrierFrag[i % 3].frameWidth / 2, fragList[i].y - carrierFrag[i % 3].frameHeight / 2,
                carrierFrag[i % 3].frameWidth, carrierFrag[i % 3].frameHeight,
                carrierFrag[i % 3].wholeDC,
                0, 0,
                carrierFrag[i % 3].frameWidth, carrierFrag[i % 3].frameHeight,
                RGB(255, 0, 255));
            break;
        }
    }
}

void FragmentManager::EmissionRockFrag(int x, int y)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < FRAG_MAX; j++) {
            if (fragList[j].isActive == true) continue;
            fragList[i].isActive = true;
            fragList[i].x = x;
            fragList[i].y = y;
            fragList[i].type = ROCK;
            fragList[i].speed = RND->getFromIntTo(200, 250);
            fragList[i].angle = RND->getFloat(PI);
            fragList[i].speedX = fragList[i].speed * cosf(fragList[i].angle);
            fragList[i].speedY = fragList[i].speed * -sinf(fragList[i].angle);
            break;
        }
    }
}

void FragmentManager::EmissionTrapBlastFrag(int x, int y)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < FRAG_MAX; j++) {
            if (fragList[j].isActive == true) continue;
            fragList[j].isActive = true;
            fragList[j].x = x;
            fragList[j].y = y;
            fragList[j].type = BLAST;
            fragList[j].speed = RND->getFromIntTo(100, 150);
            fragList[j].angle = RND->getFloat(PI);
            fragList[j].speedX = fragList[j].speed * cosf(fragList[j].angle);
            fragList[j].speedY = fragList[j].speed * -sinf(fragList[j].angle);
            break;
        }
    }
}

void FragmentManager::EmissionPrivateFrag(int x, int y)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < FRAG_MAX; j++) {
            if (fragList[j].isActive == true) continue;
            fragList[i].isActive = true;
            fragList[i].x = x;
            fragList[i].y = y;
            fragList[i].type = PRIVATE;
            fragList[i].speed = RND->getFromIntTo(100, 150);
            fragList[i].angle = RND->getFloat(PI);
            fragList[i].speedX = fragList[i].speed * cosf(fragList[i].angle);
            fragList[i].speedY = fragList[i].speed * -sinf(fragList[i].angle);
            break;
        }
    }
}

void FragmentManager::EmissionCarrierFrag(int x, int y)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < FRAG_MAX; j++) {
            if (fragList[j].isActive == true) continue;
            fragList[i].isActive = true;
            fragList[i].x = x;
            fragList[i].y = y;
            fragList[i].type = CARRIER;
            fragList[i].speed = RND->getFromIntTo(100, 150);
            fragList[i].angle = RND->getFloat(PI);
            fragList[i].speedX = fragList[i].speed * cosf(fragList[i].angle);
            fragList[i].speedY = fragList[i].speed * -sinf(fragList[i].angle);
            break;
        }
    }
}

FragmentManager* FragmentManager::_instance = 0;
FragmentManager* FragmentManager::GetInstacne()
{
    if (_instance == nullptr) {
        _instance = new FragmentManager();
    }
    return _instance;
}
