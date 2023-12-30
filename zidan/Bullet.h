#ifndef _BULLET_H_
#define _BULLET_H_

//#include "SoundManager.h"
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class Bullet : public Sprite
{
public:
	Bullet();  //���캯��
	~Bullet();  //��������
	virtual bool init();  //��
	CREATE_FUNC(Bullet);  //��������ľ�̬�����������Ϳ�����Bullet:create()����������

protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);  //�ӵ��˺�
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//�ӵ���Χ
	CC_SYNTHESIZE(int, bulletType, BulletType);  //�ӵ�����
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);  //�ӵ�����
	Sprite* sprite;  //��������
	virtual void shoot() {};  //����
	virtual void removeBullet() {};  //�ӵ����Ƴ�
};

#endif