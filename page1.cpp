#include "stdafx.h"
#include "page1.h"

page1::page1() { }

page1::~page1() { }

HRESULT page1::init(void)
{
	boxInit();

	return S_OK;
}

void page1::release(void)
{

}

void page1::update(void)
{
	checkBox();
}

void page1::render(void)
{
	titleRender();
	tileRender();
	boxRender();
}

void page1::boxInit(void)
{
	_center = WINCENTER;

	int temp = 0;
	int temp2 = 0;

	for (int i = 0; i < MAXBOXX; ++i)
	{
		for (int j = 0; j < MAXBOXY; ++j)
		{
			temp = i * MAXBOXX + j;
			temp2 = i * MAXBOXX + j + MAXBOX / 2;

			_box[temp].boxName = "PAGE_BOX_1_1";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
			_box[temp].imageIndex = NULL;
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;

			_box[temp2].boxName = "PAGE_BOX_1_1";
			_box[temp2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxName)->getHeight());
			_box[temp2].imageIndex = NULL;
			_box[temp2].frameX = NULL;
			_box[temp2].frameY = NULL;
		}
	}
}

void page1::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBOX; ++i)
		{
			if (PtInRect(&_box[i].rc, getCameraPoint()))
			{
				_currentCheck = CH_TERRAIN;
				_currentTerrain.imageIndex = _box[i].imageIndex;
				_currentTerrain.frameX = _box[i].frameX;
				_currentTerrain.frameY = _box[i].frameY;
				break;
			}
		}
	}
}

void page1::titleRender(void)
{
	_titleImage[0]->render(CAMERAMANAGER->getCameraDC(), _center.x - BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
	_titleImage[1]->render(CAMERAMANAGER->getCameraDC(), _center.x + BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
}

void page1::tileRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		if (_box[i].imageIndex == NULL) continue;

		switch (_box[i].imageIndex)
		{
		case 1:
		{
			IMAGEMANAGER->findImage("SAMPLETILE_ICE")->frameRender(CAMERAMANAGER->getCameraDC(), _box[i].center.x - 16, _box[i].center.y - 16, _box[i].frameX, _box[i].frameY);

			char str[128];
			sprintf_s(str, "%d, %d", _box[i].frameX, _box[i].frameY);
			TextOut(CAMERAMANAGER->getCameraDC(), _box[i].rc.left + 5, _box[i].rc.top + 5, str, strlen(str));
		}
		break;
		case 2:
		{

		}
		break;
		}
	}
}

void page1::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);

		char str[128];
		sprintf_s(str, "%d", i);
		TextOut(CAMERAMANAGER->getCameraDC(), _box[i].center.x, _box[i].center.y, str, strlen(str));
	}
}

void page1::setIndex(int index)
{
	switch (index)
	{
	case 0:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_WAY");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_WAY");

		for (int i = 0; i < 70; ++i)
		{
			_box[i].imageIndex = 1;
			_box[i].frameX = i % 10;
			_box[i].frameY = i / 10;
		}
	}
	break;
	case 1:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_WALL");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_WALL");
	}
	break;
	}
}

void page1::setCenterPoint(POINT point)
{
	_center = point;

	int temp = 0;
	int temp2 = 0;

	for (int i = 0; i < MAXBOXX; ++i)
	{
		for (int j = 0; j < MAXBOXY; ++j)
		{
			temp = i * MAXBOXX + j;
			temp2 = i * MAXBOXX + j + MAXBOXX * MAXBOXY;

			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
			_box[temp2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxName)->getHeight());
		}
	}
}