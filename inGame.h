#pragma once
#include "gameNode.h"
#include "projectileManager.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "scenePart.h"
#include "player.h"
#include "store.h"
#include "UI.h"
#include "stage.h"
#include "Astar.h"

class inGame : public gameNode
{
private:
	UI * _UI;
	player* _player;
	itemManager* _itemManager;
	projectileManager* _ptM;
	enemyManager* _enemyManager;
	stage * _stage;
	Astar* _Astar;

public:
	inGame();
	~inGame();

	HRESULT init();
	HRESULT init(void* obj);
	void release();
	void update();
	void render();

	void collide();

};