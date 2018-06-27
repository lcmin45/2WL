#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "scenePart.h"
#include "player.h"
#include "store.h"

class inGame : public gameNode
{
public:
	inGame();
	~inGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};