#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

HRESULT enemyManager::init()
{
	IMAGEMANAGER->addFrameImage("SummonMonster", "image/Effect/SummonMonster.bmp", 0, 0, 64, 1856, 1, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ghoul", "image/monster/Ghoul.bmp", 0, 0, 560, 304, 10, 4, true, RGB(255, 0, 255));


	//_woodBoss = new woodBoss;
	//_woodBoss->init();
	//_woodBoss->setting("나무소환", PointMake(200,200));
	//
	//_iceBoss= new iceBoss;
	//_iceBoss->init();
	//_iceBoss->setting("얼음소환", PointMake(300,300));
	//
	//_fireBoss= new fireBoss;
	//_fireBoss->init();
	//_fireBoss->setting("불소환", PointMake(100,100));

	settingMonster();

	return S_OK;
}

void enemyManager::release() {}

void enemyManager::update()
{
	//_woodBoss->update();
	//_woodBoss->woodMove();
	//
	//_iceBoss->update();
	//_iceBoss->iceMove();
	//
	//_fireBoss->update();
	//_fireBoss->fireMove();

	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		(*_viGhoul)->update();
	}

}

void enemyManager::render()
{
	//_woodBoss->render();
	//_iceBoss->render();
	//_fireBoss->render();


	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		(*_viGhoul)->render();
	}
}

void enemyManager::setBoss()
{

}

void enemyManager::settingMonster()
{
	for (float i = 0; i < 3; ++i)
	{
		Ghoul* _ghoul;
		_ghoul = new Ghoul;
		_ghoul->init({ 128 + i * 128,128 }, 1 + i*0.5,i);

		_vGhoul.push_back(_ghoul);
	}

}
