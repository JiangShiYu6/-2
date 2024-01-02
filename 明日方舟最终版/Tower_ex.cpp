#include"Tower_ex.h"
#include "SimpleAudioEngine.h"
#include"MainScene.h"
USING_NS_CC;

Scene* Tower_ex_Scene::createScene()
{
    return Tower_ex_Scene::create();
}

bool Tower_ex_Scene::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto BG = Sprite::create("Select_bg.jpg");
    BG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(BG);
    // ������ť
    auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(cocos2d::Vec2(15, 5 + origin.y + visibleSize.height - button->getContentSize().height));
    button->addTouchEventListener(CC_CALLBACK_2(Tower_ex_Scene::onButtonClicked, this));
    this->addChild(button);

    Tower01= MenuItemImage::create(
        "ami.jpg",
        "ami.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower,this));
    Tower01->setPosition(visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu1 = Menu::create(Tower01, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    Tower02 = MenuItemImage::create(
        "qieer.jpg",
        "qieer.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower,this));
    Tower02->setPosition(2*visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu2 = Menu::create(Tower02, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    Tower03 = MenuItemImage::create(
        "heijiao.jpg",
        "heijiao.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower03->setPosition(3 * visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu3 = Menu::create(Tower03, NULL);
    menu3->setPosition(Vec2::ZERO);
    this->addChild(menu3, 1);

    Tower04 = MenuItemImage::create(
        "jijing.jpg",
        "jijing.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower04->setPosition( visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu4 = Menu::create(Tower04, NULL);
    menu4->setPosition(Vec2::ZERO);
    this->addChild(menu4, 1);

    Tower05 = MenuItemImage::create(
        "hemo.jpg",
        "hemo.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower05->setPosition(2 * visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu5 = Menu::create(Tower05, NULL);
    menu5->setPosition(Vec2::ZERO);
    this->addChild(menu5, 1);

    Tower06 = MenuItemImage::create(
        "lapu.jpg",
        "lapu.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower06->setPosition(3 * visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu6 = Menu::create(Tower06, NULL);
    menu6->setPosition(Vec2::ZERO);
    this->addChild(menu6, 1);

    return true;
}

void Tower_ex_Scene::Tower(Ref* pSender) {
    auto menuItem = dynamic_cast<MenuItemImage*>(pSender); // ������ȡ�����¼���MenuItemImage����
    if (!menuItem) return; // ��ȫ���

    auto scaleToSmall = ScaleTo::create(0.1f, 0.9f); // ��С�� 90% �Ĵ�С
    auto scaleToNormal = ScaleTo::create(0.1f, 1.0f); // �ָ���ԭʼ��С
    auto sequence = Sequence::create(scaleToSmall, scaleToNormal, nullptr);
    // ����С�����������˵���
    menuItem->runAction(sequence); // ����Ӧ��ʹ��menuItem��������T
    stopAllActions();
    if(menuItem== Tower01)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower02)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower03)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower04)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower05)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower06)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));

}

void Tower_ex_Scene::onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    // ��鴥���¼��Ƿ������Ҳ�����û��Ƿ��ɿ��˰�ť
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        // �л��������泡��
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    }
}


