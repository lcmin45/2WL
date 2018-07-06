#pragma once
#include "gameNode.h"
#include "stage.h"
#include "mapTile.h"
#include "tile.h"
#include "mapToolNode.h"

//================= �ӽ� ������ ���� ================
#define TILEX 30
#define TILEY 30


class Astar : public gameNode
{

	vector<tile*>		_vEndTile;

	//��ü Ÿ���� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ���� ����
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

