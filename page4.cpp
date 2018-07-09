#include "stdafx.h"
#include "page4.h"

page4::page4() { }

page4::~page4() { }

HRESULT page4::init(void)
{
	boxInit();

	return S_OK;
}

void page4::release(void)
{

}

void page4::update(void)
{
	checkBox();
}

void page4::render(void)
{
	titleRender();
	tileRender();
	boxRender();
}

void page4::boxInit(void)
{
	_center = WINCENTER;

	int temp = 0;
	int temp2 = 0;

	for (int i = 0; i < MAXBOXY; ++i)
	{
		for (int j = 0; j < MAXBOXX; ++j)
		{
			temp = i * MAXBOXX + j;
			temp2 = i * MAXBOXX + j + MAXBOXX * MAXBOXY;

			_box[temp].boxImageName = "PAGE_BOX_3_2";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 3) + 1) - 21 + 72, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
			_box[temp].imageIndex = NULL;

			_box[temp2].boxImageName = "PAGE_BOX_3_2";
			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 3) + 1) - 21 + 72, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
			_box[temp2].imageIndex = NULL;
		}
	}
}

void page4::titleRender(void)
{
	_titleImage[0]->render(CAMERAMANAGER->getCameraDC(), _center.x - BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
	_titleImage[1]->render(CAMERAMANAGER->getCameraDC(), _center.x + BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
}

void page4::tileRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		_box[i].autoTileImg->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left + 5, _box[i].rc.top + 5);
	}
}

void page4::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxImageName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);
	}
}

void page4::checkBox(void)
{
	if (!KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return;

	for (int i = 0; i < MAXBOX; ++i)
	{
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

void page4::setIndex(int index)
{
	_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_AUTO");
	_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_AUTO");

	for (int i = 0; i < MAXBOX; ++i) _box[i].imageIndex = 10;

	AUTOCHECK	tempAutoCheck = AUTO_ALL;

	switch (index)
	{
	case 0:
		setBox(0, 0, 0, 3, 4, AUTO_ALL, TR_WAY);
		setBox(1, 0, 5, 3, 9, AUTO_ALL, TR_WAY);
		setBox(2, 4, 0, 7, 4, AUTO_ALL, TR_WAY);
		setBox(3, 4, 5, 7, 9, AUTO_ALL, TR_WAY);
		setBox(4, 8, 0, 11, 4, AUTO_ALL, TR_WAY);
		setBox(5, 8, 5, 11, 9, AUTO_ALL, TR_WAY);

		setBox(6, 29, 0, 33, 3, AUTO_UP_DOWN, TR_WALL);
		setBox(7, 29, 4, 33, 7, AUTO_UP_DOWN, TR_WALL);
		setBox(8, 29, 8, 33, 11, AUTO_UP_DOWN, TR_WALL);
		setBox(9, 29, 12, 33, 15, AUTO_UP_DOWN, TR_WALL);
		setBox(10, 29, 16, 33, 19, AUTO_UP_DOWN, TR_WALL);
		setBox(11, 29, 20, 33, 23, AUTO_UP_DOWN, TR_WALL);
		break;
	case 1:
		setBox(0, 0, 10, 3, 14, AUTO_ALL, TR_WAY);
		setBox(1, 1, 11, 2, 13, AUTO_NONE, TR_WAY);
		setBox(2, 4, 10, 7, 14, AUTO_ALL, TR_WAY);
		setBox(3, 5, 11, 6, 13, AUTO_NONE, TR_WAY);
		setBox(4, 8, 10, 11, 14, AUTO_ALL, TR_WAY);
		setBox(5, 9, 11, 10, 13, AUTO_NONE, TR_WAY);

		setBox(6, 0, 15, 3, 19, AUTO_ALL, TR_WAY);
		setBox(7, 1, 16, 2, 18, AUTO_NONE, TR_WAY);
		setBox(8, 4, 15, 7, 19, AUTO_ALL, TR_WAY);
		setBox(9, 5, 16, 6, 18, AUTO_NONE, TR_WAY);
		setBox(10, 8, 15, 11, 19, AUTO_ALL, TR_WAY);
		setBox(11, 9, 16, 10, 18, AUTO_NONE, TR_WAY);
		break;
	case 2:
		setBox(0, 24, 0, 28, 3, AUTO_ALL, TR_WAY);
		setBox(1, 25, 1, 27, 2, AUTO_NONE, TR_WAY);
		setBox(2, 24, 4, 28, 7, AUTO_ALL, TR_WAY);
		setBox(3, 25, 5, 27, 6, AUTO_NONE, TR_WAY);
		setBox(4, 24, 8, 28, 11, AUTO_ALL, TR_WAY);
		setBox(5, 25, 9, 27, 10, AUTO_NONE, TR_WAY);

		setBox(6, 24, 12, 28, 15, AUTO_ALL, TR_WAY);
		setBox(7, 25, 13, 27, 14, AUTO_NONE, TR_WAY);
		setBox(8, 24, 16, 28, 19, AUTO_ALL, TR_WAY);
		setBox(9, 25, 17, 27, 18, AUTO_NONE, TR_WAY);
		setBox(10, 24, 20, 28, 23, AUTO_ALL, TR_WAY);
		setBox(11, 25, 21, 27, 22, AUTO_NONE, TR_WAY);
		break;
	case 3:
		setBox(0, 12, 0, 15, 4, AUTO_NONE, TR_WAY);
		setBox(1, 12, 5, 15, 9, AUTO_NONE, TR_WAY);
		setBox(2, 16, 0, 19, 4, AUTO_NONE, TR_WAY);
		setBox(3, 16, 5, 19, 9, AUTO_NONE, TR_WAY);
		setBox(4, 20, 0, 23, 4, AUTO_NONE, TR_WAY);
		setBox(5, 20, 5, 23, 9, AUTO_NONE, TR_WAY);

		setBox(6, 12, 10, 15, 14, AUTO_ALL, TR_WAY);
		setBox(7, 20, 15, 23, 19, AUTO_ALL, TR_WAY);		//지우개
		setBox(8, 20, 10, 23, 14, AUTO_ALL, TR_WAY);
		setBox(9, 20, 15, 23, 19, AUTO_ALL, TR_WALL);		//지우개
		setBox(10, 16, 15, 19, 19, AUTO_ALL, TR_WAY);
		setBox(11, 20, 15, 23, 19, AUTO_ALL, TR_WALL);		//지우개
		break;
	}

	for (int i = 0; i < MAXBOX; ++i)
	{
		char str[128];
		sprintf_s(str, "AUTO_TILE_4_%d_%d", index, i);
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
}

void page4::setCenterPoint(POINT point)
{
	_center = point;

	int temp = 0;
	int temp2 = 0;

	for (int i = 0; i < MAXBOXY; ++i)
	{
		for (int j = 0; j < MAXBOXX; ++j)
		{
			temp = i * MAXBOXX + j;
			temp2 = i * MAXBOXX + j + MAXBOXX * MAXBOXY;

			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 3) + 1) - 21 + 72, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());

			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 3) + 1) - 21 + 72, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
		}
	}
}

void page4::setBox(int index, int startX, int startY, int endX, int endY, AUTOCHECK autoCheck, TERRAIN terrain)
{
	_box[index].startPoint = PointMake(startX, startY);
	_box[index].endPoint = PointMake(endX, endY);
	_box[index].autoCheck = autoCheck;
	_box[index].terrain = terrain;
}
