#pragma once
#include "cocos2d.h"
#include"basemonster.h"
#include"baseHero.h"
#include "ui/CocosGUI.h"
struct WaveInfo {
    std::string monsterType; // ��������
    int count;               // ���ֹ��������
    float spawnInterval;     // �������ɵ�ʱ����

    WaveInfo(const std::string& type, int cnt, float interval)
        : monsterType(type), count(cnt), spawnInterval(interval) {}
};

class BaseMonster;
class baseMap : public cocos2d::Scene {
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    // ��ͼ���
    void loadMap(const std::string& mapFileName, cocos2d::Size winSize);
    

    // ��Դ
    void addCoins();
    void updateCoins(float dt);
    //void spendCoins(int amount);

    //·���͵�λ
    void initPointsVector(float offX);//��ʼ��·��
    void initTowers_yuanVector(float off_position);//��ʼ��Զ�̵�λ
    void initTowers_jinVector(float off_position);//��ʼ����ս��λ

    // ��������
    void initCharacterVector();
    void initCharacterIcons(); // ��ʼ����ɫͼ��
    void createCharacterAtPosition(const Vec2& position, std::string name);
    bool isValidPosition(const Vec2& position, const std::string& name);

    //void placeTower(const Vec2& position, const std::string& towerType);//����
    //void removeTower(const Vec2& position);//��������
    //void upgradeTower(const Vec2& position);//��������

    // ���˲���
    
    virtual void startEnemyWave(int waveNumber);
    virtual void initEnemyWaves();
    virtual void spawnMonster(std::string monsterType);
    void checkAndStartNextWave(); 
    void update(float dt);
    
    Vector<BaseMonster*> monsters;
    Vector<BaseMonster*> activeMonsters;
    Vector<BaseCharacter*> characters;

    //��������
    void removeActiveMonster(BaseMonster* monster);
    void removeCharacters(BaseCharacter* monster);
   
    
    // ��Ϸ״̬
    void checkGameOver();
    void onGameOver();
    void pauseGame(Ref* sender, ui::Widget::TouchEventType type);
    void resumeGame();
    void createPauseButton();
    
    void showExitModal();
    
    // UI����
    //void showTowerOptions(const Vec2& position);
    //void updateUI();
    CREATE_FUNC(baseMap);
    // �¼�����
    //void onEnemyKilled(Enemy* enemy);
    //void onTowerPlaced(Tower* tower);
    
    int HP_land; // ����ֵ
    void HP_off() {
        HP_land--;
    }
    int point;
    //void updateMonsters(float dt);
    cocos2d::Vector<Node*> pointsVector;//·��
    cocos2d::Vector<Node*> tower_position_jin;//��ս
    cocos2d::Vector<Node*> tower_position_yuan;//Զ��
protected:
    bool isPause;
    cocos2d::Label* hpLabel;//��ͼѪ��
    cocos2d::Label* Wave_num;//ʣ�ನ����
    bool isWaveInProgress;
    int coins; // ��Դ
    int currentWave;//���ﲨ��
    std::vector<WaveInfo> wavesInfo;
    cocos2d::Label* coinsLabel;//��Դ��ǩ
    cocos2d::Label* CD;//����ʱ��ǩ
    cocos2d::TMXTiledMap* map;//��ͼ
    cocos2d::TMXLayer* bgLayer;//��ͼ����
    cocos2d::TMXObjectGroup* objects_road;//�����ƶ�·��
    cocos2d::TMXObjectGroup* objects_position01;//Զ�̷��õ�λ
    cocos2d::TMXObjectGroup* objects_position02;//��ս���õ�λ
    cocos2d::TMXObjectGroup* objects_coin;//
    Vec2 originalPosition;
    
   
    
   
};

