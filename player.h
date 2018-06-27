#pragma once
#include "gameNode.h"
#include "skill.h"
#include "inventory.h"

class player : public gameNode
{
private:
	inventory * _inventory;
public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};