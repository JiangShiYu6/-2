#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class BaseCharacter : public cocos2d::Sprite {

public:
    
    BaseCharacter();
    virtual ~BaseCharacter();
    bool init() override;
    
    // ��ʼ����ɫ����
    void initCharacterAttributes(float health, float attackPower,float range, float Cooldown);

    // ��������
    virtual void playAttackAnimation() = 0;
    void update(float dt);
    virtual void findTargetInRange();
   
    // �ܻ�����
    void playHitAnimation();
    void takeDamage(float damage);
    void playDeathAnimationAndRemove();

    
    float getattackPower()const;
    float getCurrentMana() const {
        return currentMana;
    }
    void setCurrentMana(float mana) {
        currentMana = mana;
    }
    float gethp() {
        return currHp;
    }
    // ��ɫ�������
    bool initManaBar(const std::string& manaBarImage);  // ��ʼ������
    void updateMana(float dt);                          // ��������ֵ
    void createSkillButton();                         //���ɼ���ͼ��
    void showSkillButton();                            //��ʾ����ͼ��
    void onManaBarClicked();                          // ��������¼�����
    virtual void castSkill() = 0;                     // �ͷż���
    void onSkillButtonClicked(Ref* sender, ui::Widget::TouchEventType type);
    void startSkillCooldown(float dt);                  //������ȴ
    //��ɫ�������
    virtual void levelup() {};        //��������
    void createUpButton();
    void onlevelupClicked(Ref* sender, ui::Widget::TouchEventType type);         // ��������¼�����
    int JorY() const{
        return jinoryuan;
     }
protected:
    ProgressTimer* manaBar;            // ������
    ui::Button* skillButton;          // ���ܰ�ť
    int jinoryuan;                   //Զ�̻��ǽ�ս
    ui::Button* upButton;          // ������ť
    int level = 1;  //��ɫ�ȼ�����ʼΪһ��
    int cost01;  //���÷���
    int cost02;  //��������
    float currentMana;                // ��ǰ����ֵ
    float maxMana;             // �������ֵ
    float attackRange;                // ������Χ
    float attackCooldown;             // ������ȴʱ��
    float lastAttackTime;             // �ϴι���ʱ��
    float maxHp;                      // ���Ѫ��
    float currHp;                     // ��ǰѪ��
    float skill;                      //������
    float attackPower;                // ������
    float CD;                         //��ɫ��������һ�οɷ��øý�ɫ��ʱ����
    int coin_sp;                      //���øý�ɫ����Ҫ����Դ
    Vec2 placementPosition;           // ��ɫ�ķ���λ��
    ProgressTimer* healthBar;         // Ѫ��
    ProgressTimer* skillBar;          // ������
    ui::Button* deleteButton;
    void onDeleteButtonClicked(Ref* sender, ui::Widget::TouchEventType type);
    bool wudi;
    bool isAttacking;
    bool isPlaying;
};