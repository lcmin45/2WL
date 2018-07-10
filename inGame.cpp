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


	_enemyManager = new enemyManager;
	_enemyManager->init();


	_Astar = new Astar;

	_UI->setPlayerAddressLink(_player);
	_player->setTileAddressLink(_stage->getTileinfo());
	_player->setItemManagerAddressLink(_itemManager);
	_player->setProjectileManagerAddressLink(_ptM);
	_enemyManager->setProjectileManagerAddressLink(_ptM);
	_itemManager->setPlayerAddressLink(_player);
	_ptM->setPlayerAddressLink(_player);
	_stage->setPlayerMemoryAdressLink(_player);
	_Astar->setStageMemoryAdressLink(_stage);

	_BlackAalpha = 255;

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

	_itemManager = new itemManager;
	_itemManager->init();
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		if (temp->status[i] == ON_FIELD) { _itemManager->getVItem()[i]->setPosition(temp->itemPosition[i]); _itemManager->getVItem()[i]->setStatus(ON_FIELD); }
		else if (temp->status[i] == IN_INVENTORY) _itemManager->addItemToInventory(_itemManager->getVItem()[i]);
		else if (temp->status[i] == IN_STORE) _itemManager->addItemToStore(_itemManager->getVItem()[i]);
		else { _itemManager->getVItem()[i]->setPosition({ 0, 0 });  _itemManager->getVItem()[i]->setStatus(NOWHERE); }
	}

	_ptM = new projectileManager;

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_Astar = new Astar;

	_UI->setPlayerAddressLink(_player);
	_player->setTileAddressLink(_stage->getTileinfo());
	_player->setItemManagerAddressLink(_itemManager);
	_player->setProjectileManagerAddressLink(_ptM);
	_enemyManager->setProjectileManagerAddressLink(_ptM);
	_itemManager->setPlayerAddressLink(_player);
	_ptM->setPlayerAddressLink(_player);
	_stage->setPlayerMemoryAdressLink(_player);
	_Astar->setStageMemoryAdressLink(_stage);

	_BlackAalpha = 255;

	return S_OK;
}

void inGame::release()
{
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
	if (_player->getIsDead())
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
		_UI->update();
		_itemManager->update();
		_ptM->update();
		_enemyManager->update();
		_stage->update();			//플레이어 업데이트 여기 안에 있음!

		_enemyManager->setStage(_stage);
		_enemyManager->setPlayerPoint(_player->getPosition());
		//==========================플레이어 인덱스 정보 필요함!!!!!!!!!!!!!
		//_enemyManager->setPlayerIndex(20);
		_enemyManager->setPlayerIndex(_player->getPlayerIndex());
		_Astar->setPlayerPositionLink(_player->getPosition());
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
}