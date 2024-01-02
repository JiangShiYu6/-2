#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("welcome01.jpg");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);

    // ����������
    auto loadingBar = ui::LoadingBar::create("LoadingBarFile.png");
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    loadingBar->setPosition(Vec2(visibleSize.width / 2, 50));
    loadingBar->setPercent(0); // ��ʼ������Ϊ0
    addChild(loadingBar);

    // ģ����Դ���أ��������100����Դ��ÿ�μ���һ����Դ��ģ���������
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::loadSource), 0.1f);

    return true;
}

void HelloWorld::loadSource(float dt)
{
    // ģ����Դ����
    numberOfLoadedRes++;

    // ���½�����
    float progress = static_cast<float>(numberOfLoadedRes) / 100.0f; // �������100����Դ
    CCLOG("Loading Progress: %.2f%%", progress * 10);

    // ���½������İٷֱ�
    auto loadingBar = dynamic_cast<ui::LoadingBar*>(getChildByTag(LoadingBarTag)); // ����������LoadingBar��tagΪLoadingBarTag
    if (loadingBar)
    {
        loadingBar->setPercent(progress * 100);
    }

    // ���������ɣ��л�����ӭҳ��
    if (numberOfLoadedRes == 10)
    {
        unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::loadSource));
        switchToWelcomeScene();
    }
}

void HelloWorld::switchToWelcomeScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::createScene()));
}



