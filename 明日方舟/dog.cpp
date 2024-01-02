#include"dog.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;



bool Dog::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseMonster::init()) {
        return false;
    }
    
    // ���� dabing ������ͼ��
    this->setTexture("dog.png");

    // ���� dabing �ĳ�ʼ����
    this->initMonsterAttributes(120, 120, 50, 10, 2,2,30.0);
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 5; ++i) { // ������6֡����
        std::string frameName = StringUtils::format("dog_move_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    for (int i = 1; i <= 8; ++i) { // ���蹥��������8֡
        std::string frameName = StringUtils::format("dog_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    // ... ������������

    // �����������Ϊ�򶯻���Ҳ��������������
   
    return true; 
}
void Dog::playMoveAnimation() {
    // ����һ������֡����
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) {
        std::string frameName = StringUtils::format("dog_move_%02d.png", i);
        auto frame = frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    auto animate = Animate::create(animation);

    // ���ж���
    this->runAction(RepeatForever::create(animate));
}

void Dog::playAttackAnimation() {
    // ������������֡����
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 8; ++i) {
        std::string frameName = StringUtils::format("dog_attack_%02d.png", i);
        
        auto frame = frameCache->getSpriteFrameByName(frameName);
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