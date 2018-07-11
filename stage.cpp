#include "stdafx.h"
#include "stage.h"
#include "player.h"

stage::stage() {}
stage::~stage() {}

HRESULT stage::init()
{
	_stage1 = IMAGEMANAGER->addImage("STAGE1", TILESIZE * MAXTILEX, TILESIZE * MAXTILEY);

	_stage = 0;

	///////¾óÀ½ Æ÷Å»
	_potalRc[0] = RectMakeCenter(2240, 1664, 52, 84);
	_potalRc[1] = RectMakeCenter(672, 1488, 52, 84);
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
	warp();

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

	_stage1->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2,
		CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	
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
			case 100:
				IMAGEMANAGER->findImage("storeNpc")->render(getMemDC(), _tile[(i - 2) * MAXTILEX + (j)].rc.left, _tile[(i - 2) * MAXTILEX + (j)].rc.top);
				break;
			case 101:
				IMAGEMANAGER->findImage("storeTable")->render(getMemDC(), _tile[(i - 1) * MAXTILEX + (j)].rc.left, _tile[(i - 1) * MAXTILEX + (j)].rc.top);
				break;
			}

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

	PatBlt(_stage1->getMemDC(), 0, 0, TILESIZE * MAXTILEX, TILESIZE * MAXTILEY, BLACKNESS);

	for (int i = 0; i < MAXTILEY; ++i)
	{
		for (int j = 0; j < MAXTILEX; ++j)
		{
			switch (_tile[i * MAXTILEX + j].imageIndex)
			{
			case 10:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->frameRender(_stage1->getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			case 11:
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE_2")->frameRender(_stage1->getMemDC(), _tile[i * MAXTILEX + j].rc.left, _tile[i * MAXTILEX + j].rc.top, _tile[i * MAXTILEX + j].terrainFrameX, _tile[i * MAXTILEX + j].terrainFrameY);
				break;
			}
		}
	}

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

void stage::warp()
{
	RECT temp;
	//ºÒÁö¿ª
	if (IntersectRect(&temp, &_potalRc[0], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 672, 1488 });
	}
	else if (IntersectRect(&temp, &_potalRc[1], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 2240, 1664 });
	}
	//¾óÀ½Áö¿ª
	else if (IntersectRect(&temp, &_potalRc[2], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 656, 5504 });
	}
	else if (IntersectRect(&temp, &_potalRc[3], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 956, 2912 });
	}
	//³ª¹«Áö¿ª
	else if (IntersectRect(&temp, &_potalRc[4], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 5376, 1328 });
	}
	else if (IntersectRect(&temp, &_potalRc[5], &_player->getPlayerRect()) && KEYMANAGER->isOnceKeyDown('F'))
	{
		_player->setPosition({ 5632, 2944 });
	}

}
