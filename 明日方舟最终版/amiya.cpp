#include "SimpleAudioEngine.h"
#include"amiya.h"
#include"baseMap.h"
USING_NS_CC;


bool amiya::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }
    cost01 = 8;
    cost02 = 8;
    jinoryuan = 1;
    // ���� heijiao ������ͼ��
    this->setTexture("amiya_attack_01.png");
    
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(500, 20, 150, 50);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height/2 +30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height/2+20));
    // ... ������������
    if (!initManaBar("blue.png")) {
        return false;
    }
    // �����������Ϊ�򶯻���Ҳ��������������
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 13; i++) {
        std::string frameName = StringUtils::format("amiya_attack_%02d.png", i);
        amiya::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 3; i <= 15; i++) {
        std::string frameName = StringUtils::format("AmiyaRight%d.png", i);
        amiya::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    createSkillButton();
    createUpButton();
    return true;
}

void amiya::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {
        
        for (int i = 1; i <= 13; ++i) {
            std::string frameName = StringUtils::format("amiya_attack_%02d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // ÿ֡���0.1��
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 3; i <= 15; ++i) {
            std::string frameName = StringUtils::format("AmiyaRight%d.png", i);
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
void amiya::castSkill()
{
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        // ���������е����л����
        
        for (auto monster : currentScene->activeMonsters) {
           
            if (isTargetInRange_mon(monster, attackRange)) {
               
                monster->takedamage(50);
                boomAnimation(monster);
                return;
            }
           
            
        }
    }
}

void amiya::boomAnimation(BaseMonster* target)
{
    if (target == nullptr) {
        return; // ���Ŀ�겻���ڣ���ֱ�ӷ���
    }

    

    // ��������
    auto sprite = Sprite::create("baozha.png");
    sprite->setPosition(target->getPosition()); // ���þ������ʼλ�ã�x �� y ����ϣ��������ֵ�����
    sprite->setScale(0); // ��ʼ����Ϊ0����ȫ��С��

    // �������Ŷ�������С����
    auto scaleUp = ScaleTo::create(1.0f, 1.0f); // ��������ʱ��Ϊ1�룬���ŵ�ԭʼ��С

    // ������������
    auto fadeOut = FadeOut::create(1.0f); // 1���ڽ�����ʧ

    // ����һ���ص��������ڶ����������Ƴ�����
    auto removeSprite = CallFunc::create([sprite]() {
        sprite->removeFromParent();
        });

    
    auto sequence = Sequence::create(scaleUp, fadeOut, removeSprite, nullptr);

    // ���ж���
    sprite->runAction(sequence);

    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    currentScene->addChild(sprite,INT_MAX);
}

// ��������Ŀ���Ƿ���ָ���Ĺ�����Χ��             ����Ŀ��
bool amiya::isTargetInRange_mon(BaseMonster* target, float range) {
    // ���㵱ǰ��ɫ��Ŀ��֮��ľ���
    float distance = this->getPosition().distance(target->getPosition());
    // �������С�ڻ���ڹ�����Χ����Ŀ���ڷ�Χ��
    return distance <= range;
}

void amiya::levelup() {
    
    
    if (level < 3)
        level += 1;  //��ɫ�ȼ�
   
    if (level == 2) {
       
        attackPower = 25.0f; // ������Ϊ10
        attackRange = 200.0f; // ������ΧΪ50
        setTexture("AmiyaRight1.png");
        
    }
    if (level == 3) {
       
        attackPower = 35.0f; // ������Ϊ10
        attackRange = 225.0f; // ������ΧΪ50
        setTexture("AmiyaRight1.png");
        
    }
    
}
void amiya::findTargetInRange() {
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
                
                     // ��������
                    auto sprite = Sprite::create("magic.png");
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