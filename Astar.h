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

	tile* _startTile;				//��� Ÿ��
	tile* _endTile;					//���� Ÿ��
	tile* _currentTile;				//���� Ÿ��


	stage* _stage;					//�������� ����
	POINTFLOAT _endPosition;		//���� ��ǥ
	POINTFLOAT _playerPosition;		//�÷��̾� ��ǥ

	int _tileX, _tileY;				//A* �� �̵��� �� ���� 
	int _tileStartX, _tileStartY;	//A* �� �ε��� ����Ÿ��
	int _tileEndX, _tileEndY;		//A* �� �ε��� ������ Ÿ��


public:
	Astar();
	~Astar();


	//void Move();
	POINTFLOAT readyPath(POINTFLOAT bottomPosition, int monsterIndex);			//��ã�� �Լ�
	vector<tile*> addOpenList(tile * currentTile);								//���� �����ִ� Ÿ���� ����
	void pathFinder(tile * currentTile);										//���� ã�´�.
	
	POINTFLOAT getEndPosition() {return _endPosition;}							//���Ϳ��� �Ѱ��� ��ǥ

	void setPlayerPositionLink(POINTFLOAT playerPosition) {	_playerPosition = playerPosition; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }

	vector<tile*> getEndTile(void) { return _vEndTile; }
	vector<tile*> getTotalTile() { return _vTotalList; }
	vector<tile*> getClose() { return _vClosedList; }
	vector<tile*> getOpen() { return _vOpenList; }
};

