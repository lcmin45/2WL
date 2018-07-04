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

	bool  isCheck;

public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void stageLoad(int stage);

	void setPlayerMemoryAdressLink(player* player) { _player = player; }
};