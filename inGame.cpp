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

	_ptM = new projectileManager;
	_ptM->init();

	_ptM->setPlayerAddressLink(_player);
	_player->setProjectileManagerAddressLink(_ptM);

	return S_OK;
}

void inGame::release() {}

void inGame::update()
{
	_player->update();
	_ptM->update();
}

void inGame::render()
{
	_player->render();
	_UI->render();
	_ptM->render();
}