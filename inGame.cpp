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


	return S_OK;
}

void inGame::release() {}

void inGame::update()
{



	_UI->update();
	_itemManager->update();
	_ptM->update();
	_enemyManager->update();
	_stage->update();			//�÷��̾� ������Ʈ ���� �ȿ� ����!


	_enemyManager->setStage(_stage);
	_enemyManager->setPlayerPoint(_player->getPosition());
	//==========================�÷��̾� �ε��� ���� �ʿ���!!!!!!!!!!!!!
	_enemyManager->setPlayerIndex(4);
	_Astar->setPlayerPositionLink(_player->getPosition());

	KEYANIMANAGER->update();
}

void inGame::render()
{
	_stage->render();			//�÷��̾� ���� ���� �ȿ� ����!
	_enemyManager->render();
	_itemManager->render();
	_ptM->render();
	_UI->render();
}