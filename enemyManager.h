#pragma once
#include "gameNode.h"
#include "monster.h"
#include "boss.h"
#include "fireBoss.h"
#include "iceBoss.h"
#include "woodBoss.h"

class enemyManager : public gameNode
{
private:

	//보스 클래스 소환
	woodBoss* _woodBoss;
	iceBoss* _iceBoss;
	fireBoss* _fireBoss;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setBoss();
};