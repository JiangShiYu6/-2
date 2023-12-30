#include "dabing.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

bool Db::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseMonster::init()) {
        return false;
    }

    // ���� dabing ������ͼ��
    this->setTexture("zhongzhuang.png");

    // ���� dabing �ĳ�ʼ����
    this->initMonsterAttributes(250,250,200,30,4,1,3);
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 5; ++i) { // �ƶ���5֡����
        std::string frameName = StringUtils::format("zhongzhuang-move-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 100, 100)), frameName);
    }
    for (int i = 1; i <= 7; ++i) { // ����������7֡
        std::string frameName = StringUtils::format("zhongzhuang-attack-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 100, 100)), frameName);
    }
    // ... ������������

    // �����������Ϊ�򶯻���Ҳ��������������

    return true;
}
void Db::playMoveAnimation() {
    // ����һ������֡��
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) {
        std::string frameName = StringUtils::format("zhongzhuang-move-%02d.png", i);
        
        auto frame = Db::frameCache->getSpriteFrameByName(frameName);
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

void Db::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 7; ++i) { // ���蹥��������8֡
        std::string frameName = StringUtils::format("zhongzhuang-attack-%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // ÿ֡���0.1��
    auto attackAnimate = Animate::create(attackAnimation);

    this->runAction(RepeatForever::create(attackAnimate));
}