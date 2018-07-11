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
	checkBox();
}

void page2::render(void)
{
	titleRender();
	tileRender();
	boxRender();
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

			_box[temp].boxImageName = "PAGE_BOX_2_2";
			_box[temp].center = PointMake((_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 14) * ((j * 2) + 1) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());
			_box[temp].imageObjectIndex = NULL;
			_box[temp].frameX = NULL;
			_box[temp].frameY = NULL;

			_box[temp2].boxImageName = "PAGE_BOX_2_2";
			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
			_box[temp2].imageObjectIndex = NULL;
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

void page2::tileRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		// 지금만 삭제
		if (_box[i].imageObjectIndex == NULL) continue;

		IMAGEMANAGER->findImage(_box[i].objectImageName)->frameRender(CAMERAMANAGER->getCameraDC(),
			_box[i].center.x - IMAGEMANAGER->findImage(_box[i].objectImageName)->getFrameWidth() / 2,
			_box[i].center.y - IMAGEMANAGER->findImage(_box[i].objectImageName)->getFrameHeight() / 2,
			_box[i].frameX, _box[i].frameY);
	}
}

void page2::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxImageName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);
	}
}

void page2::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBOX; ++i)
		{
			if (PtInRect(&_box[i].rc, getCameraPoint()))
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
				break;
			}
		}
	}
}

void page2::setIndex(int index)
{
	_titleImage[0] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");
	_titleImage[1] = IMAGEMANAGER->findImage("FONT_TITLE_OBJECT");

	switch (index)
	{
	case 0:
		for (int i = 0; i < 12; ++i)
		{
			_box[i].objectImageName = "IMAGE_OBJECT_2_2";
			_box[i].imageObjectIndex = 22;
			_box[i].frameX = i % 6;
			_box[i].frameY = i / 6;
			_box[i].objectSetPoint = LEFT_BOTTOM;
			_box[i].renderPoint = PointMake(16, 48);
			_box[i].objectCheckSize = PointMake(2, 2);
			_box[i].terrain = TR_WAY;
		}

		for (int i = 0; i < 6; ++i)
		{
			_box[12 + i].objectImageName = "IMAGE_OBJECT_3_4";
			_box[12 + i].imageObjectIndex = 34;
			_box[12 + i].frameX = i;
			_box[12 + i].frameY = 0;
			_box[12 + i].objectSetPoint = LEFT_BOTTOM;
			_box[12 + i].renderPoint = PointMake(16, 80);
			_box[12 + i].objectCheckSize = PointMake(2, 3);
			_box[12 + i].terrain = TR_WAY;
		}

		break;
	case 1:
		for (int i = 0; i < MAXBOX; ++i)
		{
			_box[i].objectImageName = "IMAGE_OBJECT_2_3";
			_box[i].imageObjectIndex = 23;
			_box[i].frameX = i % 9;
			_box[i].frameY = i / 9;
			_box[i].objectSetPoint = LEFT_BOTTOM;
			_box[i].renderPoint = PointMake(16, 80);
			_box[i].objectCheckSize = PointMake(2, 3);
			_box[i].terrain = TR_WAY;
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
			_box[temp].rc = RectMakeCenter(_box[temp].center.x, _box[temp].center.y, IMAGEMANAGER->findImage(_box[temp].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp].boxImageName)->getHeight());

			_box[temp2].center = PointMake(_center.x + BOOKSIZEX / 14 * ((j * 2 + 1)) - 21 + 47, (_center.y + BOOKSIZEY / 2 - 20) - 55 * (((2 - i) * 2) + 2) - 21 + 49);
			_box[temp2].rc = RectMakeCenter(_box[temp2].center.x, _box[temp2].center.y, IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[temp2].boxImageName)->getHeight());
		}
	}
}