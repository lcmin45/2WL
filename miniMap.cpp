#include "stdafx.h"
#include "miniMap.h"

miniMap::miniMap() { }

miniMap::~miniMap() { }

HRESULT miniMap::init(void)
{
	_totalMap = IMAGEMANAGER->addImage("TOTALMAP", TOTALSIZEX, TOTALSIZEY);
	_miniMap = IMAGEMANAGER->addImage("MINIMAP", WINSIZEY, WINSIZEY);

	PatBlt(_totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, BLACKNESS);
	PatBlt(_miniMap->getMemDC(), 0, 0, WINSIZEY, WINSIZEY, BLACKNESS);

	return S_OK;
}

void miniMap::release(void)
{

}

void miniMap::update(void)
{

}

void miniMap::render(void)
{
	_miniMap->render(CAMERAMANAGER->getCameraDC(), 0, 0);
}

void miniMap::setMiniMap(HDC hdc)
{
	PatBlt(_totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, BLACKNESS);
	BitBlt(_totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, hdc, 0, 0, SRCCOPY);

	PatBlt(_miniMap->getMemDC(), 0, 0, WINSIZEY, WINSIZEY, BLACKNESS);

	StretchBlt(_miniMap->getMemDC(), 0, 0, WINSIZEY, WINSIZEY, _totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, SRCCOPY);
}