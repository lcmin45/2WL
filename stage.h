#pragma once
#include "gameNode.h"
#include "inGame.h"

class stage : public gameNode
{
public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};