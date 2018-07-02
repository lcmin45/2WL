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
		_box[i].baseImg->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);

		char str[128];
		sprintf_s(str, "%d", i);
		TextOut(CAMERAMANAGER->getCameraDC(), _box[i].center.x, _box[i].center.y, str, strlen(str));

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			RectangleMake(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top, _box[i].baseImg->getWidth(), _box[i].baseImg->getHeight());
		}
	}
}

void page2::boxInit(void)
{
	_center = WINCENTER;

	for (int i = 0; i < MAXBOXX; ++i)
	{
		for (int j = 0; j < MAXBOXY; ++j)
		{
			_box[i * MAXBOXX + j].baseImg = IMAGEMANAGER->findImage("BOX_2_2");
			_box[i * MAXBOXX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 47,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j].rc = RectMakeCenter(_box[i * MAXBOXX + j].center.x, _box[i * MAXBOXX + j].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j].baseImg->getHeight());
			_box[i * MAXBOXX + j].frameX = NULL;
			_box[i * MAXBOXX + j].frameY = NULL;

			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg = IMAGEMANAGER->findImage("BOX_2_2");
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].rc = RectMakeCenter(_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.x, _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg->getHeight());
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].frameX = NULL;
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].frameY = NULL;
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

	for (int i = 0; i < MAXBOXX; ++i)
	{
		for (int j = 0; j < MAXBOXY; ++j)
		{
			_box[i * MAXBOXX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 47,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j].rc = RectMakeCenter(_box[i * MAXBOXX + j].center.x, _box[i * MAXBOXX + j].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j].baseImg->getHeight());

			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].rc = RectMakeCenter(_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.x, _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg->getHeight());
		}
	}
}