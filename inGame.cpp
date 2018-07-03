#include "stdafx.h"
#include "inGame.h"

inGame::inGame() {}
inGame::~inGame() {}

HRESULT inGame::init()
{
	_UI = new UI;
	_UI->init();

	_player = new player;
	_player->init();

	_itemManager = new itemManager;
	_itemManager->init();

	_ptM = new projectileManager;
	_ptM->init();

	_player->setProjectileManagerAddressLink(_ptM);
	_itemManager->setInventoryLink(_player->getInventory());
	_ptM->setPlayerAddressLink(_player);

	return S_OK;
}

void inGame::release() {}

void inGame::update()
{
	_player->update();
	_itemManager->update();
	_ptM->update();
}

void inGame::render()
{
	_player->render();
	_itemManager->render();
	_ptM->render();
	_UI->render();
}