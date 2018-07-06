#include "stdafx.h"
#include "tile.h"

//∏‚πˆ ¿Ã¥œº»∂Û¿Ã¡Ó
tile::tile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0)
{
}


tile::~tile()
{

}

HRESULT tile::init(int idX, int idY)
{
	_center = PointMake(idX * TILESIZE + (TILESIZE / 2),
		idY * TILESIZE + (TILESIZE / 2));

	_idX = idX;
	_idY = idY;

	_rc = RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);

	_isOpen = true;

	return S_OK;
}

void tile::release()
{

}

void tile::update()
{

}

void tile::render()
{

}
