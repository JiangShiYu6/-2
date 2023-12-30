#include"yuanshichong.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;



bool Shiyuanchong::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseMonster::init()) {
        return false;
    }

    // ���� dabing ������ͼ��
    this->setTexture("yuanshichong.png");
    
    // ���� dabing �ĳ�ʼ����
    this->initMonsterAttributes(100, 100, 100, 10, 1,1,2);
   
    // ... ������������
   
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 1; ++i) { // ������6֡����
        std::string frameName = StringUtils::format("yuanshichong_move_01.png");
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 40, 35)), frameName);
    }
    for (int i = 1; i <= 1; ++i) { // ���蹥��������8֡
        std::string frameName = StringUtils::format("yuanshichong_attack_01.png");
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 40, 35)), frameName);
    }
    // �����������Ϊ�򶯻���Ҳ��������������

    return true;
}

void Shiyuanchong::playMoveAnimation() {
    // ����һ������֡����
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 1; ++i) {
        std::string frameName = StringUtils::format("yuanshichong_move_%d.png", i);
        auto frame = Shiyuanchong::frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }
    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f);
    auto animate = Animate::create(animation);

    // ���ж���
    this->runAction(RepeatForever::create(animate));
    
}

void Shiyuanchong::playAttackAnimation() {
    // ������������֡����
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 1; ++i) {
        std::string frameName = StringUtils::format("yuanshichong_attack_%d.png", i);
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