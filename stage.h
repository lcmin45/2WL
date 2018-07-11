#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class player;

class stage : public gameNode
{
private:
	image * _stage1;
	image * _image;

	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];
	int		_stage;
	player* _player;

	image * _potal[6];
	RECT _potalRc[6];
	int _potalCount;
	int _potalIndex;

public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void stageLoad(int stage);
	void warp();           //Æ÷Å» ÀÌµ¿

	tagMapToolTile* getTileinfo() { return _tile; }
	void setPlayerMemoryAdressLink(player* player) { _player = player; }
};