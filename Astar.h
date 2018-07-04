#pragma once
#include "stage.h"
#include "player.h"

class Astar
{
	player* _player;
	stage* _stage;

public:
	Astar();
	~Astar();




	void setPlayerMemoryAdressLink(player* player) { _player = player; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }
};

