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

	if (_box[18].objectIndex != NULL) IMAGEMANAGER->findImage(_box[18].imageName)->frameRender(CAMERAMANAGER->getCameraDC(), _box[18].center.x - IMAGEMANAGER->findImage(_box[18].imageName)->getFrameWidth() / 2, _box[18].center.y - IMAGEMANAGER->findImage(_box[18].imageName)->getFrameHeight() / 2, 0, 0);

	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);

		char str[128];
		sprintf_s(str, "%d", i);
		TextOut(CAMERAMANAGER->getCameraDC(), _box[i].center.x, _box[i].center.y, str, strlen(str));
	}
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

			_box[temp].boxName = "PAGE_BOX_2_1";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 48, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (6 - i));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			temp = i * MAXBOXRX + j + MAXBOX / 2;

			_box[temp].boxName = "PAGE_BOX_1_2";
			_box[temp].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21, _center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;
		}
	}
}

void page3::titleRender(void)
{
	_titleImage[0]->render(CAMERAMANAGER->getCameraDC(), _center.x - BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
	_titleImage[1]->render(CAMERAMANAGER->getCameraDC(), _center.x + BOOKSIZEX / 4 - _titleImage[0]->getWidth() / 2, _center.y - BOOKSIZEY / 2 + 15);
}

void page3::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_box[18].rc, getCameraPoint()))
		{
			_currentCheck = CH_OBJECT;
			_currentObject.objectIndex = _box[18].objectIndex;
			_currentObject.renderPoint = _box[18].renderPoint;
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

		_box[18].imageName = "OBJECT_5";
		_box[18].objectIndex = 5;
		_box[18].renderPoint = PointMake(16, 80);
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
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			temp = i * MAXBOXRX + j + MAXBOX / 2;

			_box[temp].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21, _center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxName)->getHeight());
		}
	}
}