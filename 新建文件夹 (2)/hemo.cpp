#include "SimpleAudioEngine.h"
#include"hemo.h"
USING_NS_CC;

cocos2d::SpriteFrameCache* hemo::frameCache = nullptr;
bool hemo::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }

    // ���� heijiao ������ͼ��
    this->setTexture("hemo_front.png");
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(500, 10, 5, 500, 50);

    // ... ������������

    // �����������Ϊ�򶯻���Ҳ��������������

    return true;
}

void hemo::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 19; ++i) { // ���蹥��������8֡
        std::string frameName = StringUtils::format("hemo_attack_%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // ÿ֡���0.1��
    auto attackAnimate = Animate::create(attackAnimation);

    this->runAction(Sequence::create(attackAnimate, CallFunc::create([&]() {
        // ����������ɺ���߼�������У�
        }), nullptr));
}