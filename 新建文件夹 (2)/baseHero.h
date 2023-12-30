#pragma once
#include "cocos2d.h"


USING_NS_CC;

class BaseCharacter : public cocos2d::Sprite {
public:
    
    BaseCharacter();
    virtual ~BaseCharacter();
    virtual bool init() override;
    CREATE_FUNC(BaseCharacter);

    // ��ʼ����ɫ����
    void initCharacterAttributes(float health, float attackPower, int blockCount, float range, float Cooldown);

    // ��������
    virtual void playAttackAnimation(){}
    void update(float dt);
    bool findTargetInRange(float range);
   
    // �ܻ�����
    void playHitAnimation();
    void takeDamage(float damage);
    void playDeathAnimationAndRemove();

    // ����
    //void activateSkill();
    //void onSkillBarFull();

    // ���úͻ�ȡ�ɵֵ����������
    //void setBlockCount(int count);
    //int getBlockCount() const;
    float getattackPower();

private:
    float attackRange;                // ������Χ
    float attackCooldown;             // ������ȴʱ��
    float lastAttackTime;             // �ϴι���ʱ��
    float maxHp;                      // ���Ѫ��
    float currHp;                     // ��ǰѪ��
    float skill;                      //������
    float attackPower;                // ������
    int blockCount;                   // �ɵֵ����������
    float CD;                         //��ɫ��������һ�οɷ��øý�ɫ��ʱ����
    float range;                      //��ɫ�Ĺ�����Χ
    int coin_sp;                      //���øý�ɫ����Ҫ����Դ
    Vec2 placementPosition;           // ��ɫ�ķ���λ��
    ProgressTimer* healthBar;         // Ѫ��
    ProgressTimer* skillBar;          // ������
    void initMouseListener();         // ��ʼ����������
    void onMouseDown(Event* event);   // ����¼�����
    
};