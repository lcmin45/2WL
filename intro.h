#pragma once
#include "gameNode.h"

class intro : public gameNode
{
public:
	intro();
	~intro();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};