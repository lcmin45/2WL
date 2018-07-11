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

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_eraser = ER_NONE;
		_currentCheck = CH_AUTO_DELETE_WAY;
	}

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_eraser = ER_WAY;
		_currentCheck = CH_AUTO_DELETE_WAY;
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_eraser = ER_WALL;
		_currentCheck = CH_AUTO_DELETE_WAY;
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_eraser = ER_OBJ;
		_currentCheck = CH_AUTO_DELETE_WAY;
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_currentCheck = CH_OBJECT_IMAGE;
		_currentObject.objectIndex = NULL;
		_currentObject.imageObjectIndex = NULL;
		_currentObject.frameX = NULL;
		_currentObject.frameY = NULL;
		_currentObject.terrain = TR_NONE;
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_currentCheck = CH_OBJECT;
		_currentObject.objectIndex = NULL;
	}
}

void mapTile::render(void)
{
	tileBoxRender();
	terrainRender();
	imageObjectRender();
	classObjectRender();

	pointRender();
	mouseBoxRender();
	mousePointRender();

	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
		{
			for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
			{
				if (CAMERAMAXCHECK) continue;

				char str[128];
				sprintf_s(str, "%d", (int)_tile[i * MAXTILEX + j].terrain);
				TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, str, strlen(str));
			}
		}
	}

	// 룸 인덱스 테스트
	if (KEYMANAGER->isToggleKey(VK_F9)) return;

	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK || _tile[i * MAXTILEX + j].roomIndex == NULL) continue;

			char str[128];
			sprintf_s(str, "%d", _tile[i * MAXTILEX + j].roomIndex);
			TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, str, strlen(str));
		}
	}
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
	checkTerrain();
	checkImageObject();
	checkObject();
	checkAuto();
	checkRoomIndex();
	checkEraser();
}

void mapTile::checkTerrain(void)
{
	if (_isMouseBook || _currentCheck != CH_TERRAIN) return;

	if (!KEYMANAGER->isStayKeyDown(VK_LBUTTON)) return;

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

void mapTile::checkImageObject(void)
{
	if (_isMouseBook || _currentCheck != CH_OBJECT_IMAGE) return;

	if (!KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return;

	int temp;

	for (int i = getMousePoint().y / TILESIZE; i < getMousePoint().y / TILESIZE + WINSIZEY / TILESIZE; ++i)
	{
		for (int j = getMousePoint().x / TILESIZE; j < getMousePoint().x / TILESIZE + WINSIZEX / TILESIZE; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			temp = i * MAXTILEX + j;

			if (PtInRect(&_tile[i * MAXTILEX + j].rc, getMousePoint()))
			{
				for (int i = 0; i < _currentObject.objectCheckSize.x; ++i)
				{
					if (_tile[temp + i].object != OBJ_NONE || _tile[temp + i].objectIndex != NULL) return;
				}

				for (int i = 0; i < _currentObject.objectCheckSize.x; ++i)
				{
					_tile[temp + i].object = OBJ_WAY;
				}

				_tile[temp].imageObjectIndex = _currentObject.imageObjectIndex;
				_tile[temp].imageObjectFrameX = _currentObject.frameX;
				_tile[temp].imageObjectFrameY = _currentObject.frameY;
				_tile[temp].renderPoint = _currentObject.renderPoint;
				_tile[temp].objectSetPoint = _currentObject.objectSetpoint;
				_tile[temp].objectCheckSize = _currentObject.objectCheckSize;
				_tile[temp].objectTerrain = _currentObject.terrain;
			}
		}
	}
}

void mapTile::checkObject(void)
{
	if (_isMouseBook || _currentCheck != CH_OBJECT) return;

	if (!KEYMANAGER->isStayKeyDown(VK_LBUTTON)) return;

	int temp;

	for (int i = getMousePoint().y / TILESIZE; i < getMousePoint().y / TILESIZE + WINSIZEY / TILESIZE; ++i)
	{
		for (int j = getMousePoint().x / TILESIZE; j < getMousePoint().x / TILESIZE + WINSIZEX / TILESIZE; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			if (PtInRect(&_tile[i * MAXTILEX + j].rc, getMousePoint()))
			{
				temp = i * MAXTILEX + j;

				if (_currentObject.objectIndex == NULL)
				{
					_tile[temp].objectIndex = NULL;
					_tile[temp].object = OBJ_NONE;
					_tile[temp + 1].object = OBJ_NONE;
				}
				else if (_tile[temp].objectIndex == NULL || _tile[temp].object == OBJ_NONE)
				{
					_tile[temp].objectClass = new tileObject;
					_tile[temp].objectIndex = _currentObject.objectIndex;
					_tile[temp].renderPoint = _currentObject.renderPoint;
					_tile[temp].objectClass->init(_tile[temp].objectIndex);
					_tile[temp].objectClass->setRenderPoint(_tile[temp].renderPoint);
					_tile[temp].objectClass->setCenterPoint(_tile[temp].center);
				}
				break;
			}
		}
	}
}

void mapTile::checkAuto(void)
{
	if (_currentCheck != CH_AUTO) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_isMouseBook)
	{
		_startPoint = PointMake(getMousePoint().x / TILESIZE, getMousePoint().y / TILESIZE);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _startPoint.x != NULL && _startPoint.y != NULL)
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

				_tile[temp].terrain = _currentAuto.terrain;
				_tile[temp].imageIndex = _currentAuto.imageIndex;

				if (_currentAuto.autoCheck == AUTO_NONE)
				{
					_tile[temp].terrainFrameX = _currentAuto.startPoint.x + RND->getInt(_currentAuto.endPoint.x - _currentAuto.startPoint.x);
					_tile[temp].terrainFrameY = _currentAuto.startPoint.y + RND->getInt(_currentAuto.endPoint.y - _currentAuto.startPoint.y);
				}
				else
				{
					if (_currentAuto.endPoint.x - _currentAuto.startPoint.x <= 2)
						_tile[temp].terrainFrameX = _currentAuto.startPoint.x;
					else
						_tile[temp].terrainFrameX = _currentAuto.startPoint.x + 1 + RND->getInt(_currentAuto.endPoint.x - _currentAuto.startPoint.x - 2);

					if (_currentAuto.endPoint.y - _currentAuto.startPoint.y <= 2)
						_tile[temp].terrainFrameY = _currentAuto.startPoint.y;
					else
						_tile[temp].terrainFrameY = _currentAuto.startPoint.y + 1 + RND->getInt(_currentAuto.endPoint.y - _currentAuto.startPoint.y - 2);
				}

				if (_currentAuto.autoCheck == AUTO_NONE) continue;

				if (i == _startPoint.y)		_tile[temp].terrainFrameY = _currentAuto.startPoint.y;
				if (i == _endPoint.y)		_tile[temp].terrainFrameY = _currentAuto.endPoint.y;

				if (_currentAuto.autoCheck == AUTO_UP_DOWN) continue;

				if (j == _startPoint.x)		_tile[temp].terrainFrameX = _currentAuto.startPoint.x;
				if (j == _endPoint.x)		_tile[temp].terrainFrameX = _currentAuto.endPoint.x;
			}
		}

		_startPoint = ZEROPOINT;
		_endPoint = ZEROPOINT;
	}
}

void mapTile::checkRoomIndex(void)
{
	if (_currentCheck != CH_ROOM_INDEX) return;

	// 추후 수정 필요
	if (KEYMANAGER->isOnceKeyDown('1')) _currentAuto.roomIndex = 1;
	if (KEYMANAGER->isOnceKeyDown('2')) _currentAuto.roomIndex = 2;
	if (KEYMANAGER->isOnceKeyDown('3')) _currentAuto.roomIndex = 3;
	if (KEYMANAGER->isOnceKeyDown('4')) _currentAuto.roomIndex = 4;
	if (KEYMANAGER->isOnceKeyDown('5')) _currentAuto.roomIndex = 5;
	if (KEYMANAGER->isOnceKeyDown('6')) _currentAuto.roomIndex = 6;
	if (KEYMANAGER->isOnceKeyDown('7')) _currentAuto.roomIndex = 7;
	if (KEYMANAGER->isOnceKeyDown('8')) _currentAuto.roomIndex = 8;
	if (KEYMANAGER->isOnceKeyDown('9')) _currentAuto.roomIndex = 9;


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_isMouseBook)
	{
		_startPoint = PointMake(getMousePoint().x / TILESIZE, getMousePoint().y / TILESIZE);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _startPoint.x != NULL && _startPoint.y != NULL)
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

				if (_tile[temp].terrain != TR_WAY) continue;

				_tile[temp].roomIndex = _currentAuto.roomIndex;
			}
		}

		_startPoint = ZEROPOINT;
		_endPoint = ZEROPOINT;
	}
}

void mapTile::checkEraser(void)
{
	if (_eraser == ER_NONE) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_isMouseBook)
	{
		_startPoint = PointMake(getMousePoint().x / TILESIZE, getMousePoint().y / TILESIZE);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _startPoint.x != NULL && _startPoint.y != NULL)
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

				switch (_eraser)
				{
				case ER_WAY:
					_tile[temp].terrain = TR_WAY;
					//_tile[temp].terrain = TR_NONE;
					break;
				case ER_WALL:
					_tile[temp].terrain = TR_WALL;
					break;
				case ER_OBJ:
					_tile[temp].object = OBJ_WAY;
					break;
				}
			}
		}

		_startPoint = ZEROPOINT;
		_endPoint = ZEROPOINT;
	}
}

void mapTile::terrainRender(void)
{
	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK || _tile[i * MAXTILEX + j].imageIndex == NULL) continue;

			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 10:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			case 11:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE_2")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			}

			if (KEYMANAGER->isToggleKey(VK_F3))
			{
				if (_tile[i * MAXTILEX + j].terrain == TR_WALL)
				{
					char str[128];
					sprintf_s(str, "1");
					TextOut(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, str, strlen(str));
				}				
			}
		}
	}
}

void mapTile::imageObjectRender(void)
{
	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK) continue;

			switch (_tile[i * MAXTILEX + j].imageObjectIndex)
			{
			case 13:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_1_3")->frameRender(getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			case 22:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_2_2")->frameRender(getMemDC(), _tile[(i - 1) * MAXTILEX + (j)].rc.left, _tile[(i - 1) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			case 23:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_2_3")->frameRender(getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			case 24:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_2_4")->frameRender(getMemDC(), _tile[(i - 3) * MAXTILEX + (j)].rc.left, _tile[(i - 3) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			case 32:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_3_2")->frameRender(getMemDC(), _tile[(i - 1) * MAXTILEX + (j)].rc.left, _tile[(i - 1) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			case 34:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_3_4")->frameRender(getMemDC(), _tile[(i - 3) * MAXTILEX + (j)].rc.left, _tile[(i - 3) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			}
		}
	}
}

void mapTile::classObjectRender(void)
{
	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK || _tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			_tile[i * MAXTILEX + j].objectClass->render();
		}
	}
}

void mapTile::tileBoxRender(void)
{
	if (!KEYMANAGER->isToggleKey(VK_F1)) return;

	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK) continue;

			IMAGEMANAGER->findImage("TILE_WHITE")->render(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top);
		}
	}
}

void mapTile::pointRender(void)
{
	if (!KEYMANAGER->isToggleKey(VK_F2)) return;

	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK) continue;

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
			if (_tile[i * MAXTILEX + j].imageIndex == NULL) continue;

			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 10:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->frameRender(tempImg->getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			case 11:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE_2")->frameRender(tempImg->getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			}
		}
	}

	//for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	//{
	//	for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
	//	{
	//		if (CAMERAMAXCHECK) continue;
	//
	//		switch (_tile[i * MAXTILEX + j].imageObjectIndex)
	//		{
	//		case 13:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_1_3")->frameRender(tempImg->getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		case 22:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_2_2")->frameRender(tempImg->getMemDC(), _tile[(i - 1) * MAXTILEX + (j)].rc.left, _tile[(i - 1) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		case 23:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_2_3")->frameRender(tempImg->getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		case 24:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_2_4")->frameRender(tempImg->getMemDC(), _tile[(i - 3) * MAXTILEX + (j)].rc.left, _tile[(i - 3) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		case 32:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_3_2")->frameRender(tempImg->getMemDC(), _tile[(i - 1) * MAXTILEX + (j)].rc.left, _tile[(i - 1) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		case 34:
	//			IMAGEMANAGER->findImage("IMAGE_OBJECT_3_4")->frameRender(tempImg->getMemDC(), _tile[(i - 3) * MAXTILEX + (j)].rc.left, _tile[(i - 3) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
	//			break;
	//		}
	//	}
	//}

	_miniMap->setMiniMap(tempImg->getMemDC());
	//_miniMap->setMiniMap(getMemDC());
}
