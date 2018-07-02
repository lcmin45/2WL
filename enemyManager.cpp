#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

HRESULT enemyManager::init()
{
	_woodBoss = new woodBoss;
	_woodBoss->init();
	_woodBoss->setting("나무소환", PointMake(200,200));

	_iceBoss= new iceBoss;
	_iceBoss->init();
	_iceBoss->setting("얼음소환", PointMake(300,300));

	_fireBoss= new fireBoss;
	_fireBoss->init();
	_fireBoss->setting("불소환", PointMake(100,100));

	return S_OK;
}

void enemyManager::release() {}

void enemyManager::update()
{
	_woodBoss->update();
	_woodBoss->woodMove();

	_iceBoss->update();
	_iceBoss->iceMove();

	_fireBoss->update();
	_fireBoss->fireMove();
}

void enemyManager::render()
{
	_woodBoss->render();
	_iceBoss->render();
	_fireBoss->render();
}

void enemyManager::setBoss()
{

}
