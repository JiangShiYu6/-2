#pragma once
#include"cocos2d.h"
#include "main.h"
#include "AppDelegate.h"
#ifndef __HANDLER_H__
#define __HANDLER_H__
USING_NS_CC;

typedef enum {
    LaPuLanDe_1,  //һ����������
    LaPuLanDe_2,  //������������
    AnDeQieEr_1,  //һ�������ж�
    AnDeQieEr_2,  //���������ж�
    HeiJiao_1,  //һ���ڽ�
    HeiJiao_2,  //�����ڽ�
    HeMou_1,  //һ����Ĭ
    HeMou_2,  //������Ĭ
    AMiYa_1,  //һ�������
    AMiYa_2,  //һ�������
    JiJing_1,  //һ������
    JiJing_2,  //��������
    SoureStore,  //Դʯ��һ���Ե���
}HandlerType;
class BaseHandler :public Sprite
{
public:
    BaseHandler();
    ~BaseHandler();
    virtual void updateHandler() {};//������Ա������������
    virtual void sellHandler();//������Ա
    //virtual void removeHandler();//�Ƴ�������  //�Ƴ��������ǲ��ǿ���һ����˼��
    virtual bool init();//��ʼ����Ա
    CC_SYNTHESIZE(HandlerType, handlerType, HandlerType);  //��Ա����
    CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);  //�����
    CC_SYNTHESIZE(std::string, towerName, TowerName); //����
    CC_SYNTHESIZE(int, level, Level);//�ȼ�
    CC_SYNTHESIZE(float, scope, Scope);//��Χ
    CC_SYNTHESIZE(float, nextScope, NextScope);//������Χ
    CC_SYNTHESIZE(float, rate, Rate);//�����ٶ�
    CC_SYNTHESIZE(int, force, Force);//������
    CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
    CC_SYNTHESIZE(int, buildMoney, BuildMoney);//�۳�ʱ������Ǯ
    //virtual void showHandlerInfo();//��ʾ��Ա����Ϣ
    bool isUpdateMenuShown;     //github�¼ӵ�
    virtual void update1() {};//������������  //���Ǿ���һ�������������
    //virtual void update2() {};  //���������������ɾ��
    //virtual void setRallyPoint(Point point) {};//��Ӫ�������ü����                        //ɾ��
protected:   //������Ů��public�������ⲿ��private
    virtual void checkNearestMonster();//��⸽������
    BaseMonster* nearestMonster;  //�����ĵ���
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    virtual void showUpdateMenu() {};//��ʾ����ѡ��
    virtual void hideUpdateMenu();//����
    Sprite* terrain;//�����Ľ����
    void setListener();//����ĳЩ�����¼���              ��ʲô�õ��أ�
};

#endif  //#ifndef __HANDLER_H__