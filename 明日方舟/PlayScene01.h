#pragma once
#include "baseMap.h"
#include "cocos2d.h"
#include"MapSelect.h"
class PlayScene01 : public baseMap {
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
   
    
    void initEnemyWaves()override;
   
    
    Vector<BaseMonster*> monsters;
    Vector<BaseMonster*> activeMonsters;
    // ������� PlayScene01 ���еķ���������

    CREATE_FUNC(PlayScene01);
};


