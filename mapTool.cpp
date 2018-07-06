#include "stdafx.h"
#include "mapTool.h"
#include "miniMap.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}


HRESULT mapTool::init(void)
{
	static int index = 0;
	index += 1;

	_mapTile = new mapTile;
	_mapTile->init();

	_book = new mapToolBook;
	_book->init(index);

	_miniMap = new miniMap;
	_miniMap->init();

	_moveSpeed = 10;

	_mapTile->setMiniMapMemoryAddressLink(_miniMap);
	_book->setMapTileMemoryAddressLink(_mapTile);

	return S_OK;
}

void mapTool::release(void)
{
	SAFE_RELEASE(_book);
	SAFE_RELEASE(_mapTile);
	SAFE_RELEASE(_miniMap);
}

void mapTool::update(void)
{
	miniMapViewUpdate();
	mapToolUpdate();
}

void mapTool::render(void)
{
	miniMapRender();
	mapToolRender();
}

void mapTool::miniMapViewUpdate(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _mapTile->getIsMiniMap())
	{
		_mapTile->setIsMiniMap(false);
	}
}

void mapTool::mapToolUpdate(void)
{
	if (_mapTile->getIsMiniMap()) return;

	KEYANIMANAGER->update();
	_mapTile->setIsMouseBook(_book->getIsMouseBook());
	_mapTile->update();
	_book->update();
	inputKey();
}

void mapTool::inputKey(void)
{
	// 책이 움직이는 중이면 동작하지 않음
	if (_book->getIsMoveBook()) return;

	if (KEYMANAGER->isStayKeyDown('W')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y - _moveSpeed });

	if (KEYMANAGER->isStayKeyDown('A')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x - _moveSpeed, CAMERAMANAGER->getCameraPoint().y });

	if (KEYMANAGER->isStayKeyDown('S')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + _moveSpeed });

	if (KEYMANAGER->isStayKeyDown('D')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x + _moveSpeed, CAMERAMANAGER->getCameraPoint().y });
}

void mapTool::miniMapRender(void)
{
	if (!_mapTile->getIsMiniMap()) return;

	_miniMap->render();
}

void mapTool::mapToolRender(void)
{
	if (_mapTile->getIsMiniMap()) return;

	_mapTile->render();
	_book->render();
}