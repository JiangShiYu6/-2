#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	//static void playClickEffect();
	//static void playIncomingWave();
	//static void playNextWaveReady();

	//��Ч
	//static void playTowerMenu();
	//static void playShipOpen();
	//static void playWinStars();
	//��ս��Ա�Լ����﹥����Ч
	static void playclosehit();
	//static void playTowerUpdate();
	//static void playTowerSell();
	//Զ�̸�Ա������Ч
	static void playfarhit();
	//static void playTotemShot();
	//static void playTotemSpirits();
	//static void playTotemWeakness();
	//��ʯ
	//static void playFireballHit();
	//static void playFireballUnleash();
	//�ؿ�����
	static void playQuestCompleted();  //ս���ɹ���Ч
	static void playQuestFailed();   //ս��ʧ����Ч
	//����
	//static void playReinforcement();
	//static void playCash();
	//static void playFreeze();
	//static void playHearts();
public:
	//static void playWelcomeBackMusic();
	//static void playJungleBattle();
	//static void playDesertBattle();
	//static void playGameTheme1();
public:
	//BOSS 100
	//static void playEfreetiLaugh();
	//static void playEfreetiClap();
	//static void playEfreetiDeath();
private:
	static bool cheakEffectState();  //
};

#endif