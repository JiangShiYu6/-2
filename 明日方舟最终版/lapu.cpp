#include "SimpleAudioEngine.h"
#include"lapu.h"
USING_NS_CC;



bool lapu::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }
    cost01 = 8;
    cost02 = 8;
    jinoryuan = 0;
    // ���� heijiao ������ͼ��
    this->setTexture("lapu_front.png");
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(200, 30, 60, 1.4);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    if (!initManaBar("blue.png")) {
        return false;
    }
    // ... ������������
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 7; i++) {
        std::string frameName = StringUtils::format("lapu_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 13; i++) {
        std::string frameName = StringUtils::format(" LaDogRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 4; ++i) {  //����ͼƬ
        std::string frameName = StringUtils::format("lapu_skill%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    // �����������Ϊ�򶯻���Ҳ��������������
    createSkillButton();
    createUpButton();
    return true;
}

void lapu::playAttackAnimation() {
    
    if (level == 1) {
        Vector<SpriteFrame*> attackFrames;
        for (int i = 1; i <= 7; ++i) { // ���蹥��������8֡
            std::string frameName = StringUtils::format("lapu_attack_%02d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.2f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);
        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        Vector<SpriteFrame*> attackFrames;
        for (int i = 1; i <= 13; ++i) { // ���蹥��������8֡
            std::string frameName = StringUtils::format("LaDogRight%d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);
        this->runAction(RepeatForever::create(attackAnimate));
    }
    
}

void lapu::endSkill(float dt) {
    attackRange = attackRange - 10; // ��������Χ����Ϊ����ֵ
    // ������Ҫ�ڼ��ܽ���ʱ���õĴ���
}

void lapu::swordAnimation(BaseMonster* target)
{
    if (target == nullptr) {
        return; // ���Ŀ�겻���ڣ���ֱ�ӷ���
    }

    // ��ȡĿ���λ��
    Vec2 targetPosition = target->getPosition();

    // ���ر�ը������֡
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; ++i) {  //����ͼƬ
        std::string frameName = StringUtils::format("lapu_skill%d.png", i);
        auto frame = frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);  // ���ҵ���֡��ӵ�����֡������
        }
    }
    // ������������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f); // ����ÿ֡�ļ����0.1��
    auto animate = Animate::create(animation);

    // ����һ�����������Ŷ���
    auto explosionSprite = Sprite::createWithSpriteFrame(frames.front());
    explosionSprite->setPosition(targetPosition);
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    currentScene->addChild(explosionSprite, INT_MAX);

    // ���Ŷ��������ڲ�����Ϻ��Ƴ�����
    auto removeSprite = CallFunc::create([explosionSprite]() {
        explosionSprite->removeFromParent();
        });
    explosionSprite->runAction(Sequence::create(animate, removeSprite, nullptr));
}
void lapu::castSkill()  //�ͷż���
{
        // ��ȡ��ǰ����
        auto currentScene = dynamic_cast<baseMap*>(this->getScene());
        if (currentScene) {
            attackRange = attackRange + 10.0f;
            for (auto monster : currentScene->activeMonsters) {
                // �������Ƿ��ڹ�����Χ��,���ҵ��˹�����ȴʱ�䣡
                if (isTargetInRange_mon(monster, attackRange)) {
                    // ����ǣ��򹥻����ﲢ���� true
                    swordAnimation(monster);
                    break;
                }
            }
            this->schedule(CC_SCHEDULE_SELECTOR(lapu::endSkill), 5.0f);
        }
}
bool lapu::isTargetInRange_mon(BaseMonster* target, float range) {
    // ���㵱ǰ��ɫ��Ŀ��֮��ľ���
    float distance = this->getPosition().distance(target->getPosition());
    // �������С�ڻ���ڹ�����Χ����Ŀ���ڷ�Χ��
    return distance <= range;
}
void lapu::levelup() {
    if (level < 3)
        level += 1;  //��ɫ�ȼ�

    if (level == 2) {

        maxHp = 250;
        currHp = 250;
        attackRange = 75.0f; 
        setTexture("LaDogRight1.png");

    }
    if (level == 3) {

        maxHp = 300;
        currHp = 300;
        attackPower = 35.0f; 
        setTexture("LaDogRight1.png");

    }
}