#pragma once
#include "gameNode.h"

class monster : public gameNode
{
public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};