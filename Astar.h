#pragma once
#include "gameNode.h"
#include "stage.h"
#include "player.h"
#include "mapTile.h"

class Astar : public gameNode
{
	player* _player;
	stage* _stage;


	//��ü Ÿ���� ���� ����
	vector<mapTile*>			_vTotalList;
	vector<mapTile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ���� ����
	vector<mapTile*>			_vOpenList;
	vector<mapTile*>::iterator _viOpenList;

	//���� ���� ���� ���� ����
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

