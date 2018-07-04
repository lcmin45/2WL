#include "stdafx.h"
#include "mapTool.h"
#include "miniMap.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}


HRESULT mapTool::init(void)
{
	imageInit();

	_mapTile = new mapTile;
	_mapTile->init();

	_book = new mapToolBook;
	_book->init();

	_miniMap = new miniMap;
	_miniMap->init();

	_isMiniMapView = false;
	_moveSpeed = 10;

	_mapTile->setMiniMapMemoryAddressLink(_miniMap);
	_book->setMapTileMemoryAddressLink(_mapTile);

	return S_OK;
}

void mapTool::release(void)
{
	SAFE_DELETE(_mapTile);
	SAFE_DELETE(_book);
	SAFE_DELETE(_miniMap);
	SAFE_DELETE(_book);
}

void mapTool::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _mapTile->getIsMiniMap())
	{
		_isMiniMapView = false;
		_mapTile->setIsMiniMap(false);
	}

	if (_isMiniMapView) return;

	KEYANIMANAGER->update();
	_mapTile->setIsMouseBook(_book->getIsMouseBook());
	_mapTile->update();
	_book->update();

	inputKey();
}

void mapTool::render(void)
{
	miniMapRender();
	mapToolRender();
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
	if (!_isMiniMapView) return;

	_miniMap->render();
}

void mapTool::mapToolRender(void)
{
	if (_isMiniMapView) return;

	_mapTile->render();
	_book->render();
}