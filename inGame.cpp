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

	return S_OK;
}

void inGame::release() {}

void inGame::update()
{
	_player->update();
}

void inGame::render()
{
	_player->render();
	_UI->render();
}