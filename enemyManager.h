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



	//보스 클래스 소환
	woodBoss* _woodBoss;
	iceBoss* _iceBoss;
	fireBoss* _fireBoss;
	//보스 좌표설정
	POINTFLOAT _woodposition, _iceposition, _fireposition;

	vGhoul		_vGhoul;
	viGhoul		_viGhoul;


public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setBoss();

	void settingMonster();
};