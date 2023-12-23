#include "Arrow.h"

bool Arrow::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("arrow.png");  //��ʸ��ͼƬ���ǵ����
	addChild(sprite);
	return true;
}

void Arrow::shoot()
{
	//SoundManager::playArrowRelease();  //�����ӵ���Ч��
	runAction(Sequence::create(bulletAction,  //�ӵ�����
		CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
		NULL));
}

void Arrow::removeBullet()
{
	bool isMissed = true; //���ڱ��������Ƿ�û�л��й��
	auto instance = GameManager::getInstance();  //��ȡ��Ϸ��������ʵ����

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2, //����һ�����Σ������ӵ��������ĵ�ǰλ�úʹ�С����������ǻ��ڼ���λ�ú�����sprite�ĳߴ����ó��ġ�
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto monsterVector = instance->monsterVector;  //��ȡ�����б�:

	for (int j = 0; j < monsterVector.size(); j++)   //���������б����ÿ�������Ƿ񱻼����С�
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect) && monster->getAttackBySoldier())  //��������ľ��������Ƿ����ӵ��ľ��������ཻ�����Ƿ�����ײ�����У���
		{
			auto currHp = monster->getCurrHp();  //���ݼ����˺�ֵ��getMaxForce()���͹���Ļ���ֵ��getArmor()����������������ֵ��

			currHp = currHp - this->getMaxForce() + monster->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPercentage((currHp / monster->getMaxHp()) * 100);
			monster->getHurt();  //����������˵��߼���
			isMissed = false;  //�����ˣ�
			if (currHp == 0) {
				monster->death();  //�������������߼���
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