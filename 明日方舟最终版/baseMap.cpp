#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include "yuanshichong.h"
#include "xiaobing.h"
#include "dabing.h"
#include "dog.h"
#include"heijiao.h"
#include"amiya.h"
#include"lapu.h"
#include"andeqieer.h"
#include "ui/CocosGUI.h"
#include"MapSelect.h"
USING_NS_CC;

Scene* baseMap::createScene()
{
    return baseMap::create();
}

bool baseMap::init() {
    if (!Scene::init()) {
        return false;
    }

    // ������Ϸ��ʼ״̬
    isPause = false;
    isWaveInProgress = false;
    point = 0;     //��ʼ���Ծַ���
    coins = 0;     // ��ʼ�������
    addCoins();    // ��ӽ�ұ�ǩ������
    // ��������ʼ��Ѫ���Ͳ�����ǩ
    hpLabel = Label::createWithTTF("100", "fonts/Marker Felt.ttf", 24);
    hpLabel->setPosition(Vec2(600.0f, 710.0f));
    Wave_num = Label::createWithTTF("3/3", "fonts/Marker Felt.ttf", 24);
    Wave_num->setPosition(Vec2(460.0f, 710.0f));
    this->addChild(hpLabel, 1);
    this->addChild(Wave_num, 1);
    createPauseButton();
    //��ʼ���ܽ�ɫ
    this->initCharacterIcons();
    
    // ֹͣ��ǰ���ڲ��ŵı�������
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    // �����³����ı�������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/playscene.mp3", true);



    return true;
}

// ��ͼ���
// ��ͼ���
void baseMap::loadMap(const std::string& mapFileName,cocos2d::Size winSize) {
    
    

    // ���ص�ͼ�ļ�
    map = TMXTiledMap::create(mapFileName);
    

    // ��ȡ���洢·���������
    objects_road = map->getObjectGroup("road");
    objects_position01 = map->getObjectGroup("towers_yuan");
    objects_position02 = map->getObjectGroup("towers_jin");

    // ���������Ƿ����
   

    // ���ز����ñ�����
    bgLayer = map->getLayer("background");
    
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));

    this->addChild(map, -1); // ��ӵ�ͼ����ǰ����
}

// ��Դ
void baseMap::updateCoins(float dt) {
    // ÿ�ε���ʱ����һö���
    coins++;
    // ���±�ǩ���ı�����ʾ�µĽ������
    coinsLabel->setString("Coins: " + std::to_string(coins));
}

void baseMap::addCoins() {
    coins = 0;
    coinsLabel = cocos2d::Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 24);
    coinsLabel->setPosition(cocos2d::Vec2(970, 185));
    this->addChild(coinsLabel);
    this->schedule(CC_SCHEDULE_SELECTOR(baseMap::updateCoins), 1.0f); // ÿ�����һ�� updateCoins
}
bool baseMap::comsuption(int cum){
    if (coins - cum < 0)
        return false;
    else {
        coins -= cum;
        return true;
    }
}
//·���͵�λ
//��ʼ��·��
void baseMap::initPointsVector(float off_position) {
   
    auto objectsValueMap = objects_road->getObjects(); // ��ȡ����·�������

    // ����ÿ�����󲢻�ȡ�����꣬��ӵ�·����������
    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        auto pointNode = Node::create();
        pointNode->setPosition(Vec2(x, y)); // ���ýڵ�λ��
        pointsVector.pushBack(pointNode); // ���ڵ���ӵ�������

    }
}

//��ʼ��Զ�̵�λ
void baseMap::initTowers_yuanVector(float off_position) {
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

//��ʼ����ս��λ
void baseMap::initTowers_jinVector(float off_position)
{
    auto objectsValueMap = objects_position02->getObjects();

    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        auto towerSpot = Node::create();
        towerSpot->setPosition(Vec2(x + width / 2, y + height / 2)); // ʹ��λ���ڶ��������
        towerSpot->setContentSize(Size(width, height)); // ���ö���Ĵ�С
        tower_position_jin.pushBack(towerSpot);
    }
}

void baseMap::removeActiveMonster(BaseMonster* monster) {
    if (!activeMonsters.empty()) {
        auto iter = std::find(activeMonsters.begin(), activeMonsters.end(), monster);
        if (iter != activeMonsters.end()) {
            activeMonsters.erase(iter);

            if (activeMonsters.empty() && isWaveInProgress) {
                // ��ǰ���ε����й��ﶼ���Ƴ�
                currentWave++;
                isWaveInProgress = false;
            }
        }
    }
}

void baseMap::removeCharacters(BaseCharacter* monster) {
    if (!characters.empty()) {
        auto iter = std::find(characters.begin(), characters.end(), monster);
        if (iter != characters.end()) {
            characters.erase(iter);

        }
    }
}

void baseMap::initEnemyWaves() {
    
}

void baseMap::startEnemyWave(int waveNumber) {
    if (waveNumber >= wavesInfo.size()) {
        return; // ���γ�����Χ�����в������ڽ���
    }

    isWaveInProgress = true;
    
    this->unschedule("spawnMonster");
    // ��ʱ������һ���Ĺ���
    auto& wave = wavesInfo[waveNumber];
    this->schedule([this, waveNumber](float dt) {
        auto& wave = wavesInfo[waveNumber];
        spawnMonster(wave.monsterType);
        }, wave.spawnInterval, wave.count - 1, 0, "spawnMonster");
    

}

void baseMap::spawnMonster(std::string monsterType) {
   
    BaseMonster* monster = nullptr;

    if (monsterType == "Shiyuanchong") {
        monster = Shiyuanchong::create(); // ����Xiaobing
       
    }
    else if (monsterType == "Xiaobing") {
        monster = Xiaobing::create(); // ����Xiaobing
       
    }
    else if (monsterType == "Dog") {
        monster = Dog::create(); // ����Dog
       
    }
    else if (monsterType == "Dabing") {
        monster = Db::create();
    }
    if (monster) {
        
        monster->setMovementPath(pointsVector);
        monster->setPosition(pointsVector.at(0)->getPosition());
        this->addChild(monster, -1);
        activeMonsters.pushBack(monster);
    }

}

void baseMap::checkAndStartNextWave() {
    if (!isWaveInProgress && currentWave < wavesInfo.size()) {
        startEnemyWave(currentWave);
    }
}

void baseMap::update(float dt) {
    checkGameOver();
    hpLabel->setString(std::to_string(10*HP_land));
    
    // ��鵱ǰ���εĹ����Ƿ��ѱ�����
    checkAndStartNextWave();

    Wave_num->setString(std::to_string(currentWave+1) + "/3");
}

//��ʼ����ɫͼ�꣬���а������ý�ɫ�߼�
void baseMap::initCharacterIcons() {
    // ������һ����ɫͼ������amiya_attack_01.png
    std::vector<std::string> characterIcons = { "ami_point.jpg","lapu_point.jpg","heijiao_point.jpg","qieer_point.jpg"};
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    std::vector<Vec2>originalPosition;
    // ������ɫͼ������
    for (int i = 0; i < characterIcons.size(); ++i) {
        auto icon = Sprite::create(characterIcons[i]);
        auto name = characterIcons[i];
        originalPosition.push_back( Vec2(970 - 74 * i, 100));
        icon->setPosition(Vec2(970 - 74 * i, 100));
        this->addChild(icon);
        
        // Ϊÿ��ͼ����Ӵ����¼�������
        auto listener = EventListenerTouchOneByOne::create();

        listener->setSwallowTouches(true);

        listener->onTouchBegan = [icon, this](Touch* touch, Event* event) -> bool {
            if (isPause) {
                return false;
            }
            if (icon->getBoundingBox().containsPoint(touch->getLocation())) {
                icon->setOpacity(150); // ���ʱ���͸��
                return true;
            }
            return false;

        };

        listener->onTouchMoved = [icon, this](Touch* touch, Event* event) {
            if (!isPause)
                icon->setPosition(icon->getPosition() + touch->getDelta());
        };

        listener->onTouchEnded = [this, icon, name, originalPosition, i](Touch* touch, Event* event) {
            if (!isPause) {
                float minDistance = std::numeric_limits<float>::max();
                Node* nearestSpot = nullptr;
                icon->setOpacity(225);
                // ���ݽ�ɫ����ѡ����ʵķ��õ�λ����
                const auto& towerSpots = (name == "ami_point.jpg" || name == "qieer_point.jpg") ? tower_position_yuan : tower_position_jin;

                // Ѱ������ķ��õ�
                for (auto& towerSpot : towerSpots) {
                    float distance = icon->getPosition().distance(towerSpot->getPosition());
                    if (distance < minDistance) {
                        minDistance = distance;
                        nearestSpot = towerSpot;
                    }
                }

                // ����Ƿ�ӽ��κκϷ����õ�
                if (nearestSpot && minDistance < 70) { 
                    icon->runAction(MoveTo::create(0.5, originalPosition[i]));
                    createCharacterAtPosition(nearestSpot->getPosition(), name);
                }
                else {
                    icon->runAction(MoveTo::create(0.5, originalPosition[i]));
                }
            }
        };


        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, icon);

    }
}

//�ڷ���λ�ô�����ɫ
void baseMap::createCharacterAtPosition(const Vec2& position, std::string name) {
    // �����λ�ô�����ɫ
    if (name == "ami_point.jpg"&& comsuption(8)) {
        auto character = amiya::create(); // ����BaseCharacter��һ��create����
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    else if (name == "heijiao_point.jpg"&& comsuption(8)) {
        auto character = heijiao::create(); // ����BaseCharacter��һ��create����
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
   
    else if (name == "lapu_point.jpg"&& comsuption(8)) {
        auto character = lapu::create(); // ����BaseCharacter��һ��create����
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    else if (name == "qieer_point.jpg"&& comsuption(8)) {
        auto character = andeqieer::create(); // ����BaseCharacter��һ��create����
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
   
}

//��Ϸ�����ж�
void baseMap::checkGameOver() {

    if (HP_land <= 0) {
        onGameOver();
    }
    else if (currentWave == 3 && activeMonsters.empty() && HP_land > 0)
    {
        onGameOver();
    }
    else
        return;
}

//��Ϸ��������
void baseMap::onGameOver() {


   
    
    
    if (HP_land >= 10) {
        point = 3;
    }
    else if (HP_land < 10 && HP_land >= 7) {
        point = 2;
    }
    else if (HP_land < 7 && HP_land >0) {
        point = 1;
    }

    showExitModal();

}

// ��ͣ��Ϸ
void baseMap::pauseGame(Ref* sender, ui::Widget::TouchEventType type) {
    
    if (type == ui::Widget::TouchEventType::ENDED) {
        // �����Ϸ�Ƿ��Ѿ���ͣ
        if (!Director::getInstance()->isPaused()) {
            Director::getInstance()->pause();
            isPause = true;
            auto winSize = Director::getInstance()->getVisibleSize();
            auto modalLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);
            modalLayer->setName("ModalLayer");

            // ʹģ̬��������д����¼�����ֹ������Ľ���
            modalLayer->setTouchEnabled(true);
            modalLayer->setSwallowsTouches(true);

            auto resumeLabel = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 24);
            resumeLabel->setPosition(modalLayer->getContentSize() / 2);

            // Ϊ��ǩ��Ӵ����¼�������
            auto resumeListener = EventListenerTouchOneByOne::create();
            resumeListener->onTouchBegan = [this, resumeLabel](Touch* touch, Event* event) {
                if (resumeLabel->getBoundingBox().containsPoint(touch->getLocation())) {
                    this->resumeGame();
                    return true;
                }
                return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(resumeListener, resumeLabel);

            modalLayer->addChild(resumeLabel);

           

            auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
            exitLabel->setPosition(Vec2(490, 340)); // ���ú��ʵ�λ��

            auto exitlistener = EventListenerTouchOneByOne::create();
            exitlistener->onTouchBegan = [this, exitLabel](Touch* touch, Event* event) {
                if (exitLabel->getBoundingBox().containsPoint(touch->getLocation())) {
                    this->showExitModal();
                    return true;
                }
                return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(exitlistener, exitLabel);
            
            modalLayer->addChild(exitLabel);

            this->addChild(modalLayer, INT_MAX);

            // ������ͣ��ť
            auto pauseButton = dynamic_cast<ui::Button*>(this->getChildByName("PauseButton"));
            if (pauseButton) {
                pauseButton->setTouchEnabled(false);
                pauseButton->loadTextures("Pause_After.png", "Pause_After.png");
            }
            
        }
    }
}

// �ָ���Ϸ
void baseMap::resumeGame() {
    Director::getInstance()->resume();
    isPause = false;
    // �Ƴ�ģ̬��
    this->removeChildByName("ModalLayer");
    // ����������ͣ��ť
    auto pauseButton = dynamic_cast<ui::Button*>(this->getChildByName("PauseButton"));
    if (pauseButton) {
        pauseButton->setTouchEnabled(true);
        pauseButton->loadTextures("Stop_Button.png", "Stop_Button.png");
    }
}

//������ͣ��ť
void baseMap::createPauseButton() {
    auto pauseButton = ui::Button::create("Stop_Button.png", "Stop_Button.png");
    pauseButton->setPosition(Vec2(965, 690));
    pauseButton->addTouchEventListener(CC_CALLBACK_2(baseMap::pauseGame, this));
    pauseButton->setName("PauseButton"); // ���ð�ť������
    this->addChild(pauseButton, 1);
}

// ��ʾ�˳�ģ̬��
void baseMap::showExitModal() {
    this->removeChildByName("ModalLayer");
    auto Star1 = Sprite::create("star.png");
    Star1->setPosition(Vec2(150, 170));
    auto Star2 = Sprite::create("star.png");
    Star2->setPosition(Vec2(250, 170));
    auto Star3 = Sprite::create("star.png");
    Star3->setPosition(Vec2(350, 170));
    
    auto winSize = Director::getInstance()->getVisibleSize();
    auto modalLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);
    modalLayer->setName("ExitModalLayer");
    auto backgroundSprite = Sprite::create("over.jpg"); 
    backgroundSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    modalLayer->addChild(backgroundSprite);
    auto HERO = Sprite::create(); 
    HERO->setPosition(Vec2(18*winSize.width / 25, 9*winSize.height / 20)); 
    modalLayer->addChild(HERO);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(MapSelect::createScene());

        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, modalLayer);
    this->addChild(modalLayer, INT_MAX);

    switch (point) {
    case 3:
        HERO->setTexture("JJ_1.png");
        modalLayer->addChild(Star1);
        modalLayer->addChild(Star2);
        modalLayer->addChild(Star3);
        UserDefault::getInstance()->setIntegerForKey("currentLevel", 2);
        UserDefault::getInstance()->flush();

        break;
    case 2:
        HERO->setTexture("LP_1.png");
        modalLayer->addChild(Star1);
        modalLayer->addChild(Star2);
        UserDefault::getInstance()->setIntegerForKey("currentLevel", 2);
        UserDefault::getInstance()->flush();

    case 1:
        HERO->setTexture("AD_1.png");
        modalLayer->addChild(Star1);
        UserDefault::getInstance()->setIntegerForKey("currentLevel", 2);
        UserDefault::getInstance()->flush();

        break;
    case 0:
        HERO->setTexture("HJ_1.png");
        
        break;
    default:
        return;
    }
        
}