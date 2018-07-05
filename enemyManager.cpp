#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

HRESULT enemyManager::init()
{

	setBoss();
	settingMonster();

	return S_OK;
}

void enemyManager::release() {}

void enemyManager::update()
{


	BossUpdate();
	monsterUpdate();

}

void enemyManager::render()
{
	BossRender();
	monsterRender();
}

void enemyManager::setBoss()
{
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
	_fireBoss->setting("�Ҽ�ȯ", { _fireposition.x, _fireposition.y });


}

void enemyManager::BossUpdate()
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

void enemyManager::BossRender()
{
	//���� �߰��ϱ�
	_woodBoss->render();
	_iceBoss->render();
	_fireBoss->render();
}

void enemyManager::settingMonster()
{
	for (float i = 0; i < 3; ++i)
	{
		Ghoul* _ghoul;
		_ghoul = new Ghoul;
		_ghoul->init({ 128 + i * 128,128 }, i);

		_vGhoul.push_back(_ghoul);
	}
	for (float i = 0; i < 3; ++i)
	{
		Knight* _Knight;
		_Knight = new Knight;
		_Knight->init("BlueKnight", { 128 + i * 128,256 }, i);

		_vKnight.push_back(_Knight);
	}
}

void enemyManager::monsterUpdate()
{

	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		(*_viGhoul)->update();
	}
	for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); ++_viKnight)
	{
		(*_viKnight)->update();
	}
}

void enemyManager::monsterRender()
{
	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		(*_viGhoul)->render();
	}
	for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); ++_viKnight)
	{
		(*_viKnight)->render();
	}
}
