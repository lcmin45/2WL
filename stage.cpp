#include "stdafx.h"
#include "stage.h"
#include "player.h"

stage::stage() {}
stage::~stage() {}

HRESULT stage::init()
{
	_stage = 0;

	///////¾óÀ½ Æ÷Å»
	_potalRc[0] = RectMakeCenter(672, 1488, 52, 84);
	_potalRc[1] = RectMakeCenter(2240, 1664, 52, 84);
	//ºÒ Æ÷Å»
	_potalRc[2] = RectMakeCenter(956, 2912, 52, 84);
	_potalRc[3] = RectMakeCenter(656, 5504, 52, 84);
	////³ª¹« Æ÷Å»
	_potalRc[4] = RectMakeCenter(5632, 2944, 52, 84);
	_potalRc[5] = RectMakeCenter(5376, 1328, 52, 84);

	return S_OK;
}

void stage::release() {}

void stage::update()
{
	_player->update();

	_potalCount++;
	if (_potalCount % 10 == 0)
	{
		++_potalIndex;
		for (int i = 0; i < 6; i++)
		{
			if (_potalIndex > _potal[i]->getMaxFrameX())
			{
				_potalIndex = 0;
			}
		}
	}
}

void stage::render()
{
	if (_stage == 0) return;

	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK) continue;

			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 10:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->frameRender(getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			}
		}
	}

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
			case 23:
				IMAGEMANAGER->findImage("IMAGE_OBJECT_2_3")->frameRender(getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top, _tile[i * MAXTILEX + j].imageObjectFrameX, _tile[i * MAXTILEX + j].imageObjectFrameY);
				break;
			}
		}
	}

	for (int i = CAMERASTARTY; i < CAMERAENDY; ++i)
	{
		for (int j = CAMERASTARTX; j < CAMERAENDX; ++j)
		{
			if (CAMERAMAXCHECK) continue;

			if ((int)(_player->getPosition().y / TILESIZE) == i) _player->render();

			if (_tile[i * MAXTILEX + j].objectIndex == NULL) continue;

			_tile[i * MAXTILEX + j].objectClass->render();
		}

	}

	char str[128];
	sprintf_s(str, "%d, %d", _player->getPosition().x, _player->getPosition().y);
	TextOut(CAMERAMANAGER->getCameraDC(), 100, 100, str, strlen(str));
	
	////////////////Æ÷Å»//////////////////
	for (int i = 0; i < 6; i++)
	{
		_potal[i] = IMAGEMANAGER->findImage("Æ÷Å»");
		_potal[i]->frameRender(getMemDC(), _potalRc[i].left, _potalRc[i].top, _potalIndex,0);
	}
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
			_tile[i * MAXTILEX + j].objectClass->setRenderPoint(_tile[i * MAXTILEX + j].renderPoint);
			_tile[i * MAXTILEX + j].objectClass->setCenterPoint(_tile[i * MAXTILEX + j].center);
		}
	}
}