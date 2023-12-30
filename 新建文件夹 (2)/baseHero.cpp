#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include"baseHero.h"
#include"basemonster.h"

BaseCharacter::BaseCharacter() : currHp(0),maxHp(0), attackPower(0),blockCount(0) {}

BaseCharacter::~BaseCharacter() {}

bool BaseCharacter::init() {
    if (!Sprite::init()) {
        return false;
    }
    initMouseListener();
    // ��ʼ��Ѫ��
    healthBar = ProgressTimer::create(Sprite::create("hp_bar.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));                           // ���������
    healthBar->setBarChangeRate(Vec2(1, 0));                        // ˮƽ���
    healthBar->setPercentage(100);                                 // ��ʼѪ��Ϊ100%
    healthBar->setPosition(Vec2(this->getContentSize().width / 2,
        this->getContentSize().height + 10));                      // ����λ��
    this->addChild(healthBar);                                     // ��ӵ���ɫ�ڵ�
    this->scheduleUpdate();
    return true;
}

//����
void BaseCharacter::initCharacterAttributes(float health, float attackPower, int blockCount,float range,float Cooldown) {
    this->maxHp = health;
    this->currHp = health;
    this->attackPower = attackPower;
    this->blockCount = blockCount;
    this->attackRange = range;
    this->lastAttackTime = 0;
    this->attackCooldown = Cooldown;
}


//�����߼�
void BaseCharacter::takeDamage(float damage) {
    currHp -= damage;
    if (currHp < 0) {
        currHp = 0;
    }
    
    //updateHealthDisplay();
    playHitAnimation();
    // ����Ѫ����ʾ
    float healthPercentage = (currHp / maxHp) * 100;
    healthBar->setPercentage(healthPercentage);
    if (currHp <= 0) {
        // ��Ѫ������0ʱִ����ʧ����
        playDeathAnimationAndRemove();
    }
}

//���˱��
void BaseCharacter::playHitAnimation() {
    // ����һ�����Ķ���
    auto tintToRed = TintTo::create(0.1f, 255, 0, 0); // ����ʱ��0.1�룬��ɫΪ��ɫ

    // ����һ���������ָ���ԭʼ��ɫ
    auto tintToOriginal = TintTo::create(0.1f, 255, 255, 255); // �ָ�ʱ�����ɫ

    // ����һ�����ж������ȱ�죬Ȼ��ָ�ԭɫ
    auto sequence = Sequence::create(tintToRed, tintToOriginal, nullptr);

    // �����������
    this->runAction(sequence);
}

//����
void BaseCharacter::playDeathAnimationAndRemove() {
    // ����һ����������
    auto fadeOut = FadeOut::create(1.0f); // 1.0��Ľ�������

    // ����һ���ص��������ڽ���������ɺ��Ƴ���ɫ
    auto removeSelf = CallFunc::create([this]() {
        this->removeFromParent();
        });

    // ����һ�����ж������Ƚ�����Ȼ���Ƴ�
    auto sequence = Sequence::create(fadeOut, removeSelf, nullptr);

    // �����������
    this->runAction(sequence);
}

//��ʼ������¼�
void BaseCharacter::initMouseListener() {
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(BaseCharacter::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseCharacter::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto currentMap = dynamic_cast<baseMap*>(this->getScene());
    if (currentMap) {
        currentMap->removeCharacters(this);
    }
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        // ������Ҽ����ʱ���Ƴ���ɫ
        this->removeFromParent();
    }
   
}



bool BaseCharacter::findTargetInRange(float range) {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        for (auto monster : currentScene->activeMonsters) {
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= range) {
                this->playAttackAnimation();
                monster->takedamage(getattackPower());
                return true; // �ҵ��ڹ�����Χ�ڵĹ���
            }
        }
    }
    return false; // û���ҵ��ڹ�����Χ�ڵĹ���
}

void BaseCharacter::update(float dt) {
    if (Director::getInstance()->getTotalFrames() - lastAttackTime > attackCooldown) {
        // ��⹥����Χ�ڵ�Ŀ��
        if (findTargetInRange(attackRange)) {
            // ִ�й���
            lastAttackTime = Director::getInstance()->getTotalFrames();
        }
        else {
            this->stopAllActions();
        }
    }
    
}

float BaseCharacter::getattackPower() {
    return this->attackPower;
}


