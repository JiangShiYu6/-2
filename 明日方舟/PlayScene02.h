#pragma once

#include "baseMap.h"
#include "cocos2d.h"

class PlayScene02 : public baseMap {
public:
    static cocos2d::Scene* createScene();

     bool init() override;


     void initEnemyWaves()override;
     

    Vector<BaseMonster*> monsters;
    Vector<BaseMonster*> activeMonsters;
    // ������� PlayScene01 ���еķ���������

    CREATE_FUNC(PlayScene02);
};