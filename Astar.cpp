#include "stdafx.h"
#include "Astar.h"


Astar::Astar()
{
}


Astar::~Astar()
{
}

//void Astar::readyPath(RECT _bottomRC)
//{
//
//	_vClosedList.clear();
//	_vOpenList.clear();
//	_vTotalList.clear();
//
//	float tileX, tileY;
//	RECT _rc;
//
//	_rc = _bottomRC;
//	tileX = _rc.left / TILESIZE;
//	tileY = _rc.top / TILESIZE;
//
//	_startTile = new mapTile;
//	_startTile->init(tileX, tileY);
//	_startTile->setAttribute("start");
//
//	//µµÂø Å¸ÀÏ
//	_player->getPosition().x
//	_endTile = new mapTile;
//	_endTile->init(_player->getPosition().x / TILESIZE, _player->getPosition().y / TILESIZE);
//	_endTile->setAttribute("end");
//
//	_currentTile = _startTile;
//
//
//	for (int i = 0; i < TILEY; ++i)
//	{
//		for (int j = 0; j < TILEX; ++j)
//		{
//			if (j == _startTile->getIdX() && i == _startTile->getIdY())
//			{
//				_startTile->setColor(RGB(0, 255, 255));
//				_vTotalList.push_back(_startTile);
//				continue;
//			}
//			if (j == _endTile->getIdX() && i == _endTile->getIdY())
//			{
//				_endTile->setColor(RGB(10, 120, 55));
//				_vTotalList.push_back(_endTile);
//				continue;
//			}
//
//			mapTile* node = new mapTile;
//			node->init(j, i);
//			if (_pacmanMap->getAttribute()[i*TILEX + j] == ATTR_UNMOVE)
//			{
//				node->setAttribute("wall");
//			}
//			_vTotalList.push_back(node);
//		}
//	}
//
//	pathFinder(_startTile);
//
//	if (_vClosedList.size())
//	{
//		//_endX = _vClosedList[_vClosedList.size() - 1]->getRect().left;
//		//_endY = _vClosedList[_vClosedList.size() - 1]->getRect().top ;
//		_endX = _vClosedList[_vClosedList.size() - 1]->getCenter().x;
//		_endY = _vClosedList[_vClosedList.size() - 1]->getCenter().y;
//	}
//
//}
//
//vector<mapTile*> Astar::addOpenList(mapTile * currentTile)
//{
//	return vector<mapTile*>();
//}
//
//void Astar::pathFinder(mapTile * currentTile)
//{
//}
