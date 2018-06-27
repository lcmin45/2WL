#pragma once
#include "gameNode.h"
#include "item.h"

class itemManager : public gameNode
{
public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};