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
	_ptM->init();


	_enemyManager = new enemyManager;
	_enemyManager->init();


	_Astar = new Astar;
	_Astar->setPlayerMemoryAdressLink(_player);
	_Astar->setStageMemoryAdressLink(_stage);


	_player->setItemManagerAddressLink(_itemManager);
	_player->setProjectileManagerAddressLink(_ptM);
	_itemManager->setPlayerAddressLink(_player);
	_ptM->setPlayerAddressLink(_player);

	_stage->setPlayerMemoryAdressLink(_player);

	return S_OK;
}

void inGame::release() {}

void inGame::update()
{
	//_player->update();
	_itemManager->update();
	_ptM->update();
	_enemyManager->update();
	_stage->update();			//�÷��̾� ������Ʈ ���� �ȿ� ����!
}

void inGame::render()
{
	_stage->render();			//�÷��̾� ���� ���� �ȿ� ����!
	_enemyManager->render();
	//_player->render();
	_itemManager->render();
	_ptM->render();
	_UI->render();
}