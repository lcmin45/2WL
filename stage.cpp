#include "stdafx.h"
#include "stage.h"
#include "player.h"
#include "tileObject.h"

stage::stage() {}
stage::~stage() {}

HRESULT stage::init()
{
	// 셈플 타일 이미지
	IMAGEMANAGER->addFrameImage("SAMPLETILE_ICE", "image/mapTool/tile/sampleTile.bmp", 320, 224, 10, 7, false, RGBNONE);
	IMAGEMANAGER->addFrameImage("SAMPLETILE_AUTO_ICE", "image/mapTool/tile/autoTile_ice.bmp", 480, 224, 15, 7, false, RGBNONE);
	
	// 오브젝트 이미지
	IMAGEMANAGER->addFrameImage("OBJECT_CANDLE", "image/mapTool/object1.bmp", 60, 34, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object/object_5.bmp", 192, 96, 6, 1, true, RGBMAGENTA);

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

			if (_tile[i * MAXTILEX + j].imageIndex == NULL) continue;

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
	int temp;
	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			temp = i * MAXTILEX + j;

			_tile[temp].imageIndex = NULL;
			_tile[temp].terrain = TR_NONE;
			_tile[temp].object = OBJ_NONE;
			_tile[temp].objectIndex = NULL;
			_tile[temp].objectClass = NULL;
		}
	}

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
			_tile[i * MAXTILEX + j].objectClass->setRenderPoint(_tile[i * MAXTILEX + j].renderPoint);
			_tile[i * MAXTILEX + j].objectClass->setCenterPoint(_tile[i * MAXTILEX + j].center);
		}
	}
}