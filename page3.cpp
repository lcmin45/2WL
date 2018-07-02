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

	if (_box[18].objectIndex != NULL)IMAGEMANAGER->findImage("OBJECT_5")->frameRender(CAMERAMANAGER->getCameraDC(), _box[18].rc.left, _box[18].rc.top, 0, 0);

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

void page3::boxInit(void)
{
	_center = WINCENTER;

	for (int i = 0; i < MAXBOXLY; ++i)
	{
		for (int j = 0; j < MAXBOXLX; ++j)
		{
			_box[i * MAXBOXLX + j].baseImg = IMAGEMANAGER->findImage("BOX_2_1");
			_box[i * MAXBOXLX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 48,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (6 - i));
			_box[i * MAXBOXLX + j].rc = RectMakeCenter(_box[i * MAXBOXLX + j].center.x, _box[i * MAXBOXLX + j].center.y, _box[i * MAXBOXLX + j].baseImg->getWidth(), _box[i * MAXBOXLX + j].baseImg->getHeight());
			_box[i * MAXBOXLX + j].frameX = NULL;
			_box[i * MAXBOXLX + j].frameY = NULL;
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			_box[i * MAXBOXRX + j + MAXBOX / 2].baseImg = IMAGEMANAGER->findImage("BOX_1_2");
			_box[i * MAXBOXRX + j + MAXBOX / 2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21,
				_center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[i * MAXBOXRX + j + MAXBOX / 2].rc = RectMakeCenter(_box[i * MAXBOXRX + j + MAXBOX / 2].center.x, _box[i * MAXBOXRX + j + MAXBOX / 2].center.y, _box[i * MAXBOXRX + j + MAXBOX / 2].baseImg->getWidth(), _box[i * MAXBOXRX + j + MAXBOX / 2].baseImg->getHeight());
			_box[i * MAXBOXRX + j + MAXBOX / 2].frameX = NULL;
			_box[i * MAXBOXRX + j + MAXBOX / 2].frameY = NULL;
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

	for (int i = 0; i < MAXBOXLY; ++i)
	{
		for (int j = 0; j < MAXBOXLX; ++j)
		{
			_box[i * MAXBOXLX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 48,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (6 - i));
			_box[i * MAXBOXLX + j].rc = RectMakeCenter(_box[i * MAXBOXLX + j].center.x, _box[i * MAXBOXLX + j].center.y, _box[i * MAXBOXLX + j].baseImg->getWidth(), _box[i * MAXBOXLX + j].baseImg->getHeight());
		}
	}

	for (int i = 0; i < MAXBOXRY; ++i)
	{
		for (int j = 0; j < MAXBOXRX; ++j)
		{
			_box[i * MAXBOXRX + j + MAXBOX / 2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1) - 21 + 21,
				_center.y + BOOKSIZEY / 2 - 55 * (((2 - i) * 2) + 2) + 6);
			_box[i * MAXBOXRX + j + MAXBOX / 2].rc = RectMakeCenter(_box[i * MAXBOXRX + j + MAXBOX / 2].center.x, _box[i * MAXBOXRX + j + MAXBOX / 2].center.y, _box[i * MAXBOXRX + j + MAXBOX / 2].baseImg->getWidth(), _box[i * MAXBOXRX + j + MAXBOX / 2].baseImg->getHeight());
		}
	}
}