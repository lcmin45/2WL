#include "stdafx.h"
#include "inGame.h"

inGame::inGame() {}
inGame::~inGame() {}

HRESULT inGame::init()
{
	_player = new player;
	_player->init();

	_itemManager = new itemManager;
	_itemManager->init();
	_itemManager->setInventoryLink(_player->getInventory());

	_UI = new UI;
	_UI->init();

	return S_OK;
}

void inGame::release() {}

void inGame::update()
{
	_player->update();
	_itemManager->update();
}

void inGame::render()
{
	_player->render();
	_itemManager->render();
	_UI->render();
}