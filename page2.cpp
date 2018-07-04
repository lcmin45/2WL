#include "stdafx.h"
#include "page2.h"

page2::page2() { }

page2::~page2() { }

HRESULT page2::init(void)
{
	boxInit();

	return S_OK;
}

void page2::release(void)
{

}

void page2::update(void)
{

}

void page2::render(void)
{
	titleRender();
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);

		char str[128];
		sprintf_s(str, "%d", i);
		TextOut(CAMERAMANAGER->getCameraDC(), _box[i].center.x, _box[i].center.y, str, strlen(str));
	}
}

void page2::boxInit(void)
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

			_box[temp].boxName = "PAGE_BOX_2_2";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;

			_box[temp2].boxName = "PAGE_BOX_2_2";
			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxName)->getHeight());
			_box[temp2].frameX = NULL;
			_box[temp2].frameY = NULL;
		}
	}
}

void page2::titleRender(void)
{
	_titleImage[0]->render(CAMERAMANAGER->getCameraDC(), _center.x - BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
	_titleImage[1]->render(CAMERAMANAGER->getCameraDC(), _center.x + BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
}

void page2::setIndex(int index)
{
	switch (index)
	{
	case 0:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
	}
	break;
	case 1:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
	}
	break;
	}
}

void page2::setCenterPoint(POINT point)
{
	_center = point;

	int temp = 0;
	int temp2 = 0;

	for (int i = 0; i < MAXBOXX; ++i)
	{
		for (int j = 0; j < MAXBOXY; ++j)
		{
			temp = i * MAXBOXX + j;
			temp2 = i * MAXBOXX + j + MAXBOX / 2;

			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());

			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxName)->getHeight());
		}
	}
}