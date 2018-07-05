#pragma once
#include "gameNode.h"
#include "monster.h"
#include "boss.h"
#include "fireBoss.h"
#include "iceBoss.h"
#include "woodBoss.h"

#include <vector>
#include "Ghoul.h"
#include "Knight.h"
#include "Mage.h"
#include "Rogue.h"
#include "Scarecrow.h"

class enemyManager : public gameNode
{
private:

	typedef vector<Ghoul*>					vGhoul;
	typedef vector<Ghoul*>::iterator		viGhoul;

	typedef vector<Knight*>					vKnight;
	typedef vector<Knight*>::iterator		viKnight;

	typedef vector<Mage*>					vMage;
	typedef vector<Mage*>::iterator			viMage;

	typedef vector<Rogue*>					vRogue;
	typedef vector<Rogue*>::iterator		viRogue;

	typedef vector<Scarecrow*>				vScarecrow;
	typedef vector<Scarecrow*>::iterator	viScarecrow;




	//보스 클래스 소환
	woodBoss* _woodBoss;
	iceBoss* _iceBoss;
	fireBoss* _fireBoss;
	//보스 좌표설정
	POINTFLOAT _woodposition, _iceposition, _fireposition;


	vGhoul			_vGhoul;
	viGhoul			_viGhoul;

	vKnight			 _vKnight;
	viKnight		 _viKnight;

	vMage			 _vMage;
	viMage			 _viMage;

	vRogue			 _vRogue;
	viRogue			 _viRogue;

	vScarecrow		 _vScarecrow;
	viScarecrow		 _viScarecrow;


public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBoss();
	void BossUpdate();
	void BossRender();

	void settingMonster();
	void monsterUpdate();
	void monsterRender();
};