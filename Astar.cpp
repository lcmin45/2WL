#include "stdafx.h"
#include "Astar.h"


Astar::Astar()
{
}


Astar::~Astar()
{
}


POINTFLOAT Astar::readyPath(POINTFLOAT bottomPosition, int monsterIndex)
{
	_vClosedList.clear();
	_vOpenList.clear();
	_vTotalList.clear();
	_vEndTile.clear();

	float tileX, tileY;

	tileX = (int)(bottomPosition.x / TILESIZE);
	tileY = (int)(bottomPosition.y / TILESIZE);

	_startTile = new tile;
	_startTile->init(tileX, tileY);
	_startTile->setAttribute("start");

	cout << _playerPosition.x << "\t" << _playerPosition.y << endl;

	//���� Ÿ��
	_endTile = new tile;
	_endTile->init(_playerPosition.x / TILESIZE, _playerPosition.y / TILESIZE);
	_endTile->setAttribute("end");

	_currentTile = _startTile;

	if (monsterIndex == 4) { _tileX = ASTARSIZEX4; _tileY = ASTARSIZEY4;  _tileStartX = ASTARSIZESTARTX4; _tileStartY = ASTARSIZESTARTY4; _tileEndX = ASTARSIZEENDX4; _tileEndY = ASTARSIZEENDY4;}
	if (monsterIndex == 5) { _tileX = ASTARSIZEX5; _tileY = ASTARSIZEY5;  _tileStartX = ASTARSIZESTARTX5; _tileStartY = ASTARSIZESTARTY5; _tileEndX = ASTARSIZEENDX5; _tileEndY = ASTARSIZEENDY5;}
	if (monsterIndex == 6) { _tileX = ASTARSIZEX6; _tileY = ASTARSIZEY6;  _tileStartX = ASTARSIZESTARTX6; _tileStartY = ASTARSIZESTARTY6; _tileEndX = ASTARSIZEENDX6; _tileEndY = ASTARSIZEENDY6;}
	if (monsterIndex == 7) { _tileX = ASTARSIZEX7; _tileY = ASTARSIZEY7;  _tileStartX = ASTARSIZESTARTX7; _tileStartY = ASTARSIZESTARTY7; _tileEndX = ASTARSIZEENDX7; _tileEndY = ASTARSIZEENDY7;}

	for (int i = _tileStartY; i < _tileEndY; ++i)
	{
		for (int j = _tileStartX; j < _tileEndX; ++j)
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
			//if (_stage->getTileinfo()[i * 200 + j].objectIndex != NULL)
			//{
			//	node->setAttribute("wall");
			//}
			_vTotalList.push_back(node);
		}
	}
	
	pathFinder(_startTile);

	cout << _vTotalList.size() << endl;
	cout << _vClosedList.size() << endl;
	cout << _vOpenList.size() << endl;
	cout << _vEndTile.size() << endl;

	if (_vClosedList.size())
	{
		_endPosition.x = _vClosedList[_vClosedList.size() - 2]->getCenter().x;
		_endPosition.y = _vClosedList[_vClosedList.size() - 2]->getCenter().y;

		//_endPosition.x = _vEndTile[_vEndTile.size() - 1]->getCenter().x;
		//_endPosition.y = _vEndTile[_vEndTile.size() - 1]->getCenter().y;

		//_vClosedList.clear();
		//_vOpenList.clear();
		//_vTotalList.clear();

		//cout << _endPosition.x << "\t" << _endPosition.y << endl;

		return _endPosition;
	}
	else
	{
		return bottomPosition;
	}

}

vector<tile*> Astar::addOpenList(tile * currentTile)
{
	int x = currentTile->getIdX() - _tileStartX;
	int y = currentTile->getIdY() - _tileStartY;


	int startX = x - 1;
	int startY = y - 1;
	// 88 - 120
	// 116 - 132

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int temp;
			temp = (startY + i) * _tileX + (startX + j);
			if (temp < 0 || temp > _tileX * _tileY) continue;
			if (startX + j > _tileX || startX + j < 0 || startY + i < 0 || startY + i > _tileY) continue;

			//if (startX + j < _tileStartX || startY + i < _tileStartY || (startX + j > _tileEndX - 1 || startY + i > _tileEndY - 1)) continue;
			//if (startX + j < 0 || startY + i < 0 || startX + j > MAXTILEX - 1 || startY + i > MAXTILEX - 1) continue;
			tile* node = _vTotalList[temp];
			
			//����ó��
			//if ((i == 0 && j == 0) || (i == 2 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 2)) continue;
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;


			//���� Ÿ���� ��� �������ش�
			node->setParentNode(_currentTile);

			//������ �Ұ��� �ΰ� üũ���ߴ��� �Ǵ�
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
	//���ϱ� ���ϰ� ������ ��κ���� �����ص���
	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	//���¸���Ʈ ���Ϳ��� ���� ���� ��θ� �̾Ƴ���
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

		//���� ��κ���� ����
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		_vOpenList[i]->setIsOpen(false);
	}

	if (tempTile == NULL) return;
	//����������
	if (tempTile->getAttribute() == "end")
	{
		

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
