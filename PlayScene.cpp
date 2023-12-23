#include "SimpleAudioEngine.h"
#include "PlayScene.h"
USING_NS_CC;
// ��ȡ��Ļ�Ŀɼ���С��ԭ������
// ���������ľ�̬����
Scene* PlayScene::createScene()
{
    return PlayScene::create();
}

// ��ʼ������
bool PlayScene::init() {
    // ��ȡ��Ļ�Ŀɼ���С��ԭ������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();
    HP_land = 100;

    // ���ز����õ�ͼ
    map = TMXTiledMap::create("map01.tmx");
    bgLayer = map->getLayer("background");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //����ʱ
    CD = cocos2d::Label::createWithTTF("3", "fonts/Marker Felt.ttf", 240);
    CD->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
    this->addChild(CD);
    //��Դ
    coinsLabel = cocos2d::Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 24);
    coinsLabel->setPosition(cocos2d::Vec2(970, 185));
    this->addChild(coinsLabel);
    
   

    coins = 0; // ��ʼ���������
    this->schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCoins), 1.0f); // ÿ�����һ�� updateCoins
    
    // ��ȡ���洢·���������
    objects_road = map->getObjectGroup("road");
    objects_position01 = map->getObjectGroup("towers_yuan");
    objects_position02=map->getObjectGroup("towers_jin");
    this->addChild(map, -1);

    // ��ʼ��·����
    initPointsVector((map->getContentSize().height - visibleSize.height) / 2);
    initTowers_yuanVector((map->getContentSize().height - visibleSize.height) / 2);
    
    // ��������ϵͳ
    auto particleSystem = ParticleFireworks::create();
    particleSystem->setPosition(pointsVector.at(0)->getPosition());
    this->addChild(particleSystem);
    particleSystem->setAutoRemoveOnFinish(true); // ���Ӳ�������Զ��ӳ������Ƴ�

    Vector<FiniteTimeAction*> moveAction;
    for (int i = 1; i < pointsVector.size(); ++i) {
        moveAction.pushBack(MoveTo::create(0.2f, pointsVector.at(i)->getPosition()));
    }

    // ���һ���ص���������·��������Ƴ�����
    auto removeEnemy = CallFunc::create([particleSystem]() {
        particleSystem->removeFromParent(); // �Ӹ��ڵ����Ƴ����˾���
        });
    moveAction.pushBack(removeEnemy);

    // ����ִ�ж�������
    auto seq = Sequence::create(moveAction);
    particleSystem->runAction(seq);



    // ��ʼ������ʱΪ3��
    countdown = 3;       
    enemyAppeared = false; // ��ʼ������δ����
    // ����һ����ʱ����ÿ1���ӵ���һ�� updateCountdown ����
    this->schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCountdown), 1.0f);

    

    auto towerIcon = Sprite::create("sheshou.png"); // ����ͼ��
    towerIcon->setPosition(Vec2(970, 100)); // ���ó�ʼλ��
    this->addChild(towerIcon);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [towerIcon](Touch* touch, Event* event) {
        if (towerIcon->getBoundingBox().containsPoint(touch->getLocation())) {
            // ��������ʼ������ͼ����ʱ
            return true; // �������¼�
        }
        return false;
    };

    touchListener->onTouchMoved = [this, towerIcon](Touch* touch, Event* event) {
        // ��������ͼ���λ��
        towerIcon->setPosition(towerIcon->getPosition() + touch->getDelta());
    };

    touchListener->onTouchEnded = [this, towerIcon](Touch* touch, Event* event) {
        bool isPlaced = false;
        for (auto& towerSpot : tower_position_yuan) {
            if (towerSpot->getBoundingBox().containsPoint(towerIcon->getPosition())) {
                auto tower = Sprite::create("sheshou.png");
                tower->setPosition(towerSpot->getPosition());
                this->addChild(tower);
                isPlaced = true;
                break;
            }
        }
        if (!isPlaced) {
            
            CCLOG("Tower was not placed");
        }
        towerIcon->setPosition(Vec2(970, 100));
    };
    

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, towerIcon);

    return true;
}

// ��ʼ��·��������
void PlayScene::initPointsVector(float off_position)
{
    auto objectsValueMap = objects_road->getObjects(); // ��ȡ����·�������

    // ����ÿ�����󲢻�ȡ�����꣬��ӵ�·����������
    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat()- off_position;
        auto pointNode = Node::create();
        pointNode->setPosition(Vec2(x, y)); // ���ýڵ�λ��
        pointsVector.pushBack(pointNode); // ���ڵ���ӵ�������
    }
}

void PlayScene::initTowers_yuanVector(float off_position)
{
    auto objectsValueMap = objects_position01->getObjects();

    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        auto towerSpot = Node::create();
        towerSpot->setPosition(Vec2(x + width / 2, y + height / 2)); // ʹ��λ���ڶ��������
        towerSpot->setContentSize(Size(width, height)); // ���ö���Ĵ�С
        tower_position_yuan.pushBack(towerSpot);
    }
}

void PlayScene::updateCoins(float dt) {
    coins++; // ÿ�ε���ʱ����һö���
    // ���±�ǩ���ı�����ʾ�µĽ������
    coinsLabel->setString("Coins: " + std::to_string(coins));
}

void PlayScene::updateCountdown(float dt) {
    if (countdown >= 0) {
        
        if (countdown == 0) {
            auto fadeOut = FadeOut::create(1.0f); // ����Ч��������1��
            auto removeCD = CallFunc::create([this]() {
                CD->removeFromParent(); // �Ӹ��ڵ����Ƴ�����ʱ��ǩ
                });
            CD->runAction(Sequence::create(fadeOut, removeCD, nullptr));


            // ���ž�������
            //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("warning_sound.mp3");
            
      
            
        }

        CD->setString(std::to_string(countdown));
        countdown--; // ÿ�μ���һ��
        
    }
   
    else if (!enemyAppeared) {
        // ������ʱ�����Ҿ�����δ����ʱ���������鲢��ʼ�����ƶ�
        auto enemy = Sprite::create("chongziguai.png");
        if (pointsVector.size() > 0) {
            enemy->setPosition(pointsVector.at(0)->getPosition());
        }
        this->addChild(enemy);

        // ������������ʹ������·���ƶ�
        Vector<FiniteTimeAction*> moveActions;
        for (int i = 1; i < pointsVector.size(); ++i) {
            moveActions.pushBack(MoveTo::create(1.0f, pointsVector.at(i)->getPosition()));
        }

        // ���һ���ص���������·��������Ƴ����˾���
        auto removeEnemy = CallFunc::create([enemy]() {
            enemy->removeFromParent(); // �Ӹ��ڵ����Ƴ����˾���
            });
        moveActions.pushBack(removeEnemy);

        // ����ִ�ж�������
        auto seq = Sequence::create(moveActions);
        enemy->runAction(seq);

        enemyAppeared = true; // ���þ����Ѿ�����
        this->unschedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCountdown));
    }

   

   
    
}
