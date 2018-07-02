#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "scenePart.h"
#include "player.h"
#include "UI.h"

class inGame : public gameNode
{
private:
	player * _player;
	itemManager* _itemManager;
	UI * _UI;
public:
	inGame();
	~inGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};