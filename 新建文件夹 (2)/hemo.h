#pragma once
#include"baseHero.h"
#include"cocos2d.h"

class hemo :public BaseCharacter {
public:
    virtual bool init() override;

    virtual void playAttackAnimation() override;
    static SpriteFrameCache* frameCache;
    // ���ÿɷ��õ�λ
    
};
