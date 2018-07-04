#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

HRESULT enemyManager::init()
{
	///////���� �ʱ� ��ġ �������ֱ�
	_woodposition.x = WINSIZEX / 2;
	_woodposition.y = WINSIZEY / 2;
	_iceposition.x = WINSIZEX / 2;
	_iceposition.y = WINSIZEY / 2;
	_fireposition.x = WINSIZEX / 2;
	_fireposition.y = WINSIZEY / 2;

	_woodBoss = new woodBoss;
	_woodBoss->init();
	_woodBoss->setting("������ȯ", { _woodposition.x, _woodposition.y });

	_iceBoss = new iceBoss;
	_iceBoss->init();
	_iceBoss->setting("������ȯ", { _iceposition.x, _iceposition.y });

	_fireBoss = new fireBoss;
	_fireBoss->init();
	_fireBoss->setting("�Ҽ�ȯ", {_fireposition.x, _fireposition.y});


	return S_OK;
}

void enemyManager::release() {}

void enemyManager::update()
{
	//���� �߰��ϱ�
	_woodBoss->update();
	_woodBoss->woodMove();
	_woodBoss->woodSkill();
	//���� �߰��ϱ�
	_iceBoss->update();
	_iceBoss->iceMove();
	_iceBoss->iceSkill();
	//���� �߰��ϱ�
	_fireBoss->update();
	_fireBoss->fireMove();
	_fireBoss->fireSkill();
}

void enemyManager::render()
{
	//���� �߰��ϱ�
	_woodBoss->render();
	_iceBoss->render();
	_fireBoss->render();
}

