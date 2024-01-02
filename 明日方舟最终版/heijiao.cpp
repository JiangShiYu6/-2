#include "SimpleAudioEngine.h"
#include"heijiao.h"
USING_NS_CC; 



bool heijiao::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }
    wudi = false;
    jinoryuan = 0;
    if (level == 1)
        wudi_time = 7.5f;
    if (level == 2)
        wudi_time = 10.0f;
    if (level == 3)
        wudi_time = 12.5f;
    cost01 = 8;
    cost02 = 8;
    // ���� heijiao ������ͼ��
    this->setTexture("heijiao_front.png");
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(100, 10, 70, 3);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    if (!initManaBar("blue.png")) {
        return false;
    }
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 10; i++) {
        std::string frameName = StringUtils::format("heijiao_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 12; i++) {
       
        std::string frameName = StringUtils::format("HeiJiaoRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    createSkillButton();
    createUpButton();
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);
    return true;
}

void heijiao::playAttackAnimation() {
    
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {
        for (int i = 1; i <= 10; ++i) { //����������10֡
            std::string frameName = StringUtils::format("heijiao_attack_%02d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.3f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 1; i <= 12; ++i) { //����������12֡
            std::string frameName = StringUtils::format("HeiJiaoRight%d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.25f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }

    

}

void heijiao::castSkill() {
    // ��͸��Ч��
    wudi = true;
    auto fadeOut = FadeTo::create(0.5f, 128); // �𽥱�Ϊ��͸��������ʱ��Ϊ0.5��
    auto fadeIn = FadeTo::create(0.5f, 255); // �𽥻ָ���͸��������ʱ��Ϊ0.5��
    auto delay = DelayTime::create(7.5f); // ���ܳ���ʱ��

    // ������������
    auto sequence = Sequence::create(fadeOut, delay, fadeIn, nullptr);
    this->runAction(sequence);
    this->schedule(CC_SCHEDULE_SELECTOR(heijiao::endSkill), wudi_time);
    
}

void heijiao::endSkill(float dt) {
    wudi = false;
}

void heijiao::levelup()
{
    if(level<3)
    level +=1;  //��ɫ�ȼ�
    

    if (level == 2) {
        maxHp = 150.0f; // ��ʼѪ��Ϊ100
        currHp = maxHp; // ��ǰѪ���������Ѫ��
        attackPower = 15.0f; // ������Ϊ10
        attackRange = 80.0f; // ������ΧΪ50
        this->setTexture("HeiJiaoRight1.png");
        
        
    }
    if (level == 3) {
        maxHp = 200.0f; // ��ʼѪ��Ϊ100
        currHp = maxHp; // ��ǰѪ���������Ѫ��
        attackPower = 20.0f; // ������Ϊ10
        attackRange = 80.0f; // ������ΧΪ50
        this->setTexture("HeiJiaoRight1.png");
    }
    
}