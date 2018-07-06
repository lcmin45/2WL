#include "stdafx.h"
#include "Astar.h"


Astar::Astar()
{
}


Astar::~Astar()
{
}


POINTFLOAT Astar::readyPath(POINTFLOAT bottomPosition)
{
	_vClosedList.clear();
	_vOpenList.clear();
	_vTotalList.clear();

	float tileX, tileY;

	tileX = bottomPosition.x / TILESIZE;
	tileY = bottomPosition.y / TILESIZE;

	_startTile = new tile;
	_startTile->init(tileX, tileY);
	_startTile->setAttribute("start");

	//도착 타일
	_endTile = new tile;
	_endTile->init(_playerPosition.x / TILESIZE, _playerPosition.y / TILESIZE);
	_endTile->setAttribute("end");

	_currentTile = _startTile;


	//======================================= 도움!!!!!!!!!
	//타일 정보 몇개를 넣어야 할까!?
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_vTotalList.push_back(_endTile);
				continue;
			}

			tile* node = new tile;
			node->init(j, i);
			if (_stage->getTileinfo()[i * 200 + j].objectIndex != NULL)
			{
				node->setAttribute("wall");
			}
			_vTotalList.push_back(node);
		}
	}
	//========================================== 도우우움
	pathFinder(_startTile);


	if (_vClosedList.size())
	{
		_endPosition.x = _vClosedList[_vClosedList.size() - 1]->getCenter().x;
		_endPosition.y = _vClosedList[_vClosedList.size() - 1]->getCenter().y;

		_vClosedList.clear();
		_vOpenList.clear();
		_vTotalList.clear();

		return _endPosition;
	}
	else
	{
		return bottomPosition;
	}

}

vector<tile*> Astar::addOpenList(tile * currentTile)
{

	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//맵 나오면 타일 갯수 말고 타일 인덱스 맞는 것만 넣어두기 !
			//======================================================= 수정해야함 ============================
			if (startX + j < 0 || startY + i < 0 || startX + j > TILEX - 1 || startY + i> TILEY - 1) continue;
			tile* node = _vTotalList[(startY * TILEX) + startX + j + (i * TILEX)];

			//예외처리
			//if ((i == 0 && j == 0) || (i == 2 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 2)) continue;
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;


			//현재 타일은 계속 갱신해준다
			node->setParentNode(_currentTile);

			//임의의 불값을 두고 체크를했는지 판단
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}
			
			if (!addObj) continue;

			_vOpenList.push_back(node);

		}
	}

	return _vOpenList;

}

void Astar::pathFinder(tile * currentTile)
{
	//비교하기 편하게 임의의 경로비용을 설정해두자
	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	//오픈리스트 벡터에서 가장 빠른 경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		// F = G + H
		//H
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//G
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE ? 14 : 10);

		//F = G + H
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//빠른 경로비용을 뽑자
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		_vOpenList[i]->setIsOpen(false);
	}

	if (tempTile == NULL) return;
	//도착했으면
	if (tempTile->getAttribute() == "end")
	{
		_vEndTile.clear();

		while (_currentTile->getParentNode() != NULL)
		{
			_vEndTile.push_back(_currentTile);
			_vClosedList.push_back(_currentTile);
			_currentTile = _currentTile->getParentNode();
			//_start = false;
		}

		return;
	}


	_vClosedList.push_back(tempTile);

	

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
	pathFinder(_currentTile);
}
