#pragma once
#include "gameNode.h"
#include "stage.h"
#include "mapTile.h"
#include "tile.h"
#include "mapToolNode.h"


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

	int _tileX, _tileY;
	int _tileStartX, _tileStartY;
	int _tileEndX, _tileEndY;


public:
	Astar();
	~Astar();


	//void Move();
	POINTFLOAT readyPath(POINTFLOAT bottomPosition, int monsterIndex);
	vector<tile*> addOpenList(tile * currentTile);
	void pathFinder(tile * currentTile);
	
	POINTFLOAT getEndPosition() {return _endPosition;}

	void setPlayerPositionLink(POINTFLOAT playerPosition) {	_playerPosition = playerPosition; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }

	vector<tile*> getEndTile(void) { return _vEndTile; }
	vector<tile*> getTotalTile() { return _vTotalList; }
	vector<tile*> getClose() { return _vClosedList; }
	vector<tile*> getOpen() { return _vOpenList; }
};

