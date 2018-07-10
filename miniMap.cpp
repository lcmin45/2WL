#include "stdafx.h"
#include "miniMap.h"

miniMap::miniMap() { }

miniMap::~miniMap() { }

HRESULT miniMap::init(void)
{
	_miniMap = IMAGEMANAGER->addImage("MINIMAP", WINSIZEY, WINSIZEY);

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
	_miniMap->render(CAMERAMANAGER->getCameraDC(), 150, 0);
}

void miniMap::setMiniMap(HDC hdc)
{
	PatBlt(_miniMap->getMemDC(), 0, 0, WINSIZEY, WINSIZEY, BLACKNESS);

	StretchBlt(_miniMap->getMemDC(), 0, 0, WINSIZEY, WINSIZEY, hdc, 0, 0, TOTALSIZEX, TOTALSIZEY, SRCCOPY);
}