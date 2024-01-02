#pragma once
#include "cocos2d.h"
#include "baseMap.h"
USING_NS_CC;

class BaseMonster :public Sprite {
public:
	// ʹ�ù��캯�����г�ʼ��
	BaseMonster()
		: max_Hp(0), cur_Hp(0), range(0), force(0), defence(0),isAttacking(false), isMoving(false), currentPathIndex(0){}

	virtual ~BaseMonster() {} // ������������
	virtual bool init() ;
	void initMonsterAttributes(float m_Hp, float c_Hp, float R, float F, float D, float S,float C)
	{
		this->max_Hp = m_Hp;
		this->cur_Hp = c_Hp;
		this->range = R;
		this->force = F;
		this->defence = D;
		this->speed = S;
		this->attackCooldown = C;
		this->isAttacking = false;
		this->isMoving = false;
		this->isAttackAnimationPlaying = false;
		this->lastAttackTime = 0;
		this->currentPathIndex = 0;
	}
	
	//���˴���
	void takedamage(float damage);
	
	virtual void playMoveAnimation() {};
	virtual void playAttackAnimation() {};

	//�����ƶ�·��
	
	void setMovementPath(const cocos2d::Vector<cocos2d::Node*>& pointsVector) {
		for (auto& pointNode : pointsVector) {
			cocos2d::Vec2 point = pointNode->getPosition();
			movementPath.push_back(point);
		}
	}
	//����Ƿ񵽴��յ�
	bool isemptyofpath() {
		if (movementPath.empty())
			return true;
		else
			return false;
	}
	
	//�����ص����ؿ�Ѫ
	void reachDestination();
	//�����Χ�Ƿ����Ӣ��
	void checkNearbyHeroes();
	//������ز���
	float getForce() {
		return force;
	}
	float getSpeed() {
		return speed;
	}
	float gethp()const {
		return cur_Hp;
	}
	//�����Ƿ��ڽ���״̬
	void Attack() {
		isAttacking = true;
	}
	void StopAttak() {
		isAttacking = false;
	}

	//��������
	void disappear();
	//���ﶯ������
	void action(float dt);
	void update(float dt);
	CREATE_FUNC(BaseMonster);
protected:
	float lastAttackTime;
	float attackCooldown;
	float max_Hp;
	float cur_Hp;
	float range;
	float force;
	float defence;
	float speed;
	bool isAttacking;
	bool isMoving;
	bool isAttackAnimationPlaying;
	std::vector<cocos2d::Vec2> movementPath;
	
	int currentPathIndex;

};


