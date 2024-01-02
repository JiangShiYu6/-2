#pragma once
#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::MenuItemImage* replaceItem; // �˵���
    bool isScaling; // ��־λ�����ڷ�ֹ�ظ����
    void menuReplaceCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
};

