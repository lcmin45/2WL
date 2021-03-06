#include "stdafx.h"
#include "inGame.h"

inGame::inGame() {}
inGame::~inGame() {}

HRESULT inGame::init()
{
	_stage = new stage;
	_stage->init();
	_stage->stageLoad(1);

	_UI = new UI;
	_UI->init();

	_player = new player;
	_player->init();

	_itemManager = new itemManager;
	_itemManager->init();
	_itemManager->setStoreItem();

	_ptM = new projectileManager;
	_ptM->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_Astar = new Astar;

	_UI->setPlayerAddressLink(_player);
	_UI->setProjectileManagerAddressLink(_ptM);
	_player->setTileAddressLink(_stage->getTileinfo());
	_player->setItemManagerAddressLink(_itemManager);
	_player->setProjectileManagerAddressLink(_ptM);
	_itemManager->setPlayerAddressLink(_player);
	_enemyManager->setProjectileManagerAddressLink(_ptM);
	_enemyManager->setItemManagerLink(_itemManager);
	_ptM->setPlayerAddressLink(_player);
	_ptM->setTileAddressLink(_stage->getTileinfo());
	_stage->setPlayerMemoryAdressLink(_player);
	_Astar->setStageMemoryAdressLink(_stage);
	_player->setEnemyManagerAddressLink(_enemyManager);

	_BlackAalpha = 255;

	_saveAndLoad = new saveAndLoad;
	_saveAndLoad->init();

	_player->update();

	saveData();

	return S_OK;
}

HRESULT inGame::init(void * obj)
{
	tagSaveInfo* temp = (tagSaveInfo*)obj;

	_stage = new stage;
	_stage->init();
	_stage->stageLoad(1);

	_UI = new UI;
	_UI->init();

	_player = new player;
	_player->init();
	_player->setSaveInfo(temp->playerPosition, temp->currnetHp, temp->coin);
	for (int i = 0; i < 7; i++)
	{
		_player->getSkillSet()->setSettingSkill(temp->skillSet[i], i);
	}

	_itemManager = new itemManager;
	_itemManager->init();
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		if (temp->itemStatus[i] == ON_FIELD) { _itemManager->getVItem()[i]->setPosition(temp->itemPosition[i]); _itemManager->getVItem()[i]->setStatus(ON_FIELD); }
		else if (temp->itemStatus[i] == IN_INVENTORY) _itemManager->addItemToInventory(_itemManager->getVItem()[i]);
		else if (temp->itemStatus[i] == IN_STORE) _itemManager->addItemToStore(_itemManager->getVItem()[i]);
		else { _itemManager->getVItem()[i]->setPosition({ 0, 0 });  _itemManager->getVItem()[i]->setStatus(NOWHERE); }
	}

	_ptM = new projectileManager;
	_ptM->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();
	_enemyManager->setBossDead(temp->bossDead[0], temp->bossDead[1], temp->bossDead[2]);
	_enemyManager->setAlreadyDrop(temp->bossDead[0], temp->bossDead[1], temp->bossDead[2]);

	_Astar = new Astar;

	_UI->setPlayerAddressLink(_player);
	_UI->setProjectileManagerAddressLink(_ptM);
	_player->setTileAddressLink(_stage->getTileinfo());
	_player->setItemManagerAddressLink(_itemManager);
	_player->setProjectileManagerAddressLink(_ptM);
	_itemManager->setPlayerAddressLink(_player);
	_enemyManager->setProjectileManagerAddressLink(_ptM);
	_enemyManager->setItemManagerLink(_itemManager);
	_ptM->setPlayerAddressLink(_player);
	_stage->setPlayerMemoryAdressLink(_player);
	_Astar->setStageMemoryAdressLink(_stage);
	_player->setEnemyManagerAddressLink(_enemyManager);

	_BlackAalpha = 255;

	_saveAndLoad = new saveAndLoad;
	_saveAndLoad->init();

	_player->update();

	saveData();

	return S_OK;
}

void inGame::release()
{
	_enemyManager->release();
	_itemManager->release();
	SAFE_DELETE(_UI);
	SAFE_DELETE(_player);
	SAFE_DELETE(_itemManager);
	SAFE_DELETE(_ptM);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_stage);
	SAFE_DELETE(_Astar);
}

void inGame::update()
{
	if (_enemyManager->getFireBoss()->getFireBossDie() && _enemyManager->getIceBoss()->getIceBossDie() && _enemyManager->getWoodBoss()->getWoodBossDie())
	{
		SCENEMANAGER->changeScene("ending");
		CAMERAMANAGER->setCameraPoint({ 0, 0 });
	}
	else if (_player->getIsDead())
	{
		if (_BlackAalpha < 255) _BlackAalpha += 3;
		else
		{
			SCENEMANAGER->changeScene("intro");
			CAMERAMANAGER->setCameraPoint({ 0, 0 });
		}
	}
	else if (_BlackAalpha > 0) _BlackAalpha -= 3;
	else
	{
		collide();
		updateEffect();

		_UI->update();
		_itemManager->update();
		_ptM->update();
		_stage->update();			//플레이어 업데이트 여기 안에 있음!
		_enemyManager->update();

		_enemyManager->setStage(_stage);
		_enemyManager->setPlayerPoint(_player->getPosition());
		_enemyManager->setPlayerIndex(_player->getPlayerIndex());
		//_Astar->setPlayerPositionLink(_player->getPosition());
		_UI->update();
		if (_enemyManager->getSaveNow()) saveData();
	}
	KEYANIMANAGER->update();
}

void inGame::render()
{
	_stage->render();			//플레이어 렌더 여기 안에 있음!
	_enemyManager->render();
	_itemManager->render();
	_ptM->render();
	_UI->render();
	drawEffect();
}

void inGame::saveData()
{
	tagSaveInfo* temp = new tagSaveInfo;
	temp->playerPosition = _player->getPosition();
	temp->currnetHp = _player->getCurrentHp();
	temp->coin = _player->getCoin();

	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		temp->itemStatus[i] = _itemManager->getVItem()[i]->getStatus();
		temp->itemPosition[i] = _itemManager->getVItem()[i]->getPosition();
	}
	for (int i = 0; i < 7; i++)
	{
		temp->skillSet[i] = _player->getSkillSet()->getSettingSkill()[i];
	}
	temp->bossDead[0] = _enemyManager->getFireBoss()->getFireBossDie();
	temp->bossDead[1] = _enemyManager->getIceBoss()->getIceBossDie();
	temp->bossDead[2] = _enemyManager->getWoodBoss()->getWoodBossDie();

	_saveAndLoad->save(temp);
}

void inGame::collide()
{

	//================================= 에너미랑 플레이어 스킬 충돌체크 ============================
	for (int i = 0; i < _enemyManager->getVGhoul().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_enemyManager->getVGhoul()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getRect())
				&& _enemyManager->getVGhoul()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getVGhoul()[i]->HitMotion();
				_enemyManager->getVGhoul()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
			}
		}
	}
	for (int i = 0; i < _enemyManager->getVGhoul().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_enemyManager->getVGhoul()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getsRect()[h])
					&& _enemyManager->getVGhoul()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getVGhoul()[i]->HitMotion();
					_enemyManager->getVGhoul()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
				}
			}
		}
	}
	//=========================================================================================================================
	for (int i = 0; i < _enemyManager->getVKnight().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_enemyManager->getVKnight()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getRect())
				&& _enemyManager->getVKnight()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getVKnight()[i]->HitMotion();
				_enemyManager->getVKnight()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
			}
		}
	}
	for (int i = 0; i < _enemyManager->getVKnight().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_enemyManager->getVKnight()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getsRect()[h])
					&& _enemyManager->getVKnight()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getVKnight()[i]->HitMotion();
					_enemyManager->getVKnight()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
				}
			}
		}
	}
	//=========================================================================================================================


	for (int i = 0; i < _enemyManager->getVMage().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_enemyManager->getVMage()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getRect())
				&& _enemyManager->getVMage()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getVMage()[i]->HitMotion();
				_enemyManager->getVMage()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
			}
		}
	}
	for (int i = 0; i < _enemyManager->getVMage().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_enemyManager->getVMage()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getsRect()[h])
					&& _enemyManager->getVMage()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getVMage()[i]->HitMotion();
					_enemyManager->getVMage()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
				}
			}
		}
	}
	//=========================================================================================================================
	for (int i = 0; i < _enemyManager->getVRogue().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_enemyManager->getVRogue()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getRect())
				&& _enemyManager->getVRogue()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getVRogue()[i]->HitMotion();
				_enemyManager->getVRogue()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
			}
		}
	}
	for (int i = 0; i < _enemyManager->getVRogue().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_enemyManager->getVRogue()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getsRect()[h])
					&& _enemyManager->getVRogue()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getVRogue()[i]->HitMotion();
					_enemyManager->getVRogue()[i]->HitHP(_ptM->getVSkill()[j]->getSkillDamage(), _ptM->getVSkill()[j]->getSkillAngle());
				}
			}
		}
	}
	//=========================================================================================================================
	for (int i = 0; i < _enemyManager->getVScarecrow().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_enemyManager->getVScarecrow()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getRect()) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getVScarecrow()[i]->HitMotion();
			}
		}
	}
	for (int i = 0; i < _enemyManager->getVScarecrow().size(); ++i)
	{
		for (int j = 0; j < _ptM->getVSkill().size(); ++j)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_enemyManager->getVScarecrow()[i]->getMonsterRC(), &_ptM->getVSkill()[j]->getsRect()[h])
					&& _enemyManager->getVScarecrow()[i]->getForm() == BATTLE && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getVScarecrow()[i]->HitMotion();
				}
			}
		}
	}
	//================================= 보스랑 플레이어 스킬 충돌체크 ============================

	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getFireBoss()->getFireDialogue() == false)
		{
			if (IntersectRect(&temp, &_enemyManager->getFireBoss()->getbossRect(), &_ptM->getVSkill()[j]->getRect()) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getFireBoss()->setFireBossHit(_ptM->getVSkill()[j]->getSkillDamage());
				if (_enemyManager->getFireBoss()->getbossimage() == IMAGEMANAGER->findImage("불등장"))
				{
					_enemyManager->getFireBoss()->setbossimage(IMAGEMANAGER->findImage("불피격"));
					SOUNDMANAGER->play("firebossHurt");
				}
			}
		}
	}
	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getFireBoss()->getFireDialogue() == false)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				if (IntersectRect(&temp, &_enemyManager->getFireBoss()->getbossRect(), &_ptM->getVSkill()[j]->getsRect()[h]) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getFireBoss()->setFireBossHit(_ptM->getVSkill()[j]->getSkillDamage());
					if (_enemyManager->getFireBoss()->getbossimage() == IMAGEMANAGER->findImage("불등장"))
					{
						_enemyManager->getFireBoss()->setbossimage(IMAGEMANAGER->findImage("불피격"));
						SOUNDMANAGER->play("firebossHurt");
					}
				}
			}
		}
	}


	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getIceBoss()->getIceDialogue() == false)
		{
			if (IntersectRect(&temp, &_enemyManager->getIceBoss()->getbossRect(), &_ptM->getVSkill()[j]->getRect()) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getIceBoss()->setIceBossHit(_ptM->getVSkill()[j]->getSkillDamage());
				if (_enemyManager->getIceBoss()->getbossimage() == IMAGEMANAGER->findImage("얼음등장"))
				{
					_enemyManager->getIceBoss()->setbossimage(IMAGEMANAGER->findImage("얼음피격"));
					SOUNDMANAGER->play("icebossHurt");
				}
			}
		}
	}
	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getIceBoss()->getIceDialogue() == false)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				if (IntersectRect(&temp, &_enemyManager->getIceBoss()->getbossRect(), &_ptM->getVSkill()[j]->getsRect()[h]) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getIceBoss()->setIceBossHit(_ptM->getVSkill()[j]->getSkillDamage());
					if (_enemyManager->getIceBoss()->getbossimage() == IMAGEMANAGER->findImage("얼음등장"))
					{
						_enemyManager->getIceBoss()->setbossimage(IMAGEMANAGER->findImage("얼음피격"));
						SOUNDMANAGER->play("icebossHurt");
					}
				}
			}
		}
	}


	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getWoodBoss()->getWoodDialogue() == false)
		{
			if (IntersectRect(&temp, &_enemyManager->getWoodBoss()->getbossRect(), &_ptM->getVSkill()[j]->getRect()) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
			{
				createEffect(temp);
				_enemyManager->getWoodBoss()->setWoodBossHit(_ptM->getVSkill()[j]->getSkillDamage());
				if (_enemyManager->getWoodBoss()->getbossimage() == IMAGEMANAGER->findImage("나무등장"))
				{
					_enemyManager->getWoodBoss()->setbossimage(IMAGEMANAGER->findImage("나무오른쪽피격"));
					SOUNDMANAGER->play("woodbossHurt");
				}
			}
		}
	}
	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (_enemyManager->getWoodBoss()->getWoodDialogue() == false)
		{
			for (int h = 0; h < MAXPARTICLE; h++)
			{
				if (IntersectRect(&temp, &_enemyManager->getWoodBoss()->getbossRect(), &_ptM->getVSkill()[j]->getsRect()[h]) && _ptM->getVSkill()[j]->getSubject() == PLAYER)
				{
					createEffect(temp);
					_enemyManager->getWoodBoss()->setWoodBossHit(_ptM->getVSkill()[j]->getSkillDamage());
					if (_enemyManager->getWoodBoss()->getbossimage() == IMAGEMANAGER->findImage("나무등장"))
					{
						_enemyManager->getWoodBoss()->setbossimage(IMAGEMANAGER->findImage("나무오른쪽피격"));
						SOUNDMANAGER->play("woodbossHurt");
					}
				}
			}
		}
	}

	if (_enemyManager->getFireBoss()->getbossimage() == IMAGEMANAGER->findImage("불피격"))
	{
		++_count;
		if ((_count % 5 == 0) && (_enemyManager->getFireBoss()->getbossimage() == IMAGEMANAGER->findImage("불피격")))
		{
			_enemyManager->getFireBoss()->setbossimage(IMAGEMANAGER->findImage("불등장"));
		}
	}

	else if (_enemyManager->getIceBoss()->getbossimage() == IMAGEMANAGER->findImage("얼음피격"))
	{
		++_count;
		if ((_count % 5 == 0) && (_enemyManager->getIceBoss()->getbossimage() == IMAGEMANAGER->findImage("얼음피격")))
		{
			_enemyManager->getIceBoss()->setbossimage(IMAGEMANAGER->findImage("얼음등장"));
		}
	}

	else if (_enemyManager->getWoodBoss()->getbossimage() == IMAGEMANAGER->findImage("나무오른쪽피격"))
	{
		++_count;
		if ((_count % 5 == 0) && (_enemyManager->getWoodBoss()->getbossimage() == IMAGEMANAGER->findImage("나무오른쪽피격")))
		{
			_enemyManager->getWoodBoss()->setbossimage(IMAGEMANAGER->findImage("나무등장"));
		}
	}

	//================================= 플레이어랑 적 스킬 충돌체크 ============================
	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getBody(), &_ptM->getVSkill()[j]->getRect()) && _ptM->getVSkill()[j]->getSubject() == ENEMY)
		{
			createEffect(temp);
			_player->setPlayerHit(_ptM->getVSkill()[j]->getSkillDamage());
		}
	}

	for (int j = 0; j < _ptM->getVSkill().size(); ++j)
	{
		for (int h = 0; h < _ptM->getVSkill()[j]->getVWoodSkill().size(); ++h)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getBody(), &_ptM->getVSkill()[j]->getVWoodSkill()[h]->rc))
			{
				createEffect(temp);
				_player->setPlayerHit(_ptM->getVSkill()[j]->getSkillDamage());
			}
		}

		for (int h = 0; h < _ptM->getVSkill()[j]->getVHail().size(); ++h)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getBody(), &_ptM->getVSkill()[j]->getVHail()[h]->rc))
			{
				createEffect(temp);
				_player->setPlayerHit(_ptM->getVSkill()[j]->getSkillDamage());
			}
		}

		for (int h = 0; h < _ptM->getVSkill()[j]->getVIceThrow().size(); ++h)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getBody(), &_ptM->getVSkill()[j]->getVIceThrow()[h]->getRect()))
			{
				createEffect(temp);
				_player->setPlayerHit(_ptM->getVSkill()[j]->getSkillDamage());
			}
		}
		// 메테오 오지게 아픔 떨어질떄 판정
		for (int h = 0; h < _ptM->getVSkill()[j]->getVMeteor().size(); ++h)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getBody(), &_ptM->getVSkill()[j]->getVMeteor()[h]->rc)
				&& _ptM->getVSkill()[j]->getVMeteor()[h]->img == IMAGEMANAGER->findImage("메테오효과"))
			{
				createEffect(temp);
				_player->setPlayerHit(_ptM->getVSkill()[j]->getSkillDamage());
			}
		}
	}

}

void inGame::createEffect(RECT rect)
{
	HITEFFECT* effect = new HITEFFECT;
	effect->img = IMAGEMANAGER->findImage("효과");
	effect->pt = { (rect.left + (rect.right - rect.left) / 2) + RND->getFromIntTo(-5,5), (rect.top + (rect.bottom - rect.top) / 2) + RND->getFromIntTo(-5,5) };
	effect->rc = RectMakeCenter(effect->pt.x, effect->pt.y, effect->img->getFrameWidth(), effect->img->getFrameHeight());
	effect->frameIndex = 0;
	vEffect.push_back(effect);
}

void inGame::updateEffect()
{
	for (viEffect = vEffect.begin(); viEffect != vEffect.end();)
	{
		(*viEffect)->frameIndex++;

		if ((*viEffect)->img->getMaxFrameX() < (*viEffect)->frameIndex) viEffect = vEffect.erase(viEffect);
		else viEffect++;
	}
}

void inGame::drawEffect()
{
	for (viEffect = vEffect.begin(); viEffect != vEffect.end(); viEffect++)
	{
		(*viEffect)->img->frameRender(getMemDC(), (*viEffect)->rc.left, (*viEffect)->rc.top, (*viEffect)->frameIndex, 0);
	}
}
