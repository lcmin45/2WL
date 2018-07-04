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

	//���� Ŭ���� ��ȯ
	woodBoss * _woodBoss;
	iceBoss* _iceBoss;
	fireBoss* _fireBoss;
	//���� ��ǥ����
	POINTFLOAT _woodposition, _iceposition, _fireposition;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};