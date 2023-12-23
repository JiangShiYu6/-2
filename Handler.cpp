#include"Handler.h"
#include"cocos2d.h"
#include "AppDelegate.h"
USING_NS_CC;
/*getInstance()
{
    if (instance == NULL)
        instance = new GameManager();
    return instance;
}*/
BaseHandler::BaseHandler()  //���캯��
    :isUpdateMenuShown(false)
{}
BaseHandler::~BaseHandler() {}  //��������
bool BaseHandler::init()  //��ʼ����Ա
{
    if (!Sprite::init())  // ���û��ࣨSprite���ĳ�ʼ������
    {
        return false;  // ��������ʼ��ʧ�ܣ��򷵻�false 
    }
    isUpdateMenuShown = false;  // ���ó�Ա���� isUpdateMenuShown �ĳ�ʼֵΪ false ,���Ƹ�Ա�Ƿ��ڲ˵���ʾ
    return true;  //��ʼ���ɹ�������true
}
void BaseHandler::checkNearestMonster()  //������Ĺ���                                                                     ��Ҫ�޸ģ�����������
{
    auto instance = GameManager::getInstance();  //������룬                                                             ������Ҫgamemanger���ࣿ
    auto monsterVector = instance->monsterVector;//ȫ��Vector�����������洢��ǰ�ؿ��ĵ���

    auto currMinDistant = this->scope;  //this�Ǹ�Ա

    nearestMonster = NULL;
    for (int i = 0; i < monsterVector.size(); i++)
    {
        auto monster = monsterVector.at(i);
        double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());//���������

        if (distance < currMinDistant && monster->getAttackByTower()) { //�������ķ�Χ�ڣ��ҹ�����Ա�������ĳЩ���¹���ֻ�����������Ա�������
            currMinDistant = distance;//������С���룬�ҵ�����Ĺ���
            <pre name = "code" class = "cpp">            nearestMonster < span style = "font-family: Arial, Helvetica, sans-serif;" >= monster< / span>  
        }
    }

}
void BaseHandler::setListener()  //���ø�Ա����ʱ��
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BaseHandler::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(BaseHandler::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
}
bool BaseHandler::onTouchBegan(Touch* touch, Event* event)  //�Դ����¼����д�����ʼ����
{
    return true;
}
void BaseHandler::onTouchEnded(Touch* touch, Event* event)  //��������                                      ��Ҫ�޸ģ�����������
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    Point locationInNode = target->convertTouchToNodeSpace(touch);

    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(locationInNode))//���������ڸ�Ա��Χ�ڣ��������Ա��Ŀǰֻ��ͨ���˷������ж��Ƿ�����Ա��
    {
        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(getHandlerType());//���ø������֣�BaseMap)��PlayState�㣬��ʾ��������Ϣ
        if (isUpdateMenuShown)//�����Ա���������Ѿ���ʾ�������أ�ĳ����ʾ
        {
            hideUpdateMenu();
        }
        else {
            showUpdateMenu();
        }
    }
    else {//�����������������ط�������������
        hideUpdateMenu();
    }
}
void BaseHandler::showHandlerInfo()  //��ʾ������Ϣ
{
    ;
}
void BaseHandler::sellHandler()  //���۸�Ա                                                                   //��Ҫ�޸ģ�����
{
    static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);  /// ����ǰ����ĸ����󣨼���ΪTerrain���ͣ���terrain��Ա��Ϊ�ɼ� 
    static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();  // �ӵ�ǰ������游���󣨼���ΪBaseMap���ͣ����Ƴ��йص�ǰ������Ϣ
    static_cast<Terrain*>(this->getParent())->smokeEffect();  //�ڵ�ǰ����ĸ����󣨼���ΪTerrain���ͣ��ϴ�������Ч��   �ĳ�ʲôЧ���أ� 
    this->unscheduleAllCallbacks();  //ȡ����ǰ�����������Ѱ��ŵĻص�����
    this->removeAllChildren();  //�Ƴ���ǰ����������Ӷ���
    this->removeFromParent();  //����ǰ������丸�������Ƴ�
}
void BaseHandler::setListener()  //������
{
    auto listener = EventListenerTouchOneByOne::create();  //����һ��������
    listener->onTouchBegan = CC_CALLBACK_2(BaseHandler::onTouchBegan, this);  //���ô�����ʼʱ�Ļص�����
    listener->onTouchEnded = CC_CALLBACK_2(BaseHandler::onTouchEnded, this);  // ���ô�������ʱ�Ļص�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);   // ����������ӵ��¼��ַ����У����г���ͼ���ȼ�
}
