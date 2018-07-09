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

			_box[temp].boxImageName = "PAGE_BOX_1_1";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
			_box[temp].imageIndex = NULL;
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;

			_box[temp2].boxImageName = "PAGE_BOX_1_1";
			_box[temp2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
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
		IMAGEMANAGER->findImage("AUTO_TILE_IMAGE")->frameRender(CAMERAMANAGER->getCameraDC(), _box[i].center.x - 16, _box[i].center.y - 16, _box[i].frameX, _box[i].frameY);
	}
}

void page1::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxImageName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);
	}
}

void page1::setIndex(int index)
{
	_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_TILE");
	_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_TILE");

	for (int i = 0; i < MAXBOX; ++i)
		_box[i].imageIndex = 10;

	switch (index)
	{
	case 0:
		setBox(0, 0, 20);	setBox(1, 1, 20);	setBox(2, 2, 20);	setBox(3, 3, 20);	setBox(4, 4, 20);	setBox(5, 5, 20);
		setBox(6, 0, 23);	setBox(7, 1, 23);	setBox(8, 2, 23);	setBox(9, 3, 23);	setBox(10, 4, 23);	setBox(11, 5, 23);
		setBox(12, 6, 20);	setBox(13, 7, 20);	setBox(14, 8, 20);	setBox(15, 9, 20);	setBox(16, 10, 20);	setBox(17, 11, 20);
		setBox(18, 6, 23);	setBox(19, 7, 23);	setBox(20, 8, 23);	setBox(21, 9, 23);	setBox(22, 10, 23);	setBox(23, 11, 23);
		setBox(24, 12, 20);	setBox(25, 13, 20);	setBox(26, 14, 20);	setBox(27, 15, 20);	setBox(28, 0, 10);	setBox(29, 3, 10);
		setBox(30, 12, 23);	setBox(31, 13, 23);	setBox(32, 14, 23);	setBox(33, 15, 23);	setBox(34, 0, 14);	setBox(35, 3, 14);

		setBox(36, 4, 10);	setBox(37, 7, 10);	setBox(38, 8, 10);	setBox(39, 11, 10);	setBox(40, 12, 10);	setBox(41, 15, 10);
		setBox(42, 4, 14);	setBox(43, 7, 14);	setBox(44, 8, 14);	setBox(45, 11, 14);	setBox(46, 12, 14);	setBox(47, 15, 14);
		setBox(48, 16, 10);	setBox(49, 19, 10);	setBox(50, 20, 10);	setBox(51, 23, 10);	setBox(52, 0, 15);	setBox(53, 3, 15);
		setBox(54, 16, 14);	setBox(55, 19, 14);	setBox(56, 20, 14);	setBox(57, 23, 14);	setBox(58, 0, 19);	setBox(59, 3, 19);
		setBox(60, 4, 15);	setBox(61, 7, 15);	setBox(62, 8, 15);	setBox(63, 11, 15);	setBox(64, 12, 15);	setBox(65, 15, 15);
		setBox(66, 4, 19);	setBox(67, 7, 19);	setBox(68, 8, 19);	setBox(69, 11, 19);	setBox(70, 12, 19);	setBox(71, 15, 19);
		break;
	case 1:
		setBox(0, 16, 15);	setBox(1, 19, 15);	setBox(2, 24, 20);	setBox(3, 28, 20);	setBox(4, 24, 0);	setBox(5, 28, 0);
		setBox(6, 16, 19);	setBox(7, 19, 19);	setBox(8, 24, 23);	setBox(9, 28, 23);	setBox(10, 24, 3);	setBox(11, 28, 3);
		setBox(12, 24, 4);	setBox(13, 28, 4);	setBox(14, 24, 8);	setBox(15, 28, 8);	setBox(16, 24, 12);	setBox(17, 28, 12);
		setBox(18, 24, 7);	setBox(19, 28, 7);	setBox(20, 24, 11);	setBox(21, 28, 11);	setBox(22, 24, 15);	setBox(23, 28, 15);
		setBox(24, 24, 16);	setBox(25, 28, 16);	setBox(26, 0, 0);	setBox(27, 3, 0);	setBox(28, 4, 0);	setBox(29, 7, 0);
		setBox(30, 24, 19);	setBox(31, 28, 19);	setBox(32, 0, 4);	setBox(33, 3, 4);	setBox(34, 4, 4);	setBox(35, 7, 4);

		setBox(36, 8, 0);	setBox(37, 11, 0);	setBox(38, 0, 5);	setBox(39, 3, 5);	setBox(40, 4, 5);	setBox(41, 7, 5);
		setBox(42, 8, 4);	setBox(43, 11, 4);	setBox(44, 0, 9);	setBox(45, 3, 9);	setBox(46, 4, 9);	setBox(47, 7, 9);
		setBox(48, 8, 5);	setBox(49, 11, 5);	setBox(50, 1, 11);	setBox(51, 5, 11);	setBox(52, 9, 11);	setBox(53, 13, 11);
		setBox(54, 8, 9);	setBox(55, 11, 9);	setBox(56, 1, 12);	setBox(57, 5, 12);	setBox(58, 9, 12);	setBox(59, 13, 12);
		setBox(60, 17, 11);	setBox(61, 1, 16);	setBox(62, 5, 16);	setBox(63, 9, 16);	setBox(64, 13, 16);	setBox(65, 17, 16);
		setBox(66, 17, 12);	setBox(67, 1, 17);	setBox(68, 5, 17);	setBox(69, 9, 17);	setBox(70, 13, 17);	setBox(71, 17, 17);
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
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
			_box[temp2].center = PointMake(_center.x + (BOOKSIZEX / 14) * (j + 1), (_center.y + BOOKSIZEY / 2 - 20) - 55 * ((5 - i) + 1));
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
		}
	}
}

void page1::setBox(int index, int frameX, int frameY)
{
	_box[index].frameX = frameX;
	_box[index].frameY = frameY;
}