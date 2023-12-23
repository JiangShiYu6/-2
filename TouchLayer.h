#ifndef _TOUCH_LAYER_H_
#define _TOUCH_LAYER_H_

#include "cocos2d.h"
#include "Handler.h"


USING_NS_CC;

class TouchLayer :public Layer
{
public:
	virtual bool init();   // �꣬��������TouchLayer���� 
	CREATE_FUNC(TouchLayer);
	EventListenerTouchOneByOne* PlaceListener;   //���ü�����
	EventListenerTouchOneByOne* RetreatListener;  //���˼�����
	EventListenerTouchOneByOne* LevelupListener;  //����������
	//EventListenerTouchOneByOne* Freezelistener;
	//EventListenerTouchOneByOne* Dynamitelistener;  //ըҩ������
	//EventListenerTouchOneByOne* FiereBalllistener;   ����л������ʵ��Դʯ

	void setDynamiteTouchShield();  
	void removeDynamiteTouchShield();
	bool onDynamiteTouchBegan(Touch* touch, Event* event);
	void onDynamiteTouchEnded(Touch* touch, Event* event);

	void setRallyFlagTouchShield();
	void removeRallyFlagTouchShield();
	bool onRallyFlagTouchBegan(Touch* touch, Event* event);
	void onRallyFlagTouchEnded(Touch* touch, Event* event);

	void setSoldierTouchShield();
	void removeSoldierTouchShield();
	bool onSoldierTouchBegan(Touch* touch, Event* event);
	void onSoldierTouchEnded(Touch* touch, Event* event);

	void setFreezeTouchShield();
	void removeFreezeTouchShield();
	bool onFreezeTouchBegan(Touch* touch, Event* event);
	void onFreezeTouchEnded(Touch* touch, Event* event);

	void setFireBallTouchShield();
	void removeFireBallTouchShield();
	bool onFireBallTouchBegan(Touch* touch, Event* event);
	void onFireBallTouchEnded(Touch* touch, Event* event);

	void removeTouchShield();
	void setTouchShield();

	BaseTower* tower;
	void addRallyFlag(Point location);
	void addWrongPlace(Point location);

	bool isFlag;
	bool onPlaceBegan(Touch* touch, Event* event);   //���ü�����
	void onPlaceEnded(Touch* touch, Event* event);
	void onPlaceMoved(Touch* touch, Event* event);
	Size winSize;
	bool isMoved;
	RallyCircle* rallyCircle;
	void removeAllListener();
};

#endif