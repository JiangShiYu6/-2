#pragma once
#include "cocos2d.h"

class StopScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::MenuItemImage* backtoGameItem;              // ������Ϸ������
    cocos2d::MenuItemImage* MapSelectItem;               // ����ѡ�ؽ�����
    bool isScaling_01;                                   // ��־λ�����ڷ�ֹ�ظ����
    bool isScaling_02;                                   // ��־λ�����ڷ�ֹ�ظ����
    void MapSelectCallback(cocos2d::Ref* pSender);       //������Ϸ����
    void backtoGameCallback(cocos2d::Ref* pSender);      //����ѡ�ؽ���
    
    CREATE_FUNC(StopScene);
};
