#include "stdafx.h"
#include "mapTile.h"

mapTile::mapTile() { }

mapTile::~mapTile() { }

HRESULT mapTile::init(void)
{
	tileInit();

	_isMouseBook = false;
	_isMiniMap = false;
	return S_OK;
}

void mapTile::release(void)
{

}

void mapTile::update(void)
{
	inputKey();
	checkTile();
}

void mapTile::render(void)
{
	tileBoxRender();
	terrainRender();
	objectRender();

	pointRender();
	mouseBoxRender();
	mousePointRender();
}

void mapTile::tileInit(void)
{
	int temp;

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			temp = i * MAXTILEX + j;

			_tile[temp].center = PointMake(j * TILESIZE + TILESIZE / 2, i * TILESIZE + TILESIZE / 2);
			_tile[temp].rc = RectMakeCenter(_tile[temp].center.x, _tile[temp].center.y, TILESIZE, TILESIZE);
			_tile[temp].imageIndex = NULL;
			_tile[temp].terrain = TR_NONE;
			_tile[temp].object = OBJ_NONE;
			_tile[temp].tileIndexX = j;
			_tile[temp].tileIndexY = i;
			_tile[temp].terrainFrameX = NULL;
			_tile[temp].terrainFrameY = NULL;
		}
	}
}

void mapTile::inputKey(void)
{

}

void mapTile::checkTile(void)
{
	if (_isMouseBook) return;

	checkTerrain();
	checkObject();
	checkAuto();
}

void mapTile::checkTerrain(void)
{
	if (_currentCheck != CH_TERRAIN) return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		int temp;

		for (int i = getMousePoint().y / TILESIZE; i < getMousePoint().y / TILESIZE + WINSIZEY / TILESIZE; ++i)
		{
			for (int j = getMousePoint().x / TILESIZE; j < getMousePoint().x / TILESIZE + WINSIZEX / TILESIZE; ++j)
			{
				if (i >= MAXTILEY || j >= MAXTILEX) continue;

				if (PtInRect(&_tile[i * MAXTILEX + j].rc, getMousePoint()))
				{
					temp = i * MAXTILEX + j;

					_tile[temp].imageIndex = _currentTerrain.imageIndex;
					_tile[temp].terrainFrameX = _currentTerrain.frameX;
					_tile[temp].terrainFrameY = _currentTerrain.frameY;
				}
			}
		}
	}
}

void mapTile::checkObject(void)
{
	if (_currentCheck != CH_OBJECT) return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		int temp;

		for (int i = getMousePoint().y / TILESIZE; i < getMousePoint().y / TILESIZE + WINSIZEY / TILESIZE; ++i)
		{
			for (int j = getMousePoint().x / TILESIZE; j < getMousePoint().x / TILESIZE + WINSIZEX / TILESIZE; ++j)
			{
				if (i >= MAXTILEY || j >= MAXTILEX) continue;

				if (PtInRect(&_tile[i * MAXTILEX + j].rc, getMousePoint()))
				{
					temp = i * MAXTILEX + j;
					_tile[temp].objectClass = new tileObject;
					_tile[temp].objectIndex = _currentObject.objectIndex;
					_tile[temp].renderPoint = _currentObject.renderPoint;
					_tile[temp].objectClass->init(_tile[temp].objectIndex);
					_tile[temp].objectClass->setRenderPoint(_tile[temp].renderPoint);
					_tile[temp].objectClass->setCenterPoint(_tile[temp].center);
					break;
				}
			}
		}
	}
}

void mapTile::checkAuto(void)
{
	if (_currentCheck != CH_AUTO) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_startPoint = PointMake(getMousePoint().x / TILESIZE, getMousePoint().y / TILESIZE);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_endPoint = PointMake(getMousePoint().x / TILESIZE, getMousePoint().y / TILESIZE);

		POINT tempPoint;

		if (_startPoint.x > _endPoint.x)
		{
			tempPoint.x = _endPoint.x;
			_endPoint.x = _startPoint.x;
			_startPoint.x = tempPoint.x;
		}

		if (_startPoint.y > _endPoint.y)
		{
			tempPoint.y = _endPoint.y;
			_endPoint.y = _startPoint.y;
			_startPoint.y = tempPoint.y;
		}

		int temp;

		for (int i = _startPoint.y; i < _endPoint.y + 1; ++i)
		{
			for (int j = _startPoint.x; j < _endPoint.x + 1; ++j)
			{
				temp = i * MAXTILEX + j;

				_tile[temp].terrain = TR_WALL;
				_tile[temp].imageIndex = _currentAuto.imageIndex;

				if (_currentAuto.endPoint.x - _currentAuto.startPoint.x <= 2)	_tile[temp].terrainFrameX = _currentAuto.startPoint.x + 1;
				else _tile[temp].terrainFrameX = _currentAuto.startPoint.x + 1 + RND->getInt(_currentAuto.endPoint.x - _currentAuto.startPoint.x - 2);

				if (_currentAuto.endPoint.y - _currentAuto.startPoint.y <= 2)	_tile[temp].terrainFrameY = _currentAuto.startPoint.y + 1;
				else _tile[temp].terrainFrameY = _currentAuto.startPoint.y + 1 + RND->getInt(_currentAuto.endPoint.y - _currentAuto.startPoint.y - 2);

				if (i == _startPoint.y)		_tile[temp].terrainFrameY = _currentAuto.startPoint.y;
				if (i == _endPoint.y)		_tile[temp].terrainFrameY = _currentAuto.endPoint.y;
				if (j == _startPoint.x)		_tile[temp].terrainFrameX = _currentAuto.startPoint.x;
				if (j == _endPoint.x)		_tile[temp].terrainFrameX = _currentAuto.endPoint.x;
			}
		}

		_startPoint = ZEROPOINT;
		_endPoint = ZEROPOINT;
	}
}

void mapTile::terrainRender(void)
{
	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (_tile[i * MAXTILEX + j].imageIndex == NULL || i >= MAXTILEY || j >= MAXTILEX) continue;

			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 1:
			{
				IMAGEMANAGER->findImage("SAMPLETILE_ICE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 10:
			{
				IMAGEMANAGER->findImage("SAMPLETILE_AUTO_ICE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
			}
			break;
			}

			if (KEYMANAGER->isToggleKey(VK_F3))
			{
				char str[128];
				sprintf_s(str, "%d, %d", _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, str, strlen(str));
			}
		}
	}
}

void mapTile::objectRender(void)
{
	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (_tile[i * MAXTILEX + j].objectIndex == NULL || i >= MAXTILEY || j >= MAXTILEX) continue;

			_tile[i * MAXTILEX + j].objectClass->render();
		}
	}
}

void mapTile::tileBoxRender(void)
{
	if (!KEYMANAGER->isToggleKey(VK_F1)) return;

	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			IMAGEMANAGER->findImage("TILE_WHITE")->render(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top);
		}
	}
}

void mapTile::pointRender(void)
{
	if (!KEYMANAGER->isToggleKey(VK_F2)) return;

	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			char str[128];
			sprintf_s(str, "%d,", _tile[i * MAXTILEX + j].tileIndexX);
			TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, str, strlen(str));

			char str2[128];
			sprintf_s(str2, "%d", _tile[i * MAXTILEX + j].tileIndexY);
			TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top + 15, str2, strlen(str2));
		}
	}
}

void mapTile::mouseBoxRender(void)
{
	IMAGEMANAGER->findImage("TILE_BLUE")->render(getMemDC(), _tile[getMousePoint().y / TILESIZE * MAXTILEX + getMousePoint().x / TILESIZE].rc.left,
		_tile[getMousePoint().y / TILESIZE * MAXTILEX + getMousePoint().x / TILESIZE].rc.top);

	if (_startPoint.x == NULL && _startPoint.y == NULL) return;

	POINT tempPoint;
	POINT startPoint = _startPoint;
	POINT mousePoint;

	mousePoint.x = getMousePoint().x / TILESIZE;
	mousePoint.y = getMousePoint().y / TILESIZE;

	if (startPoint.x > mousePoint.x)
	{
		tempPoint.x = startPoint.x;
		startPoint.x = mousePoint.x;
		mousePoint.x = tempPoint.x;
	}

	if (startPoint.y > mousePoint.y)
	{
		tempPoint.y = startPoint.y;
		startPoint.y = mousePoint.y;
		mousePoint.y = tempPoint.y;
	}

	for (int i = startPoint.y; i < mousePoint.y + 1; ++i)
	{
		for (int j = startPoint.x; j < mousePoint.x + 1; ++j)
		{
			IMAGEMANAGER->findImage("TILE_BLUE")->render(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top);
		}
	}
}

void mapTile::mousePointRender(void)
{
	if (_isMouseBook) return;


}

void mapTile::save(void)
{
	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			_tile[i * MAXTILEX + j].objectClass = NULL;
		}
	}

	HANDLE file;
	DWORD save;

	file = CreateFile("mapTool.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tile, sizeof(tagMapToolTile) * MAXTILEX * MAXTILEY, &save, NULL);

	CloseHandle(file);

	int temp;

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			temp = i * MAXTILEX + j;
			_tile[temp].objectClass = new tileObject;
			_tile[temp].objectClass->init(_tile[temp].objectIndex);
			_tile[temp].objectClass->setRenderPoint(_tile[temp].renderPoint);
			_tile[temp].objectClass->setCenterPoint(_tile[temp].center);
		}
	}
}

void mapTile::load(void)
{
	HANDLE file;
	DWORD load;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagMapToolTile) * MAXTILEX * MAXTILEY, &load, NULL);

	CloseHandle(file);

	int temp;

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			temp = i * MAXTILEX + j;

			_tile[temp].objectClass = new tileObject;
			_tile[temp].objectClass->init(_tile[temp].objectIndex);
			_tile[temp].objectClass->setRenderPoint(_tile[temp].renderPoint);
			_tile[temp].objectClass->setCenterPoint(_tile[temp].center);
		}
	}
}

void mapTile::minimap(void)
{
	_isMiniMap = true;

	image* tempImg;
	tempImg = IMAGEMANAGER->addImage("TMEP", TOTALSIZEX, TOTALSIZEY);
	PatBlt(tempImg->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, BLACKNESS);

	int temp;

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			temp = i * MAXTILEX + j;

			if (_tile[i].imageIndex == NULL) continue;

			switch (_tile[temp].imageIndex)
			{
			case 1: IMAGEMANAGER->findImage("SAMPLETILE_ICE")->frameRender(tempImg->getMemDC(), _tile[temp].rc.left, _tile[temp].rc.top, _tile[temp].terrainFrameX, _tile[temp].terrainFrameY);
				break;
			case 10: IMAGEMANAGER->findImage("SAMPLETILE_AUTO_ICE")->frameRender(tempImg->getMemDC(), _tile[temp].rc.left, _tile[temp].rc.top, _tile[temp].terrainFrameX, _tile[temp].terrainFrameY);
				break;
			}
		}
	}

	_miniMap->setMiniMap(tempImg->getMemDC());
}