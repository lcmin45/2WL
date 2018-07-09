#include "stdafx.h"
#include "page3.h"

page3::page3() { }

page3::~page3() { }

HRESULT page3::init(void)
{
	boxInit();

	return S_OK;
}

void page3::release(void)
{

}

void page3::update(void)
{
	checkBox();
}

void page3::render(void)
{
	titleRender();
	tileRender();
	boxRender();
}

void page3::boxInit(void)
{
	_center = WINCENTER;

	int temp = 0;

	for (int i = 0; i < MAXBOXLY; ++i)
	{
		for (int j = 0; j < MAXBOXLX; ++j)
		{
			temp = i * MAXBOXLX + j;

			_box[temp].boxImageName = "PAGE_BOX_2_1";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 48, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (6 - i));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			temp = i * MAXBOXRX + j + MAXBOX / 2;

			_box[temp].boxImageName = "PAGE_BOX_1_2";
			_box[temp].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21, _center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
		}
	}
}

void page3::titleRender(void)
{
	_titleImage[0]->render(CAMERAMANAGER->getCameraDC(), _center.x - BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
	_titleImage[1]->render(CAMERAMANAGER->getCameraDC(), _center.x + BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
}

void page3::tileRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		if (_box[i].imageIndex != 10)
		{
			if (_box[i].imageObjectIndex == 13)
			{
				IMAGEMANAGER->findImage(_box[i].objectImageName)->frameRender(CAMERAMANAGER->getCameraDC(),
					_box[i].center.x - IMAGEMANAGER->findImage(_box[i].objectImageName)->getFrameWidth() / 2,
					_box[i].center.y - IMAGEMANAGER->findImage(_box[i].objectImageName)->getFrameHeight() / 2,
					_box[i].frameX, _box[i].frameY);
			}
		}
		else
			_box[i].autoTileImg->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left + 5, _box[i].rc.top + 5);
	}

	if (_box[34].objectIndex != NULL) IMAGEMANAGER->findImage(_box[34].tileImageName)->frameRender(CAMERAMANAGER->getCameraDC(), _box[34].center.x - IMAGEMANAGER->findImage(_box[34].tileImageName)->getFrameWidth() / 2, _box[34].center.y - IMAGEMANAGER->findImage(_box[34].tileImageName)->getFrameHeight() / 2, 0, 0);
}

void page3::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxImageName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);
	}
}

void page3::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBOX; ++i)
		{
			if (PtInRect(&_box[i].rc, getCameraPoint()))
			{
				if (_box[i].objectIndex == 5)
				{
					_currentCheck = CH_OBJECT;
					_currentObject.objectIndex = _box[34].objectIndex;
					_currentObject.renderPoint = _box[34].renderPoint;
				}

				if (_box[i].imageObjectIndex == 13)
				{
					_currentCheck = CH_OBJECT_IMAGE;

					_currentObject.imageName = _box[i].objectImageName;
					_currentObject.imageObjectIndex = _box[i].imageObjectIndex;
					_currentObject.frameX = _box[i].frameX;
					_currentObject.frameY = _box[i].frameY;
					_currentObject.objectSetpoint = _box[i].objectSetPoint;
					_currentObject.renderPoint = _box[i].renderPoint;
					_currentObject.objectCheckSize = _box[i].objectCheckSize;
					_currentObject.terrain = _box[i].terrain;
				}

				if (_box[i].imageIndex != 10) continue;

				if (PtInRect(&_box[i].rc, getCameraPoint()))
				{
					_currentCheck = CH_AUTO;
					_currentAuto.imageIndex = _box[i].imageIndex;
					_currentAuto.startPoint = _box[i].startPoint;
					_currentAuto.endPoint = _box[i].endPoint;
					_currentAuto.autoCheck = _box[i].autoCheck;
					_currentAuto.terrain = _box[i].terrain;
					break;
				}
			}
		}
	}
}

void page3::setIndex(int index)
{
	switch (index)
	{
	case 0:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");

		for (int i = 0; i < 12; ++i)
		{
			_box[MAXBOX / 2 + i].objectImageName = "IMAGE_OBJECT_1_3";
			_box[MAXBOX / 2 + i].imageObjectIndex = 13;
			_box[MAXBOX / 2 + i].frameX = i;
			_box[MAXBOX / 2 + i].frameY = 0;
			_box[MAXBOX / 2 + i].objectSetPoint = LEFT_BOTTOM;
			_box[MAXBOX / 2 + i].renderPoint = PointMake(16, 80);
			_box[MAXBOX / 2 + i].objectCheckSize = PointMake(1, 3);
			_box[MAXBOX / 2 + i].terrain = TR_WAY;
		}
	}
	break;
	case 1:
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");

		for (int i = 0; i < 8; ++i)
			_box[i].imageIndex = 10;

		setBox(0, 16, 20, 19, 20, AUTO_ALL, TR_WAY);
		setBox(1, 16, 21, 19, 21, AUTO_ALL, TR_WAY);
		setBox(2, 16, 22, 19, 22, AUTO_ALL, TR_WAY);
		setBox(3, 16, 23, 19, 23, AUTO_ALL, TR_WAY);
		setBox(4, 20, 20, 23, 20, AUTO_ALL, TR_WAY);
		setBox(5, 20, 21, 23, 21, AUTO_ALL, TR_WAY);
		setBox(6, 20, 22, 23, 22, AUTO_ALL, TR_WAY);
		setBox(7, 20, 23, 23, 23, AUTO_ALL, TR_WAY);

		for (int i = MAXBOX / 2; i < MAXBOX / 2 + 16; ++i)
			_box[i].imageIndex = 10;

		setBox(MAXBOX / 2 + 0, 0, 21, 0, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 1, 1, 21, 1, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 2, 2, 21, 2, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 3, 3, 21, 3, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 4, 4, 21, 4, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 5, 5, 21, 5, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 6, 6, 21, 6, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 7, 7, 21, 7, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 8, 8, 21, 8, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 9, 9, 21, 9, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 10, 10, 21, 10, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 11, 11, 21, 11, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 12, 12, 21, 12, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 13, 13, 21, 13, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 14, 14, 21, 14, 22, AUTO_UP_DOWN, TR_WALL);
		setBox(MAXBOX / 2 + 15, 15, 21, 15, 22, AUTO_UP_DOWN, TR_WALL);

		_box[34].tileImageName = "OBJECT_5";
		_box[34].objectIndex = 5;
		_box[34].renderPoint = PointMake(16, 80);

		for (int i = 0; i < MAXBOX; ++i)
		{
			if (_box[i].imageIndex != 10) continue;

			char str[128];
			sprintf_s(str, "AUTO_TILE_3_%d_%d", index, i);
			_box[i].autoTileImg = IMAGEMANAGER->addImage(str, _box[i].rc.right - _box[i].rc.left - 10, _box[i].rc.bottom - _box[i].rc.top - 10);

			PatBlt(_box[i].autoTileImg->getMemDC(), 0, 0, _box[i].rc.right - _box[i].rc.left - 10, _box[i].rc.bottom - _box[i].rc.top - 10, BLACKNESS);

			StretchBlt(_box[i].autoTileImg->getMemDC(),
				0, 0,
				_box[i].rc.right - _box[i].rc.left - 10,
				_box[i].rc.bottom - _box[i].rc.top - 10,
				IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->getMemDC(),
				_box[i].startPoint.x * TILESIZE, _box[i].startPoint.y * TILESIZE,
				(_box[i].endPoint.x - _box[i].startPoint.x + 1) * TILESIZE,
				(_box[i].endPoint.y - _box[i].startPoint.y + 1) * TILESIZE, SRCCOPY);
		}
		break;
	}
}

void page3::setCenterPoint(POINT point)
{
	_center = point;

	int temp = 0;

	for (int i = 0; i < MAXBOXLY; ++i)
	{
		for (int j = 0; j < MAXBOXLX; ++j)
		{
			temp = i * MAXBOXLX + j;

			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 48, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (6 - i));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			temp = i * MAXBOXRX + j + MAXBOX / 2;

			_box[temp].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21, _center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
		}
	}
}

void page3::setBox(int index, int startX, int startY, int endX, int endY, AUTOCHECK autoCheck, TERRAIN terrain)
{
	_box[index].startPoint = PointMake(startX, startY);
	_box[index].endPoint = PointMake(endX, endY);
	_box[index].autoCheck = autoCheck;
	_box[index].terrain = terrain;
}