#include "SimpleAudioEngine.h"
#include"andeqieer.h"
USING_NS_CC;

bool andeqieer::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }
    jinoryuan = 1;
    cost01 = 8;
    cost02 = 8;
    // ���� heijiao ������ͼ��
    this->setTexture("andeqieer_attack_01.png");
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(50, 30, 200, 1.6f);
    if (!initManaBar("blue.png")) {
        return false;
    }
    // ... ������������
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <=5; i++) {
        std::string frameName = StringUtils::format("andeqieer_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 8; i++) {
        std::string frameName = StringUtils::format("AnDeRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 7; ++i) {  
        std::string frameName = StringUtils::format("boom%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 400, 350)), frameName);
    }
    // �����������Ϊ�򶯻���Ҳ��������������
    createSkillButton();
    createUpButton();
    return true;
}

void andeqieer::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {

        for (int i = 1; i <= 5; ++i) {
            std::string frameName = StringUtils::format("andeqieer_attack_%02d.png", i);

            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.3f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 1; i <= 8; ++i) {
            std::string frameName = StringUtils::format("AnDeRight%d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.2f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
}
void andeqieer::endSkill(float dt) {
    attackCooldown = attackCooldown + 1.5f; // ��������Χ����Ϊ����ֵ
    // ������Ҫ�ڼ��ܽ���ʱ���õĴ���
    ifskillison = false;
}
void andeqieer::arrowAnimation()
{
    if (this == nullptr) {
        return; // ���Ŀ�겻���ڣ���ֱ�ӷ���
    }
    // ��ȡĿ���λ��
    Vec2 targetPosition = this->getPosition();

    // ���ر�ը������֡
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 7; ++i) {  //����ͼƬ

        std::string frameName = StringUtils::format("boom%d.png", i);

        auto frame = frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
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
void andeqieer::castSkill()  //�ͷż���
{

        ifskillison = true;
        // ��ȡ��ǰ����
        auto currentScene = dynamic_cast<baseMap*>(this->getScene());
        if (currentScene) {
            attackCooldown = attackCooldown - 1.5f;
            for (auto monster : currentScene->activeMonsters) {
                // �������Ƿ��ڹ�����Χ��,���ҵ��˹�����ȴʱ�䣡
                if (isTargetInRange_mon(monster, attackRange)) {
                    // ����ǣ��򹥻����ﲢ���� true
                    monster->takedamage(100);
                    arrowAnimation();
                    break;
                }
            }
            this->schedule(CC_SCHEDULE_SELECTOR(andeqieer::endSkill), 7.5f);

        }
}
// ��������Ŀ���Ƿ���ָ���Ĺ�����Χ��             ����Ŀ��
bool andeqieer::isTargetInRange_mon(BaseMonster* target, float range) {
    // ���㵱ǰ��ɫ��Ŀ��֮��ľ���
    float distance = this->getPosition().distance(target->getPosition());
    // �������С�ڻ���ڹ�����Χ����Ŀ���ڷ�Χ��
    return distance <= range;
}

void andeqieer::levelup() //����Ч��
{

    if (level < 3)
        level += 1;  //��ɫ�ȼ�

    if (level == 2) {

        attackPower = 25.0f; // ������Ϊ10
        attackRange = 200.0f; // ������ΧΪ50
        setTexture("AnDeRight1.png");

    }
    if (level == 3) {

        attackPower = 35.0f; // ������Ϊ10
        attackRange = 225.0f; // ������ΧΪ50
        setTexture("AnDeRight1.png");

    }

}
void andeqieer::findTargetInRange() {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        int currentFrame = Director::getInstance()->getTotalFrames();
        for (auto monster : currentScene->activeMonsters) {
            if (monster->gethp() <= 0)
                break;
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= this->attackRange) {
                isAttacking = true;
                if (currentFrame - lastAttackTime >= attackCooldown) {
                    // Monster = monster;//   
                     /*
                     auto bullet = Bullet::create();
                     bullet->setPosition(this->getPosition()); // �����ӵ��ĳ�ʼλ��Ϊ����櫵�λ��
                     bullet->character = this; // �����ӵ���Ŀ��
                     bullet->monster = monster;
                     auto currentScene = dynamic_cast<baseMap*>(this->getScene());
                     bullet->scheduleUpdate();
                     currentScene->addChild(bullet); // ���ӵ���ӵ�������
                     bullet->getmove();*/
                     // ��������
                    auto sprite = Sprite::create("arrow.png");
                    sprite->setPosition(this->getPosition()); // ������ʼλ��
                    auto scene = Director::getInstance()->getRunningScene();
                    scene->addChild(sprite); // ��������ӵ���ǰ���еĳ���

                    // Ŀ��λ��
                    Vec2 targetPosition = monster->getPosition();

                    // �����ƶ�����
                    auto moveTo = MoveTo::create(1.0f, targetPosition); // 2�����ƶ���Ŀ��λ��

                    // �����ص����������ƶ���ɺ�ִ��
                    auto removeSprite = CallFunc::create([sprite]() {
                        sprite->removeFromParentAndCleanup(true);
                        });

                    // �������ж��������ƶ���Ȼ��ִ�лص�
                    auto sequence = Sequence::create(moveTo, removeSprite, nullptr);

                    // ִ�����ж���
                    sprite->runAction(sequence);

                    monster->takedamage(getattackPower());
                    lastAttackTime = currentFrame;  // �����ϴι�����֡��

                }

                return;

            }
        }
        isAttacking = false;
        isPlaying = false;
    }
}