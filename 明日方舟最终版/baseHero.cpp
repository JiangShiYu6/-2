#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include"baseHero.h"
#include"basemonster.h"
const int SKILL_BUTTON_TAG = 1001;  //����һ����ǩ
const float SKILL_COOLDOWN_TIME = 5.0f;
BaseCharacter::BaseCharacter() : currHp(100),maxHp(100), attackPower(0) {}

BaseCharacter::~BaseCharacter() {}

bool BaseCharacter::init() {
    if (!Sprite::init()) {
        return false;
    }
    
    // ��ʼ��Ѫ��
    healthBar = ProgressTimer::create(Sprite::create("hp_bar.png"));
   
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5)); // ���������
    healthBar->setBarChangeRate(Vec2(1, 0)); // ˮƽ���
    healthBar->setPercentage(100); // ��ʼѪ��Ϊ100%
   
    this->addChild(healthBar); // ��ӵ���ɫ�ڵ�
    deleteButton = ui::Button::create("CloseNormal.png", "CloseSelect.png");
   
    deleteButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onDeleteButtonClicked, this));
    this->addChild(deleteButton);
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::update), 0.1f);
    

    return true;
}

//����
void BaseCharacter::initCharacterAttributes(float health, float attackPower,float range,float Cooldown) {
    this->maxHp = health;
    this->currHp = health;
    this->attackPower = attackPower;
    this->attackRange = range;
    this->attackCooldown = Cooldown;
    this->lastAttackTime = 0;
    this->isAttacking = false;
    this->isPlaying = false;
}


//�����߼�
void BaseCharacter::takeDamage(float damage) {
    if (wudi)
        damage = 0;
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
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        currentMap->removeCharacters(this);
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

void BaseCharacter::onDeleteButtonClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        // ɾ����ɫ
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        if (currentMap) {
            currentMap->removeCharacters(this);
            this->removeFromParent();
        }
    }
}

void BaseCharacter::findTargetInRange() {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        int currentFrame = Director::getInstance()->getTotalFrames();
        for (auto monster : currentScene->activeMonsters) {
            if (monster->gethp() <= 0)
                break;
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= this->attackRange) {
                isAttacking = true;
                if(currentFrame - lastAttackTime >= attackCooldown) {
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

void BaseCharacter::update(float dt) {

    // ��⹥����Χ�ڵ�Ŀ��
    if (currHp <= 0) {
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        currentMap->removeCharacters(this);
        playDeathAnimationAndRemove();
    }
    findTargetInRange();

    if (!isPlaying) {
        if (isAttacking) {

            this->playAttackAnimation();
            isPlaying = true;
        }
        else {
            stopAllActions();
        }
    }
}  

float BaseCharacter::getattackPower() const{
    return this->attackPower;
}

bool BaseCharacter::initManaBar(const std::string& manaBarImage) {
    maxMana = 100; // �����������ֵ
    currentMana = 0; // ��ʼ����ֵ

    // ��������ʼ������
    manaBar = ProgressTimer::create(Sprite::create(manaBarImage));
    manaBar->setType(ProgressTimer::Type::BAR);
    manaBar->setMidpoint(Vec2(0, 0.5)); // ���������
    manaBar->setBarChangeRate(Vec2(1, 0));
    manaBar->setPercentage(0); // ��ʼ����Ϊ0%
    manaBar->setPosition(Vec2(this->getContentSize().width / 2,
        this->getContentSize().height/2+10)); // ����λ��
    this->addChild(manaBar);

    // ����ÿ����������Ķ�ʱ��
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);

    // ��ӵ���¼�����
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (manaBar->getBoundingBox().containsPoint(touch->getLocation())) {
            this->onManaBarClicked();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, manaBar);

    return true;
}

void BaseCharacter::onManaBarClicked() {
    if (currentMana >= maxMana) {
        this->castSkill();
        currentMana = 0; // �ͷż��ܺ���������ֵ
        manaBar->setPercentage(0);
    }
}

void BaseCharacter::updateMana(float dt) {
    currentMana += 10; // ÿ������10%
    if (currentMana > maxMana) {
        currentMana = maxMana;
        showSkillButton();  // ����������ʱ��ʾ���ܰ�ť
    }
    manaBar->setPercentage((currentMana / maxMana) * 100);
}

void BaseCharacter::createSkillButton() {
    skillButton = ui::Button::create("skill_button.png");
    skillButton->setPosition(Vec2(0, this->getContentSize().height / 2));
    skillButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onSkillButtonClicked, this));
    skillButton->setVisible(false);
    this->addChild(skillButton);
}

void BaseCharacter::showSkillButton() {
    if (currentMana >= maxMana) {
        skillButton->setVisible(true);
    }
}



void BaseCharacter::onSkillButtonClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        if (currentMana >= maxMana) {
            castSkill();       // ʵ�ּ���Ч��
            currentMana = 0;   // ���ü�����
            manaBar->setPercentage(0);
            skillButton->setVisible(false);  // ���ؼ��ܰ�ť
            startSkillCooldown(SKILL_COOLDOWN_TIME); // ��ʼ������ȴ
        }
    }
}

void BaseCharacter::startSkillCooldown(float cooldownTime) {
    // ��ȴ�ڼ似������������
    this->unschedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana));

    // ����һ����ʱ��������ȴʱ��������ٴ����ü������ĸ���
    this->scheduleOnce([this](float dt) {
        // ���������������ĸ���
        this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);

        // ���¼�鼼�����Ƿ������������������ʾ���ܰ�ť
        this->showSkillButton();
        }, cooldownTime, "cooldownTimer");
}

void BaseCharacter::createUpButton() {
    upButton = ui::Button::create("uplevel.png");
    upButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 50));
    upButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onlevelupClicked, this));
    this->addChild(upButton);
}

void BaseCharacter::onlevelupClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        if (!isAttacking&&currentMap->comsuption(cost02)) {
            levelup();       // ʵ������Ч��
            if (level == 3)
                upButton->setVisible(false);  // ���ؼ��ܰ�ť
        }
    }
}


