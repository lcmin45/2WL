#include "stdafx.h"
#include "stage.h"
#include "player.h"

stage::stage() {}
stage::~stage() {}

HRESULT stage::init()
{
	_stage = 0;

	return S_OK;
}

void stage::release() {}

void stage::update()
{
	_player->update();
}

void stage::render()
{
	if (_stage == 0) return;

	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 1:
			{
				IMAGEMANAGER->findImage("SAMPLETILE_ICE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
			}
				break;
			case 10:
			{
				IMAGEMANAGER->findImage("SAMPLETILE_AUTO_ICE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
			}
				break;
			}
		}
	}

	for (int i = (CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE; i < (CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE; j < (CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1; ++j)
		{
			if (i >= MAXTILEY || j >= MAXTILEX) continue;

			if ((int)(_player->getPosition().y / TILESIZE) == i) _player->render();

			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			_tile[i * MAXTILEX + j].objectClass->render();
		}
	
	}

	char str[128];
	sprintf_s(str, "%d, %d", _player->getPosition().x, _player->getPosition().y);
	TextOut(CAMERAMANAGER->getCameraDC(), 100, 100, str, strlen(str));
}

void stage::stageLoad(int stage)
{
	_stage = stage;

	HANDLE file;
	DWORD load;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagMapToolTile) * MAXTILEX * MAXTILEY, &load, NULL);

	CloseHandle(file);

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;
			
			_tile[i * MAXTILEX + j].objectClass = new tileObject;
			_tile[i * MAXTILEX + j].objectClass->init(_tile[i * MAXTILEX + j].objectIndex);
			_tile[i * MAXTILEX + j].objectClass->setPoint(_tile[i * MAXTILEX + j].center);
		}
	}
}