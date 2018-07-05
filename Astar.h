#pragma once
#include "gameNode.h"
#include "stage.h"
#include "player.h"
#include "mapTile.h"

class Astar : public gameNode
{
	player* _player;
	stage* _stage;


	//전체 타일을 담을 벡터
	vector<mapTile*>			_vTotalList;
	vector<mapTile*>::iterator _viTotalList;

	//갈 수 있는 길을 담은 벡터
	vector<mapTile*>			_vOpenList;
	vector<mapTile*>::iterator _viOpenList;

	//가장 빠른 길이 담기는 벡터
	vector<mapTile*>			_vClosedList;
	vector<mapTile*>::iterator _viClosedList;

	mapTile* _startTile;
	mapTile* _endTile;
	mapTile* _currentTile;


	POINTFLOAT _endPosition;

public:
	Astar();
	~Astar();


	//void Move();
	void readyPath(RECT _bottomRC);
	vector<mapTile*> addOpenList(mapTile * currentTile);
	void pathFinder(mapTile * currentTile);



	POINTFLOAT getEndPosition() {return _endPosition;}

	void setPlayerMemoryAdressLink(player* player) { _player = player; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }
};

