#include "stdafx.h"
#include "mapToolPage.h"


mapToolPage::mapToolPage() {}

mapToolPage::~mapToolPage() {}

HRESULT mapToolPage::init(int index)
{
	imageInit();
	checkPage(index);
	  
	for (int i = 0; i < 6; ++i)
	{
		_title[i].img = IMAGEMANAGER->findImage("title");
	}


	return S_OK;
}

void mapToolPage::release(void)
{
}

void mapToolPage::update(void)
{

}

void mapToolPage::render(void)
{
	switch (_pageIndex)
	{
	case 0:
	{
		for (int i = 0; i < 6; ++i)
		{
			_title[i].img->render(getMemDC(),
				_center.x + BOOKSIZEX / 4 - _title[i].img->getWidth() / 2,
				_center.y + BOOKSIZEY / 2 - 50 * i - 100);
		}
	}
	break;
	case 1:
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				_box[i * 6 + j].img->frameRender(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * (j + 1) - 21 + 4,
					(_center.y + BOOKSIZEY / 2 - 20) - (55) * (i + 1) - 21 + 4,
					_box[i * 6 + j].frameX,
					_box[i * 6 + j].frameY);
			}
		}

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				_box[i * 6 + j].edgeImg->render(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * (j + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - (55) * (i + 1) - 21);
			}
		}

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				_box[i * 6 + j].edgeImg->render(getMemDC(),
					(_center.x) + (BOOKSIZEX / 2 / 7) * (j + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - (55) * (i + 1) - 21);
			}
		}
	}
	break;
	case 2:
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i * 3 + j > 4) continue;

				_box[i * 3 + j].img->frameRender(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * ((j * 2) + 1) - 21 + 4,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21 + 4,
					_box[i * 3 + j].frameX,
					_box[i * 3 + j].frameY);
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				_box[i * 3 + j].edgeImg->render(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * ((j * 2) + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21);
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				_box[i * 3 + j].edgeImg->render(getMemDC(),
					(_center.x) + (BOOKSIZEX / 2 / 7) * ((j * 2) + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21);
			}
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				_box[i * 3 + j].edgeImg->render(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * ((j * 2) + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * (i + 1) - 21);
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				_box[i * 3 + j + 18].edgeImg->render(getMemDC(),
					(_center.x) + (BOOKSIZEX / 2 / 7) * ((j + 1)) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21);
			}
		}
	}
	break;
	case 4:
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				_box[i * 2 + j].edgeImg->render(getMemDC(),
					(_center.x - BOOKSIZEX / 2) + (BOOKSIZEX / 2 / 7) * ((j * 3) + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21);
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				_box[i * 2 + j].edgeImg->render(getMemDC(),
					(_center.x) + (BOOKSIZEX / 2 / 7) * ((j * 3) + 1) - 21,
					(_center.y + BOOKSIZEY / 2 - 20) - 55 * ((i * 2) + 2) - 21);
			}
		}
	}
	break;
	}

	RectangleMakeCenter(getMemDC(), _center.x, _center.y, 10, 10);
}

void mapToolPage::imageInit(void)
{
	IMAGEMANAGER->addImage("title2", "image/mapTool/title.bmp", 114, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title", "image/mapTool/title2.bmp", 171, 42, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("BASE_1_1", "image/mapTool/view_1_1.bmp", 42, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BASE_1_2", "image/mapTool/view_1_2.bmp", 42, 97, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BASE_2_1", "image/mapTool/view_2_1.bmp", 93, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BASE_2_2", "image/mapTool/view_2_2.bmp", 93, 97, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BASE_3_2", "image/mapTool/view_3_2.bmp", 144, 97, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("SAMPLETILE", "image/mapTool/sampleTile.bmp", 320, 224, 10, 7, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("OBJECT", "image/mapTool/object_2_2_1.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
}

void mapToolPage::checkPage(int index)
{
	_pageIndex = index;

	switch (_pageIndex)
	{
	case 0:
	{
		return;
	}
	break;
	case 1:
	{
		for (int i = 0; i < 36; ++i)
		{
			_box[i].edgeImg = IMAGEMANAGER->findImage("BASE_1_1"); //포인터
			_box[i].img = IMAGEMANAGER->findImage("SAMPLETILE");
			_box[i].frameX = i / 6;
			_box[i].frameY = i % 6;
		}
	}
	break;
	case 2:
	{
		for (int i = 0; i < 9; ++i)
		{
			_box[i].edgeImg = IMAGEMANAGER->findImage("BASE_2_2"); //포인터
			_box[i].img = IMAGEMANAGER->findImage("OBJECT");
			if (i > 4) continue;
			_box[i].frameX = i;
			_box[i].frameY = 0;
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < 18; ++i)
		{
			_box[i].edgeImg = IMAGEMANAGER->findImage("BASE_2_1"); //포인터
			_box[i + 18].edgeImg = IMAGEMANAGER->findImage("BASE_1_2"); //포인터
		}
	}
	break;
	case 4:
	{
		for (int i = 0; i < 6; ++i)
		{
			_box[i].edgeImg = IMAGEMANAGER->findImage("BASE_3_2"); //포인터
		}
	}
	break;
	}

}

void mapToolPage::checkCenter(POINT bookCenter)
{
	_center = bookCenter;
}