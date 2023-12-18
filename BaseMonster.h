#ifndef _BASE_MONSTER_H_
#define _BASE_MONSTER_H_

#include "cocos2d.h"

USING_NS_CC;
typedef enum {
	stateNone = 0, //��״̬
	stateWalkRight, //��������״̬
	stateWalkLeft, //������
	stateWalkUp, //������
	stateWalkDown, //������
	stateAttackLeft,  //���󹥻�
	stateAttackRight, //���ҹ���
	stateDeath,//����
	//stateFrozen  //����
}MonsterState;

typedef enum {
	SourceLithina,  //Դʯ��
	Soldier,  //С��
	Dog,  //��
	ShiledMan,  //�ܱ�
}MonsterName;

class BaseMonster : public Sprite
{
public:
	BaseMonster();
	~BaseMonster();
	virtual bool init() override;
	CREATE_FUNC(BaseMonster);
	Sprite* baseSprite;
	//ðѪ���ܻ���Ч
	virtual void death();
	//��
	//virtual void explosion();  
	CC_SYNTHESIZE(std::vector<Point>, pointsVector, PointsVector);  //·����
	CC_SYNTHESIZE(bool, attackBySoldier, AttackBySoldier);  //�Ƿ񱻸�Ա��ս����
	CC_SYNTHESIZE(MonsterName, monsterType, MonsterType);  //��������
	CC_SYNTHESIZE(bool, attackByHandler, AttackByHandler);  //�Ƿ񱻸�ԱԶ�̹���  
	CC_SYNTHESIZE(bool, isAttacking, IsAttacking);  //�Ƿ����ڹ���
	CC_SYNTHESIZE(float, runSpeed, RunSpeed);  //�ƶ��ٶ�
	CC_SYNTHESIZE(float, maxHp, MaxHp);  //���Ѫ��
	CC_SYNTHESIZE(float, currHp, CurrHp);  //��ǰѪ��
	CC_SYNTHESIZE(float, force, Force);  //������
	CC_SYNTHESIZE(float, armor, Armor);  //������
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);  //Ѫ���ٷֱ�
	//CC_SYNTHESIZE(MonsterState, state, State);  
	//CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);  //������
	virtual void stopWalking();  //ֹͣ�ƶ�
	virtual void restartWalking();  //���¿�ʼ�ƶ�
	//virtual void slowRunSpeed(float dt, float dis);  //�����ٶ�
	Point getNextPoint();  //��ȡ��һ��·��
	virtual void frozen();  //����
	virtual void refrozen(float dt);  //�ⶳ
private:

protected:
	void setMonsterZorder(int yOrder);  //���ù���z��˳��
	int pointCounter;  //·���������
	Sprite* hpBgSprite;  //����ֵ��������
	Point currPoint();  //��ǰ��
	Point nextPoint();  //��һ����
	Point tempNextPoint;  //��ʱ����һ����
	void runNextPoint();  //�ƶ�����һ����
	void createAndSetHpBar();  //����������������

	bool onTouchBegan(Touch* touch, Event* event);  //�����������¼���ʼ
	void onTouchEnded(Touch* touch, Event* event);  //�����������¼�����

	virtual void update(float dt);
	//CC_SYNTHESIZE(bool, isSlowed, IsSlowed);

	Sprite* blood;                                       //? ? ? ? ? ? 
	//MonsterState tempState;
	//MonsterState lastState;
	void stopMonsterAnimation();  //ֹ֮ͣǰ����
	//Sprite* ice;
	//void showInfo();  //��ʾ������Ϣ
	void setListener();  //������
};
#endif