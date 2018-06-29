#pragma once
#include "gameNode.h"
#include "tileNode.h"


class mapTool : public gameNode
{
private:
	tagTile _tileMap;
	tagTile _currentTile;

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};