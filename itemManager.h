#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class inventory;

class itemManager : public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
	inventory* _inventory;
public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPosition(const char* name, POINTFLOAT position);
	void setStatus(const char* name, STATUS status);

	void setInventoryLink(inventory* inventory) { _inventory = inventory; }
};