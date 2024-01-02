#include "yuanshichong.h"
#include "xiaobing.h"
#include "dabing.h"
#include "dog.h"
#include "SimpleAudioEngine.h"
#include "PlayScene01.h"
USING_NS_CC;


cocos2d::Scene* PlayScene01::createScene() {

    return  PlayScene01::create();
}

bool PlayScene01::init() {
    if (!baseMap::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    loadMap("map01.tmx",winSize);
    currentWave = 0;
    HP_land = 10;

    // ��ʼ��·����
    initPointsVector((map->getContentSize().height - visibleSize.height)); // ����·����ƫ����Ϊ10
    // ��ʼ��Զ�̺ͽ�ս������λ��
    initTowers_yuanVector((map->getContentSize().height - visibleSize.height)); // ����Զ��������λ��ƫ����Ϊ10
    initTowers_jinVector((map->getContentSize().height - visibleSize.height));  // �����ս������λ��ƫ����Ϊ10

    // ��ʼ�����˲�����Ϣ
    this->initEnemyWaves();
    
    // ���� update ������ʱ����
    
    this->schedule(CC_SCHEDULE_SELECTOR(baseMap::update), 0.1f);
    
    return true;
}

void PlayScene01::initEnemyWaves() {
    wavesInfo.push_back(WaveInfo("Dog", 3, 3.0f));                   // ��һ����3��Shiyuanchong��ÿ2��һ��
    wavesInfo.push_back(WaveInfo("Xiaobing", 2, 5.0f));             // �ڶ�����2��Xiaobing��ÿ1.5��һ��
    wavesInfo.push_back(WaveInfo("Shiyuanchong", 3, 2.0f));          // ��������3��Dog��ÿ1��һ��
}




