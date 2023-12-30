#include "SimpleAudioEngine.h"
#include"MapSelect.h"
#include"PlayScene.h"
#include"PlayScene01.h"
#include"MainScene.h"
USING_NS_CC;

bool MapSelect::init() {
    if (!Scene::init()) 
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto Mysprite = Sprite::create("MAPS.jpg");
    Mysprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(Mysprite);
    // ����һ����ť
    auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(Vec2(15, 5+origin.y + visibleSize.height - button->getContentSize().height));
    button->addTouchEventListener(CC_CALLBACK_2(MapSelect::onButtonClicked, this));
    this->addChild(button);
    //��ͼ1�Ĳ˵�
    map_01_Item = MenuItemImage::create(
        "map_01_S.png",
        "map_01_S.png",
        CC_CALLBACK_1(MapSelect::menu_Map_01, this));
    map_01_Item->setPosition(visibleSize.width / 2 + origin.x, 4*(visibleSize.height / 8));
    auto menu1 = Menu::create(map_01_Item, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);
    map_02_Item = MenuItemImage::create(
        "map_02_S.png",
        "map_02_S.png",
        CC_CALLBACK_1(MapSelect::menu_Map_01, this));
    map_02_Item->setPosition((3*(visibleSize.width / 5)) + origin.x, 4 * (visibleSize.height / 8));
    auto menu2 = Menu::create(map_02_Item, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    return true;
}
void MapSelect::onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        // �л��������泡��

        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    }
}
void MapSelect::menu_Map_01(Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(2, PlayScene01::createScene()));
}
void MapSelect::menu_Map_02(Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(2, PlayScene::createScene()));
}
void MapSelect::onEnter() {
    Scene::onEnter();
    currentLevel = UserDefault::getInstance()->getIntegerForKey("level", 1);

    // ���ݹؿ�����������°�ť״̬
    map_02_Item->setEnabled(currentLevel >= 2); // ����2�ǵڶ��صĹؿ���
    // ��Ҳ�����޸İ�ť���������ӳ���ǵ�״̬
}
void MapSelect::unlockLevel(int level) {
    // ���¹ؿ���������
    currentLevel = level;
    UserDefault::getInstance()->setIntegerForKey("level", level);
    UserDefault::getInstance()->flush();
    // ���½���
    // ...
}
