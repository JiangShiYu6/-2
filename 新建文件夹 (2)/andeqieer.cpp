#include "SimpleAudioEngine.h"
#include"andeqieer.h"
#include"basemonster.h"
USING_NS_CC;
bool andeqieer::init() {
    // ���ȵ��û���ĳ�ʼ��
    if (!BaseCharacter::init()) {
        return false;
    }

    // ���� heijiao ������ͼ��
    this->setTexture("�����ж�-����.png");
    // ���� heijiao �ĳ�ʼ����
    this->initCharacterAttributes(500, 10, 5, 500, 50);

    // ... ������������

    // �����������Ϊ�򶯻���Ҳ��������������

    return true;
}

void andeqieer::playAttackAnimation() {

}