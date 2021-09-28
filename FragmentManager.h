#pragma once
#include "GameObject.h"
#define FRAG_MAX 30
class FragmentManager :
    public Component
{
private:
    enum enumFrag {
        ROCK,
        BLAST,
        PRIVATE,
        CARRIER
    };
    typedef struct tagFragment {
        float x, y;
        float angle;
        float speed;
        float speedX;
        float speedY;
        bool isActive;
        enumFrag type;
    }FRAGINFO;
private:
    AnimationClip rockFrag[3];
    AnimationClip trapBlastFrag[3];
    AnimationClip privateFrag[5];
    AnimationClip carrierFrag[3];
    FRAGINFO fragList[FRAG_MAX];
    float _gravity;
    static FragmentManager* _instance;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void EmissionRockFrag(int x, int y);
    void EmissionTrapBlastFrag(int x, int y);
    void EmissionPrivateFrag(int x, int y);
    void EmissionCarrierFrag(int x, int y);

    static FragmentManager* GetInstacne();
};

