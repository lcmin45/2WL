#pragma once
#include "gameNode.h"
#include "stage.h"
#include "mapTile.h"
#include "tile.h"
#include "mapToolNode.h"

//================= 임시 디파일 길이 ================
#define TILEX 30
#define TILEY 30


class Astar : public gameNode
{

	vector<tile*>		_vEndTile;

	//전체 타일을 담을 벡터
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 길을 담은 벡터
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 빠른 길이 담기는 벡터
	vector<tile*>			_vClosedList;
	vector<tile*>::iterator _viClosedList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;


	stage* _stage;
	POINTFLOAT _endPosition;
	POINTFLOAT _playerPosition;

	//bool _start;

public:
	Astar();
	~Astar();


	//void Move();
	POINTFLOAT readyPath(POINTFLOAT bottomPosition);
	vector<tile*> addOpenList(tile * currentTile);
	void pathFinder(tile * currentTile);
	
	POINTFLOAT getEndPosition() {return _endPosition;}

	void setPlayerPositionLink(POINTFLOAT playerPosition) {	_playerPosition = playerPosition; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }
};

