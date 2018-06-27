#pragma once
#include "gameNode.h"

class mapTool : public gameNode
{
public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};