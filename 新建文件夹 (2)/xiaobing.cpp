#include "xiaobing.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


bool Xiaobing::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseMonster::init()) {
        return false;
    }

    // ���� dabing ������ͼ��
    this->setTexture("shibing.png");
    // ���� dabing �ĳ�ʼ����
    this->initMonsterAttributes(150, 150, 200, 50, 2,1,2);
    
    // ... ������������
     // ���� xiaobing ʵ��
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 7; ++i) { // ������6֡����
        std::string frameName = StringUtils::format("shibing-move-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    for (int i = 1; i <= 10; ++i) { // ���蹥��������8֡
        std::string frameName = StringUtils::format("shibing-attack-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    // �����������Ϊ�򶯻���Ҳ��������������

    return true;
}

void Xiaobing::playMoveAnimation() {
    // ����һ������֡����
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 7; ++i) {
        std::string frameName = StringUtils::format("shibing-move-%02d.png", i);
        
        auto frame = Xiaobing::frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames,0.1f);
    auto animate = Animate::create(animation);

    // ���ж���
    this->runAction(RepeatForever::create(animate));
}

void Xiaobing::playAttackAnimation() {
    // ������������֡����
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 10; ++i) {
        std::string frameName = StringUtils::format("shibing-attack-%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    // ������������
    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f);
    auto attackAnimate = Animate::create(attackAnimation);

    // ���й�������
    this->runAction(RepeatForever::create(attackAnimate));
}