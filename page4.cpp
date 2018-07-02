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

void page4::boxInit(void)
{
	_center = WINCENTER;

	for (int i = 0; i < MAXBOXY; ++i)
	{
		for (int j = 0; j < MAXBOXX; ++j)
		{
			_box[i * MAXBOXX + j].baseImg = IMAGEMANAGER->findImage("BOX_3_2");
			_box[i * MAXBOXX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 3) + 1) - 21 + 72,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j].rc = RectMakeCenter(_box[i * MAXBOXX + j].center.x, _box[i * MAXBOXX + j].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j].baseImg->getHeight());
			_box[i * MAXBOXX + j].imageIndex = NULL;
			_box[i * MAXBOXX + j].frameX = NULL;
			_box[i * MAXBOXX + j].frameY = NULL;
			_box[i * MAXBOXX + j].objectIndex = NULL;

			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg = IMAGEMANAGER->findImage("BOX_3_2");
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 3) + 1) - 21 + 72,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].rc = RectMakeCenter(_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.x, _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg->getHeight());
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].imageIndex = NULL;
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].frameX = NULL;
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].frameY = NULL;
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].objectIndex = NULL;
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
	for (int i = 0; i < MAXBOXY * MAXBOXX; ++i)
	{
		switch (_box[i].imageIndex)
		{
		case 10:
		{
			
		}
			break;
		default:
			break;
		}
	}
}

void page4::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBOX; ++i)
		{
			if (PtInRect(&_box[i].rc, getCameraPoint()))
			{
				_currentCheck = CH_AUTO;
				_currentAuto.imageIndex = _box[i].imageIndex;
				_currentAuto.startPoint = _startPoint[i];
				_currentAuto.endPoint	= _box[i].renderPoint;
				break;
			}
		}		
	}
}

void page4::setIndex(int index)
{
	switch (index)
	{
	case 0:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_AUTOWAY");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_AUTOWALL");

		_box[0].imageIndex = 10;
		_startPoint[0] = PointMake(0, 0);
		_box[0].renderPoint = PointMake(4, 3);

		_box[1].imageIndex = 10;
		_startPoint[1] = PointMake(0, 4);
		_box[1].renderPoint = PointMake(4 ,6);

		_box[2].imageIndex = 10;
		_startPoint[2] = PointMake(5, 0);
		_box[2].renderPoint = PointMake(14, 3);

		_box[3].imageIndex = 10;
		_startPoint[3] = PointMake(5, 4);
		_box[3].renderPoint = PointMake(9, 6);

		_box[4].imageIndex = 10;
		_startPoint[4] = PointMake(10, 4);
		_box[4].renderPoint = PointMake(14, 6);
	}
		break;
	case 1:
	{
		_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_AUTOWAY");
		_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_AUTOWALL");
	}
		break;
	}
}

void page4::setCenterPoint(POINT point)
{
	_center = point;

	for (int i = 0; i < MAXBOXY; ++i)
	{
		for (int j = 0; j < MAXBOXX; ++j)
		{
			_box[i * MAXBOXX + j].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 3) + 1) - 21 + 72,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j].rc = RectMakeCenter(_box[i * MAXBOXX + j].center.x, _box[i * MAXBOXX + j].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j].baseImg->getHeight());

			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 3) + 1) - 21 + 72,
				(_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].rc = RectMakeCenter(_box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.x, _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].center.y, _box[i * MAXBOXX + j].baseImg->getWidth(), _box[i * MAXBOXX + j + MAXBOXX * MAXBOXY].baseImg->getHeight());
		}
	}
}