#include "stdafx.h"
#include "page0.h"
#include "mapTile.h"

page0::page0() { }

page0::~page0() { }

HRESULT page0::init(void)
{
	boxInit();

	return S_OK;
}

void page0::release(void)
{

}

void page0::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('X')) _mapTile->save();
	checkBox();
}

void page0::render(void)
{
	boxRender();
	fontRender();
}

void page0::boxInit(void)
{
	_center = WINCENTER;

	for (int i = 0; i < MAXBOX; ++i)
	{
		_box[i].boxImageName = "FONT_BOX";
		_box[i].center = PointMake(_center.x + BOOKSIZEX / 4 - IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth() / 2 + IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth() / 2, _center.y + BOOKSIZEY / 2 - 50 * (5 - i) - 100 + IMAGEMANAGER->findImage(_box[i].boxImageName)->getHeight() / 2);
		_box[i].rc = RectMakeCenter(_box[i].center.x, _box[i].center.y, IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[i].boxImageName)->getHeight());
	}
}

void page0::checkBox(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBOX; ++i)
		{
			if (PtInRect(&_box[i].rc, getCameraPoint()))
			{
				switch (i)
				{
				case 0: _currentCheck = CH_TERRAIN;
					break;
				case 1: _currentCheck = CH_TERRAIN;
					break;
				case 2:	_currentCheck = CH_ROOM_INDEX;
					break;
				case 3: _mapTile->save();
					break;
				case 4: _mapTile->load();
					break;
				case 5: _mapTile->minimap();
					break;
				}
				break;
			}
		}
	}
}

void page0::boxRender(void)
{
	for (int i = 0; i < MAXBOX; ++i)
	{
		IMAGEMANAGER->findImage(_box[i].boxImageName)->render(CAMERAMANAGER->getCameraDC(), _box[i].rc.left, _box[i].rc.top);
	}
}

void page0::fontRender(void)
{
	IMAGEMANAGER->findImage("FONT_PAGE0")->render(CAMERAMANAGER->getCameraDC(), _center.x - IMAGEMANAGER->findImage("FONT_PAGE0")->getWidth() / 2, _center.y - IMAGEMANAGER->findImage("FONT_PAGE0")->getHeight() / 2);

	IMAGEMANAGER->findImage("FONT_WAY")->render(CAMERAMANAGER->getCameraDC(), _box[0].center.x - IMAGEMANAGER->findImage("FONT_WAY")->getWidth() / 2,
		_box[0].center.y - IMAGEMANAGER->findImage("FONT_WAY")->getHeight() / 2);
	IMAGEMANAGER->findImage("FONT_WALL")->render(CAMERAMANAGER->getCameraDC(), _box[1].center.x - IMAGEMANAGER->findImage("FONT_WALL")->getWidth() / 2,
		_box[1].center.y - IMAGEMANAGER->findImage("FONT_WALL")->getHeight() / 2);
	IMAGEMANAGER->findImage("FONT_OBJECT")->render(CAMERAMANAGER->getCameraDC(), _box[2].center.x - IMAGEMANAGER->findImage("FONT_OBJECT")->getWidth() / 2,
		_box[2].center.y - IMAGEMANAGER->findImage("FONT_OBJECT")->getHeight() / 2);
	IMAGEMANAGER->findImage("FONT_SAVE")->render(CAMERAMANAGER->getCameraDC(), _box[3].center.x - IMAGEMANAGER->findImage("FONT_SAVE")->getWidth() / 2,
		_box[3].center.y - IMAGEMANAGER->findImage("FONT_SAVE")->getHeight() / 2);
	IMAGEMANAGER->findImage("FONT_LOAD")->render(CAMERAMANAGER->getCameraDC(), _box[4].center.x - IMAGEMANAGER->findImage("FONT_LOAD")->getWidth() / 2,
		_box[4].center.y - IMAGEMANAGER->findImage("FONT_LOAD")->getHeight() / 2);
	IMAGEMANAGER->findImage("FONT_MINIMAP")->render(CAMERAMANAGER->getCameraDC(), _box[5].center.x - IMAGEMANAGER->findImage("FONT_MINIMAP")->getWidth() / 2,
		_box[5].center.y - IMAGEMANAGER->findImage("FONT_MINIMAP")->getHeight() / 2);
}

void page0::setCenterPoint(POINT point)
{
	_center = point;

	for (int i = 0; i < MAXBOX; ++i)
	{
		_box[i].center = PointMake(_center.x + BOOKSIZEX / 4 - IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth() / 2 + IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth() / 2, _center.y + BOOKSIZEY / 2 - 50 * (5 - i) - 100 + IMAGEMANAGER->findImage(_box[i].boxImageName)->getHeight() / 2);
		_box[i].rc = RectMakeCenter(_box[i].center.x, _box[i].center.y, IMAGEMANAGER->findImage(_box[i].boxImageName)->getWidth(), IMAGEMANAGER->findImage(_box[i].boxImageName)->getHeight());
	}
}