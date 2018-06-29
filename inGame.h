#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "scenePart.h"
#include "player.h"
#include "store.h"
#include "UI.h"

class inGame : public gameNode
{
private:
	UI * _UI;
	player* _player;
public:
	inGame();
	~inGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};