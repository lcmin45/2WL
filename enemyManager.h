#pragma once
#include "gameNode.h"
#include "monster.h"
#include "boss.h"

class enemyManager : public gameNode
{
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};