#include "stdafx.h"
#include "player.h"

player::player() {}
player::~player() {}

HRESULT player::init()
{
	_inventory = new inventory;
	_inventory->init();

	return S_OK;
}

void player::release() {}

void player::update()
{

}

void player::render()
{

}