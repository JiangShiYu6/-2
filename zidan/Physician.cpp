#include "Physician.h"

bool Milk::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("arrow.png");  //��ʸ��ͼƬ���ǵ����
	addChild(sprite);
	return true;
}

void Milk::shoot()
{
	//SoundManager::playArrowRelease();  //�����ӵ���Ч��
	runAction(Sequence::create(bulletAction,  //�ӵ�����
		CallFuncN::create(CC_CALLBACK_0(Milk::removeBullet, this)),
		NULL));
}

void Milk::removeBullet()
{
	bool isMissed = true; //���ڱ��������Ƿ�û�л��и�Ա��
	auto instance = GameManager::getInstance();  //��ȡ��Ϸ��������ʵ����

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2, //����һ�����Σ������ӵ��������ĵ�ǰλ�úʹ�С����������ǻ��ڼ���λ�ú�����sprite�ĳߴ����ó��ġ�
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto handlerVector = instance->handlerVector;  //��ȡ��Ա�б�:

	for (int j = 0; j < handlerVector.size(); j++)   //������Ա�б����ÿ����Ա�Ƿ��̻��С�
	{
		auto handler = handlerVector.at(j);
		auto handlerRect = handler->baseSprite->getBoundingBox();

		if (handlerRect.intersectsRect(bulletRect) && handler->getAttackByHandler())  //������Ա�ľ��������Ƿ����ӵ��ľ��������ཻ�����Ƿ�����ײ�����У���
		{
			auto currHp = handler->getCurrHp();  //�����̵��˺�ֵ��getMaxForce()���͹���Ļ���ֵ��getArmor()����������������ֵ��

			currHp = currHp - this->getMaxForce() + handler->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			handler->setCurrHp(currHp);

			handler->getHpBar()->setPercentage((currHp / handler->getMaxHp()) * 100);
			handler->getHurt();  //����������˵��߼���
			isMissed = false;  //�����ˣ�
			if (currHp == 0) {
				handler->death();  //�����Ա�������߼���
			}
			break;
		}
	}
	if (isMissed) {

		sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
		//����û�л����κι������ı����spriteΪһ���µľ���֡�����磬���е���ļ���ͼ�񣩣�Ȼ�������������Ӹ��ڵ��Ƴ���  �ǵû�ͼƬ��

		sprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));             //����һ�����ж�����ʵ�ֵ���Ч�����Ƴ�����
	}
	else {
		this->removeFromParent();    //��������˹����ֱ�ӵ���this->removeFromParent()�����Ӹ��ڵ��Ƴ���
	}
}
