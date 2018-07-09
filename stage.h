#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class player;

class stage : public gameNode
{
private:
	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];
	int		_stage;
	player* _player;

public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void stageLoad(int stage);

	tagMapToolTile* getTile() { return _tile; }

	void setPlayerMemoryAdressLink(player* player) { _player = player; }
};