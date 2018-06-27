#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class store : public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
public:
	store();
	~store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};