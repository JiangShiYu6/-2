#pragma once
#include "cocos2d.h"

class PlayScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    void updateCoins(float dt); // ������Դ
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);


private:
    cocos2d::Label* coinsLabel;
    cocos2d::Label* CD;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* bgLayer;
    cocos2d::TMXObjectGroup* objects_road;
    cocos2d::TMXObjectGroup* objects_position01;
    cocos2d::TMXObjectGroup* objects_position02;
    cocos2d::TMXObjectGroup* objects_coin;
    cocos2d::Vector<Node*> pointsVector;
    cocos2d::Vector<Node*> tower_position_jin;
    cocos2d::Vector<Node*> tower_position_yuan;
    void PlayScene::updateCountdown(float dt);
    int countdown;     // ����ʱ
    bool enemyAppeared; // ��¼�����Ƿ��Ѿ�����
    void initPointsVector(float offX);
    void initTowers_yuanVector(float off_position);
    void initTowers_jinVector(float off_position);
    int coins;//��Դ
    int HP_land;
};
