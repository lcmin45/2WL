#pragma once
#include "gameNode.h"
#include "skill.h"
#include "inventory.h"

class player : public gameNode  
{
private:
	//수우왔다감요
	inventory * _inventory;
public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};