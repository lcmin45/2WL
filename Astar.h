#pragma once
#include "gameNode.h"
#include "stage.h"
#include "mapTile.h"
#include "tile.h"
#include "mapToolNode.h"


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

	tile* _startTile;				//출발 타일
	tile* _endTile;					//도착 타일
	tile* _currentTile;				//현재 타일


	stage* _stage;					//스테이지 정보
	POINTFLOAT _endPosition;		//도착 좌표
	POINTFLOAT _playerPosition;		//플레이어 좌표

	int _tileX, _tileY;				//A* 로 이동할 방 갯수 
	int _tileStartX, _tileStartY;	//A* 방 인덱스 시작타일
	int _tileEndX, _tileEndY;		//A* 방 인덱스 끝나는 타일


public:
	Astar();
	~Astar();


	//void Move();
	POINTFLOAT readyPath(POINTFLOAT bottomPosition, int monsterIndex);			//길찾는 함수
	vector<tile*> addOpenList(tile * currentTile);								//현재 갈수있는 타일을 넣음
	void pathFinder(tile * currentTile);										//길을 찾는다.
	
	POINTFLOAT getEndPosition() {return _endPosition;}							//몬스터에게 넘겨줄 좌표

	void setPlayerPositionLink(POINTFLOAT playerPosition) {	_playerPosition = playerPosition; }
	void setStageMemoryAdressLink(stage* stage) { _stage = stage; }

	vector<tile*> getEndTile(void) { return _vEndTile; }
	vector<tile*> getTotalTile() { return _vTotalList; }
	vector<tile*> getClose() { return _vClosedList; }
	vector<tile*> getOpen() { return _vOpenList; }
};

