#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1)
		return true;
	else
		return false;
}
void SoundManager::playclosehit()   //��ս������Ч
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playfarhit()   //Զ�̹�����Ч
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playQuestCompleted()   //ս���ɹ���Ч
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playQuestFailed()   //ս��ʧ����Ч
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}