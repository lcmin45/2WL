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
	_woodposition.x = 5376;
	_woodposition.y = 304;
	_iceposition.x = 656;
	_iceposition.y = 464;
	_fireposition.x = 624;
	_fireposition.y = 4224;

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
	_woodBoss->setPlayerPoint(_playerPoint);
	_woodBoss->update();
	_woodBoss->woodMove();
	_woodBoss->woodSkill();
	//���� �߰��ϱ�
	_iceBoss->update();
	_iceBoss->iceMove();
	_iceBoss->iceSkill();
	_iceBoss->setPlayerPoint(_playerPoint);
	_iceBoss->setProjectileAddressLink(_PM);
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
	for (float i = 0; i < 1; ++i)
	{
		Ghoul* _ghoul;
		_ghoul = new Ghoul;
		_ghoul->init({ 128 + i * 128,128 }, i,1);

		_vGhoul.push_back(_ghoul);
	}
	for (float i = 0; i < 1; ++i)
	{
		Knight* _Knight;
		_Knight = new Knight;
		_Knight->init("BlueKnight", { 128 + i * 128,128*2 }, i,2);
		_vKnight.push_back(_Knight);
	}

	for (float i = 0; i < 1; ++i)
	{
		Mage* _Mage;
		_Mage = new Mage;
		_Mage->init("RedMage", { 128 + i * 128,128*3 }, i, 3);

		_vMage.push_back(_Mage);
	}

	for (float i = 0; i < 1; ++i)
	{
		Rogue* _Rogue;
		_Rogue = new Rogue;
		_Rogue->init("GreenRogue", { 128 + i * 128,128 * 4 }, i,4);

		_vRogue.push_back(_Rogue);
	}

	for (float i = 0; i < 1; ++i)
	{
		Scarecrow* _Scarecrow;
		_Scarecrow = new Scarecrow;
		_Scarecrow->init({ 128 + i * 128,128 * 5 });

		_vScarecrow.push_back(_Scarecrow);
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
