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
	monsterRemove();

}

void enemyManager::render()
{
	BossRender();
	monsterRender();
}

void enemyManager::setBoss()
{
	_woodposition.x = 5376;
	_woodposition.y = 304;
	_iceposition.x = 656;
	_iceposition.y = 464;
	_fireposition.x = 624;
	_fireposition.y = 4224;

	_woodBoss = new woodBoss;
	_woodBoss->init();
	_woodBoss->setting("나무소환", { _woodposition.x, _woodposition.y });

	_iceBoss = new iceBoss;
	_iceBoss->init();
	_iceBoss->setting("얼음소환", { _iceposition.x, _iceposition.y });

	_fireBoss = new fireBoss;
	_fireBoss->init();
	_fireBoss->setting("불소환", { _fireposition.x, _fireposition.y });


}

void enemyManager::BossUpdate()
{

	//조건 추가하기
	_woodBoss->setPlayerPoint(_playerPoint);
	_woodBoss->update();
	_woodBoss->woodMove();
	_woodBoss->woodSkill();
	_woodBoss->setProjectileAddressLink(_PM);
	//조건 추가하기
	_iceBoss->update();
	_iceBoss->iceMove();
	_iceBoss->iceSkill();
	_iceBoss->setPlayerPoint(_playerPoint);
	_iceBoss->setProjectileAddressLink(_PM);
	//조건 추가하기
	_fireBoss->update();
	_fireBoss->fireMove();
	_fireBoss->fireSkill();
	_fireBoss->setPlayerPoint(_playerPoint);
	_fireBoss->setProjectileAddressLink(_PM);
}

void enemyManager::BossRender()
{
	//조건 추가하기
	_woodBoss->render();
	_iceBoss->render();
	_fireBoss->render();
}

void enemyManager::settingMonster()			//주석은 타일 번호
{
	//훈련용 허수아비 이닛
	for (float i = 0; i <2; ++i)
	{
		for (float j = 0; j < 3; ++j)
		{
			Scarecrow* _Scarecrow;
			_Scarecrow = new Scarecrow;
			_Scarecrow->init({ 2816 + i * 896 + 16 ,(4736 + j * 128 + 16) });	// 88.148 , 88.152 , 88.156 / 116.148 , 116.152 , 116.156

			_vScarecrow.push_back(_Scarecrow);
		}
	}
	//index 4 번 몬스터 이닛
	{
		for (float i = 0; i < 1; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 3264 + 16, 3776 + 16 }, 4);		//102.118

			_vGhoul.push_back(_ghoul);
		}
		for (float i = 0; i < 2; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 2976 + i * 736 + 16, 3936 + 16 }, 4);	//93.123 , 116.123

			_vGhoul.push_back(_ghoul);
		}
	}
	//index 5 번 몬스터 이닛 (RED)
	{
		for (float i = 0; i < 1; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 1504 + 16, 3040 + 16 }, 5);	//47.95

			_vGhoul.push_back(_ghoul);
		}

		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("RedMage", {1344+16,2720+16}, 5);	//42.85

			_vMage.push_back(_Mage);
		}
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("RedKnight", { 1600 +16,2816 +16 }, 5);	//50.88
			_vKnight.push_back(_Knight);
		}
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("RedRogue", { 1408+16,3232+16 }, 5);	//44.101

			_vRogue.push_back(_Rogue);
		}
	}
	//index 6 번 몬스터 이닛 (BLUE)
	{
		for (float i = 0; i < 1; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 3232 + 16, 1792 + 16 }, 6);	//101.56

			_vGhoul.push_back(_ghoul);
		}

		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("BlueMage", { 3616 + 16,1504 + 16 }, 6);	//113.47

			_vMage.push_back(_Mage);
		}
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("BlueKnight", { 3552 + 16,1856+ 16 }, 6);	//111.58
			_vKnight.push_back(_Knight);
		}
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("BlueRogue", { 3200 + 16,1440 + 16 }, 6);	//100.45

			_vRogue.push_back(_Rogue);
		}
	}
	//index 7 번 몬스터 이닛 (GREEN)
	{
		for (float i = 0; i < 1; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 4672 + 16, 2752 + 16 }, 7);	// 146.86

			_vGhoul.push_back(_ghoul);
		}

		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("GreenMage", { 5088 + 16,2688 + 16 }, 7);	//159.84

			_vMage.push_back(_Mage);
		}
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("GreenKnight", { 4800 + 16,3040 + 16 }, 7);	//150.95
			_vKnight.push_back(_Knight);
		}
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("GreenRogue", { 5024 + 16,3200 + 16 }, 7);	//157.100

			_vRogue.push_back(_Rogue);
		}
	}

	//for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	//{
	//	(*_viGhoul)->setSkillLink(_PM);
	//	(*_viGhoul)->setStageLink(_stage);
	//	(*_viGhoul)->setPlayerPoint(_playerPoint);
	//	(*_viGhoul)->setPlayerIndex(_playerIndex);
	//}
	//for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	//{
	//	(*_viGhoul)->setSkillLink(_PM);
	//	(*_viGhoul)->setStageLink(_stage);
	//	(*_viGhoul)->setPlayerPoint(_playerPoint);
	//	(*_viGhoul)->setPlayerIndex(_playerIndex);
	//}
	//for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); ++_viKnight)
	//{
	//	(*_viKnight)->setSkillLink(_PM);
	//	(*_viKnight)->setStageLink(_stage);
	//	(*_viKnight)->setPlayerPoint(_playerPoint);
	//	(*_viKnight)->setPlayerIndex(_playerIndex);
	//}
	//for (_viMage = _vMage.begin(); _viMage != _vMage.end(); ++_viMage)
	//{
	//	(*_viMage)->setSkillLink(_PM);
	//	(*_viMage)->setStageLink(_stage);
	//	(*_viMage)->setPlayerPoint(_playerPoint);
	//	(*_viMage)->setPlayerIndex(_playerIndex);
	//}
	//for (_viRogue = _vRogue.begin(); _viRogue != _vRogue.end(); ++_viRogue)
	//{
	//	(*_viRogue)->setSkillLink(_PM);
	//	(*_viRogue)->setStageLink(_stage);
	//	(*_viRogue)->setPlayerPoint(_playerPoint);
	//	(*_viRogue)->setPlayerIndex(_playerIndex);
	//}

}

void enemyManager::monsterUpdate()
{
	
	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		(*_viGhoul)->setSkillLink(_PM);
		(*_viGhoul)->setStageLink(_stage);
		(*_viGhoul)->setPlayerPoint(_playerPoint);
		(*_viGhoul)->setPlayerIndex(_playerIndex);
		(*_viGhoul)->update();
	}
	for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); ++_viKnight)
	{
		(*_viKnight)->setSkillLink(_PM);
		(*_viKnight)->setStageLink(_stage);
		(*_viKnight)->setPlayerPoint(_playerPoint);
		(*_viKnight)->setPlayerIndex(_playerIndex);
		(*_viKnight)->update();
	}
	for (_viMage = _vMage.begin(); _viMage != _vMage.end(); ++_viMage)
	{
		(*_viMage)->setSkillLink(_PM);
		(*_viMage)->setStageLink(_stage);
		(*_viMage)->setPlayerPoint(_playerPoint);
		(*_viMage)->setPlayerIndex(_playerIndex);
		(*_viMage)->update();
	}
	for (_viRogue = _vRogue.begin(); _viRogue != _vRogue.end(); ++_viRogue)
	{
		(*_viRogue)->setSkillLink(_PM);
		(*_viRogue)->setStageLink(_stage);
		(*_viRogue)->setPlayerPoint(_playerPoint);
		(*_viRogue)->setPlayerIndex(_playerIndex);
		(*_viRogue)->update();
	}

	for (_viScarecrow = _vScarecrow.begin(); _viScarecrow != _vScarecrow.end(); ++_viScarecrow)
	{
		(*_viScarecrow)->update();
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
	for (_viMage = _vMage.begin(); _viMage != _vMage.end(); ++_viMage)
	{
		(*_viMage)->render();
	}
	for (_viRogue = _vRogue.begin(); _viRogue != _vRogue.end(); ++_viRogue)
	{
		(*_viRogue)->render();
	}
	for (_viScarecrow = _vScarecrow.begin(); _viScarecrow != _vScarecrow.end(); ++_viScarecrow)
	{
		(*_viScarecrow)->render();
	}
}

void enemyManager::monsterRemove()
{
	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); ++_viGhoul)
	{
		if ((*_viGhoul)->getIsDie())
		{
			_viGhoul = _vGhoul.erase(_viGhoul);
		}
	}
	for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); ++_viKnight)
	{
		if ((*_viKnight)->getIsDie())
		{
			_viKnight = _vKnight.erase(_viKnight);
		}
	}
	for (_viMage = _vMage.begin(); _viMage != _vMage.end(); ++_viMage)
	{
		if ((*_viMage)->getIsDie())
		{
			_viMage = _vMage.erase(_viMage);
		}
	}
	for (_viRogue = _vRogue.begin(); _viRogue != _vRogue.end(); ++_viRogue)
	{
		if ((*_viRogue)->getIsDie())
		{
			_viRogue = _vRogue.erase(_viRogue);
		}
	}



}
