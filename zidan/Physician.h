#ifndef _ARROW_H_
#define _ARROW_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Milk : public Bullet  //��Ѫ��Զ�̵ĺ�Ĭר�ã�Ŀǰ�ȶ�����һ������ʱ�����������ӵ�
{
public:
	virtual bool init();
	CREATE_FUNC(Milk);  //��
	void shoot();  //�ӵ�����
	void removeBullet();  //�ӵ��Ƴ�
};

#endif