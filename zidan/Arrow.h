#ifndef _ARROW_H_
#define _ARROW_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Arrow : public Bullet  //��ʸ��Զ�̵İ����ж�ר�ã�Ŀǰ�ȶ�����һ������ʱ�����������ӵ�
{
public:
	virtual bool init();
	CREATE_FUNC(Arrow);  //��
	void shoot();  //�ӵ�����
	void removeBullet();  //�ӵ��Ƴ�
};

#endif