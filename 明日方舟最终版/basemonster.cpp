#include"basemonster.h"

bool BaseMonster::init() {
	if (!Sprite::init()) {
		return false;
	}
	// ���� action ����������ÿ0.1�����һ��
	
	this->schedule(CC_SCHEDULE_SELECTOR(BaseMonster::action), 0.1f);
	
	return true;
	
}

void BaseMonster::takedamage(float damage) {
	if (damage <= 0) {
		damage = 0;
	}
	float real_damage = damage / this->defence;
	this->cur_Hp -= real_damage;
	if (this->cur_Hp > 0) {
		// ����һ�����Ķ���
		auto tintToRed = TintTo::create(0.1f, 255, 0, 0); // ����ʱ��0.1�룬��ɫΪ��ɫ

		// ����һ���������ָ���ԭʼ��ɫ
		auto tintToOriginal = TintTo::create(0.1f, 255, 255, 255); // �ָ�ʱ�����ɫ

		// ����һ�����ж������ȱ�죬Ȼ��ָ�ԭɫ
		auto sequence = Sequence::create(tintToRed, tintToOriginal, nullptr);

		// �����������
		this->runAction(sequence);
	}
}

void BaseMonster::checkNearbyHeroes() {
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (!currentMap) {
		return;
	}

	int currentFrame = Director::getInstance()->getTotalFrames();

	// �������н�ɫ
	for (auto& character : currentMap->characters) {
		if (character->gethp() <= 0||character->JorY()==1) {
			break;
		}
		float distance = this->getPosition().distance(character->getPosition());

		// ����Ƿ��ڹ�����Χ�ڣ����Ҽ�鹥����ȴ�Ƿ����
		if (distance <= this->range ) {
			
			Attack();  // �ı����״̬��׼������
			if (currentFrame - lastAttackTime >= attackCooldown) {
				character->takeDamage(this->force);
				lastAttackTime = currentFrame;  // �����ϴι�����֡��
				
			}
			else {
				isAttackAnimationPlaying = true;

			}
			return;
		}
	}
	this->StopAttak();
	
}

void BaseMonster::action(float dt) {
	// ����Ƿ񵽴��յ��Ѫ��Ϊ0
	if (cur_Hp <= 0) {
		stopAllActions();
		disappear();
		return;
	}


	// �����Χ�Ƿ����Ӣ��
	checkNearbyHeroes();
	
	// ����������ڹ������򲥷Ź�������
	if (isAttacking) {
		
		if (!isAttackAnimationPlaying) {
			if (isMoving) {
				this->stopAllActions();
				isMoving = false;
			}
			playAttackAnimation();
			isAttackAnimationPlaying = true;
		}
		
	}
	// ����ִ���ƶ��߼�
	else {
		
		if (isAttackAnimationPlaying) {
			this->stopAllActions();
			isAttackAnimationPlaying = false;
		}
		if (!isMoving) {
			playMoveAnimation();
			isMoving = true;
		}
		
		// ��ȡ��ǰĿ���
		auto targetPoint = movementPath[currentPathIndex];

		// �����ƶ�����
		Vec2 direction = (targetPoint - this->getPosition()).getNormalized();
		float moveDistance = speed * dt * 10;
		Vec2 newPoint = this->getPosition() + direction * moveDistance;

		// ���ù����µ�λ��
		this->setPosition(newPoint);


		// ����Ƿ񵽴ﵱǰĿ���
		if (newPoint.distance(targetPoint) < moveDistance) {

			currentPathIndex++;

			if (currentPathIndex >= movementPath.size()) {
				// �������·��ĩβ�����õ����յ���߼�
				reachDestination();
				disappear();
			}
		}
	}
}



void BaseMonster::disappear() {
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (currentMap) {
		currentMap->removeActiveMonster(this);  // ��activeMonsters�������Ƴ�
		this->removeFromParent();  // �ӳ������Ƴ�����
	}
	
}

void BaseMonster::reachDestination() {
	
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (currentMap) {
		currentMap->HP_off();
	}
}



void BaseMonster::update(float dt) {
	// ���������action����
	this->action(dt);
}
