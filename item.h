#pragma once
#include "gameNode.h"

class item : public gameNode
{
public:
	item();
	~item();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};