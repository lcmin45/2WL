#include "stdafx.h"
#include "enemyManager.h"
#include "itemManager.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

static int _key = 0;

HRESULT enemyManager::init()
{
	_key += 1;

	setBoss();

	_alreadyDrop[0] = false; //fire
	_alreadyDrop[1] = false; //ice
	_alreadyDrop[2] = false; //wood

	saveNow = false;

	return S_OK;
}

void enemyManager::release()
{
	_vGhoul.clear();
	_vKnight.clear();
	_vMage.clear();
	_vRogue.clear();
	_vScarecrow.clear();
}

void enemyManager::update()
{


	BossUpdate();
	settingMonster(_key);
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

	fireBossStart = false;
	iceBossStart = false;
	woodBossStart = false;

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
	if (1 == _playerIndex) fireBossStart = true;
	if (2 == _playerIndex) iceBossStart = true;
	if (3 == _playerIndex) woodBossStart = true;
	if (fireBossStart)
	{
		_fireBoss->update();
		_fireBoss->fireMove();
		_fireBoss->setPlayerPoint(_playerPoint);
		_fireBoss->setProjectileAddressLink(_PM);
	}
	//조건 추가하기
	if (iceBossStart)
	{
		_iceBoss->update();
		_iceBoss->iceMove();
		_iceBoss->setPlayerPoint(_playerPoint);
		_iceBoss->setProjectileAddressLink(_PM);
	}
	//조건 추가하기
	if (woodBossStart)
	{
		_woodBoss->setPlayerPoint(_playerPoint);
		_woodBoss->update();
		_woodBoss->woodMove();
		_woodBoss->setProjectileAddressLink(_PM);
	}

	BossDie();
}

void enemyManager::BossRender()
{
	//조건 추가하기
	if (fireBossStart) { _fireBoss->render(); }
	if (iceBossStart) { _iceBoss->render(); }
	if (woodBossStart) { _woodBoss->render(); }
}

void enemyManager::BossDie()
{
	saveNow = false;
	if (_fireBoss->getFireBossDie() && !_alreadyDrop[0]) { _itemManager->dropItem(_fireBoss->getPosition()); _alreadyDrop[0] = true; saveNow = true; }
	if (_iceBoss->getIceBossDie() && !_alreadyDrop[1]) { _itemManager->dropItem(_iceBoss->getPosition()); _alreadyDrop[1] = true; saveNow = true; }
	if (_woodBoss->getWoodBossDie() && !_alreadyDrop[2]) { _itemManager->dropItem(_woodBoss->getPosition()); _alreadyDrop[2] = true; saveNow = true; }
}

void enemyManager::settingMonster(int key)			//주석은 타일 번호
{
	//훈련용 허수아비 이닛
	if (_vScarecrow.size() == 0)
	{
		for (float i = 0; i < 2; ++i)
		{
			for (float j = 0; j < 3; ++j)
			{
				Scarecrow* _Scarecrow;
				_Scarecrow = new Scarecrow;
				_Scarecrow->init({ 2816 + i * 896 + 16 ,(4736 + j * 128 + 16) });	// 88.148 , 88.152 , 88.156 / 116.148 , 116.152 , 116.156

				_vScarecrow.push_back(_Scarecrow);
			}
		}
	}
	//index 4 번 몬스터 이닛 (Ghoul)
	if (_vGhoul.size() == 0 && _playerIndex !=4)
	{
		++_key;
		for (float i = 0; i < 1; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 3264 + 16, 3776 + 16 }, 4, key);		//102.118

			_vGhoul.push_back(_ghoul);
		}
		for (float i = 0; i < 2; ++i)
		{
			Ghoul* _ghoul;
			_ghoul = new Ghoul;
			_ghoul->init({ 2976 + i * 736 + 16, 3936 + 16 }, 4, key);	//93.123 , 116.123

			_vGhoul.push_back(_ghoul);
		}
	}
	//index 5 번 몬스터 이닛 (Mage)
	if (_vMage.size() == 0 && _playerIndex != 5)
	{
		++_key;
		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("RedMage", { 1344 + 16,2720 + 16 }, 5, key);	//42.85

			_vMage.push_back(_Mage);
		}
		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("BlueMage", { 1600 + 16,2816 + 16 }, 5, key);	//50.88

			_vMage.push_back(_Mage);
		}
		for (float i = 0; i < 1; ++i)
		{
			Mage* _Mage;
			_Mage = new Mage;
			_Mage->init("GreenMage", { 1408 + 16,3232 + 16 }, 5, key);	//44.101

			_vMage.push_back(_Mage);
		}
	}
	//index 6 번 몬스터 이닛 (Knight)
	if (_vKnight.size() == 0 && _playerIndex != 6)
	{
		++_key;
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("RedKnight", { 3616 + 16,1504 + 16 }, 6, key);	//113.47
			_vKnight.push_back(_Knight);
		}
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("BlueKnight", { 3552 + 16,1856 + 16 }, 6, key);	//111.58
			_vKnight.push_back(_Knight);
		}
		for (float i = 0; i < 1; ++i)
		{
			Knight* _Knight;
			_Knight = new Knight;
			_Knight->init("GreenKnight", { 3200 + 16,1440 + 16 }, 6, key);	//100.45
			_vKnight.push_back(_Knight);
		}
	}
	//index 7 번 몬스터 이닛 (Rogue)
	if (_vRogue.size() == 0 && _playerIndex != 7)
	{
		++_key;
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("RedRogue", { 5088 + 16,2688 + 16 }, 7, key);	//159.84

			_vRogue.push_back(_Rogue);
		}
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("BlueRogue", { 4800 + 16,3040 + 16 }, 7, key);	//150.95

			_vRogue.push_back(_Rogue);
		}
		for (float i = 0; i < 1; ++i)
		{
			Rogue* _Rogue;
			_Rogue = new Rogue;
			_Rogue->init("GreenRogue", { 5024 + 16,3200 + 16 }, 7, key);	//157.100

			_vRogue.push_back(_Rogue);
		}
	}
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
	for (_viGhoul = _vGhoul.begin(); _viGhoul != _vGhoul.end(); )
	{
		if ((*_viGhoul)->getIsDie())
		{
			_itemManager->dropCoin((*_viGhoul)->getBottomPosition());
			_viGhoul = _vGhoul.erase(_viGhoul);
		}
		else ++_viGhoul;
	}
	for (_viKnight = _vKnight.begin(); _viKnight != _vKnight.end(); )
	{
		if ((*_viKnight)->getIsDie())
		{
			_itemManager->dropCoin((*_viKnight)->getBottomPosition());
			_viKnight = _vKnight.erase(_viKnight);
		}
		else ++_viKnight;
	}
	for (_viMage = _vMage.begin(); _viMage != _vMage.end(); )
	{
		if ((*_viMage)->getIsDie())
		{
			_itemManager->dropCoin((*_viMage)->getBottomPosition());
			_viMage = _vMage.erase(_viMage);
		}
		else ++_viMage;
	}
	for (_viRogue = _vRogue.begin(); _viRogue != _vRogue.end(); )
	{
		if ((*_viRogue)->getIsDie())
		{
			_itemManager->dropCoin((*_viRogue)->getBottomPosition());
			_viRogue = _vRogue.erase(_viRogue);
		}
		else ++_viRogue;
	}
}