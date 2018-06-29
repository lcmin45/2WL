#include "stdafx.h"
#include "mapToolBook.h"

mapToolBook::mapToolBook() {}

mapToolBook::~mapToolBook() {}

HRESULT mapToolBook::init(void)
{
	imageInit();
	bookInit();
	//////
	for (int i = 0; i < MAXPAGE + 1; ++i)
	{
		_mapPage[i] = new mapToolPage;
		if (i == 0) _mapPage[i]->init(0);
		else _mapPage[i]->init((i + 1) / 2);
	}




	return S_OK;
}

void mapToolBook::release(void)
{

}

void mapToolBook::update(void)
{
	inputKey();
	frame();
	//
	for (int i = 0; i < MAXPAGE + 1; ++i) _mapPage[i]->checkCenter(_book.center);
}

void mapToolBook::render(void)
{
	iconRender();
	bookRender();
	//
	testRender();
	//
	pageRender();
	markRender();

}

///////////
void mapToolBook::testRender(void)
{
	if (!_book.isOpenCheck) return;

	_mapPage[_mark.pageIndex]->render();
}
////////////////

void mapToolBook::imageInit(void)
{
	IMAGEMANAGER->addFrameImage("BOOKICON", "image/mapTool/bookAnimation.bmp", 1200, 104, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OPENBOOK", "image/mapTool/bookOpen.bmp", 960, 18900, 1, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOOKMARK", "image/mapTool/number2.bmp", 90, 324, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PAGEMOVE", "image/mapTool/page.bmp", 1920, 3240, 2, 6, true, RGB(255, 0, 255));
}

void mapToolBook::bookInit(void)
{
	_book.img = IMAGEMANAGER->findImage("OPENBOOK");
	_book.center = PointMake(WINSIZEX / 2, WINSIZEY / 2);
	_book.frameIndex = _book.frameX = _book.frameY = 0;
	_book.isView = _book.isMove = _book.isOpenCheck = _book.isCloseCheck = false;

	_icon.img = IMAGEMANAGER->findImage("BOOKICON");
	_icon.center = PointMake(WINSIZEX - _icon.img->getFrameWidth() / 2, _icon.img->getFrameHeight() / 2);
	_icon.frameIndex = _icon.frameX = _icon.frameY = 0;
	_icon.isView = true;

	_mark.leftImg = IMAGEMANAGER->findImage("BOOKMARK");
	_mark.leftPoint = PointMake(_book.center.x - BOOKSIZEX / 2 - _mark.leftImg->getWidth() / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	_mark.rightImg = IMAGEMANAGER->findImage("BOOKMARK");
	_mark.rightPoint = PointMake(_book.center.x + BOOKSIZEX / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	_mark.pageIndex = 0;

	_page.img = IMAGEMANAGER->findImage("PAGEMOVE");
	_page.frameIndex = _page.frameX = _page.frameY = 0;
	_page.checkIndex = 0;
}

void mapToolBook::inputKey(void)
{
	// 책 오픈용 버튼 추후 변경
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		if (_icon.isView)	openBook();
		else				closeBook();
	}

	moveBook();
	changePage();
}

void mapToolBook::moveBook(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))	_book.isMove = true;
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))		_book.isMove = false;

	if (!_book.isMove) return;

	int moveSpeed = 5;

	if (KEYMANAGER->isStayKeyDown('W')) _book.center = PointMake(_book.center.x, _book.center.y - moveSpeed);
	if (KEYMANAGER->isStayKeyDown('A')) _book.center = PointMake(_book.center.x - moveSpeed, _book.center.y);
	if (KEYMANAGER->isStayKeyDown('S')) _book.center = PointMake(_book.center.x, _book.center.y + moveSpeed);
	if (KEYMANAGER->isStayKeyDown('D')) _book.center = PointMake(_book.center.x + moveSpeed, _book.center.y);

	_mark.leftPoint = PointMake(_book.center.x - BOOKSIZEX / 2 - _mark.leftImg->getWidth() / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	_mark.rightPoint = PointMake(_book.center.x + BOOKSIZEX / 2, _book.center.y - BOOKSIZEY / 2 + 50);
}

void mapToolBook::changePage(void)
{
	if (!_book.isOpenCheck) return;

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_mark.pageIndex == 0) return;

		changePage(false);
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_mark.pageIndex == MAXPAGE) return;

		changePage(true);
	}
}

void mapToolBook::frame(void)
{
	iconFrame();
	bookFrame();
	pageFrame();
}

void mapToolBook::iconFrame(void)
{
	if (!_icon.isView) return;

	_icon.frameIndex += 1;

	if (_icon.frameIndex % 6 == 0)
	{
		_icon.frameX += 1;
		if (_icon.frameX > _icon.img->getMaxFrameX()) _icon.frameX = 0;
		_icon.frameIndex = 0;
	}
}

void mapToolBook::bookFrame(void)
{
	if (!_book.isView) return;

	if (_book.isCloseCheck)
	{
		_book.frameIndex += 1;

		if (_book.frameIndex % 6 == 0)
		{
			_book.frameY -= 1;
			if (_book.frameY == 0)
			{
				_book.isView = false;
				_book.isCloseCheck = false;
				_book.isOpenCheck = false;
				_icon.isView = true;
			}
			_book.frameIndex = 0;
		}
	}

	if (_book.isOpenCheck || _book.isCloseCheck) return;

	_book.frameIndex += 1;

	if (_book.frameIndex % 6 == 0)
	{
		_book.frameY += 1;
		if (_book.frameY == _book.img->getMaxFrameY()) _book.isOpenCheck = true;
		_book.frameIndex = 0;
	}

}

void mapToolBook::pageFrame(void)
{
	if (!_page.isView) return;

	_page.frameIndex += 1;

	if (_page.frameIndex % 6 == 0)
	{
		_page.frameY -= 1;
		if (_page.frameY == 0) _page.isView = false;
		_page.frameIndex = 0;
	}
}

void mapToolBook::iconRender(void)
{
	if (!_icon.isView) return;

	_icon.img->frameRender(getMemDC(), _icon.center.x - _icon.img->getFrameWidth() / 2,
		_icon.center.y - _icon.img->getFrameHeight() / 2, _icon.frameX, _icon.frameY);
}

void mapToolBook::bookRender(void)
{
	if (!_book.isView) return;

	_book.img->frameRender(getMemDC(), _book.center.x - _book.img->getFrameWidth() / 2,
		_book.center.y - _book.img->getFrameHeight() / 2, _book.frameX, _book.frameY);
}

void mapToolBook::pageRender(void)
{
	if (!_page.isView) return;

	_page.img->frameRender(getMemDC(), _book.center.x - _book.img->getFrameWidth() / 2,
		_book.center.y - _book.img->getFrameHeight() / 2, _page.frameX, _page.frameY);
}

void mapToolBook::markRender(void)
{
	if (!_book.isOpenCheck) return;

	_mark.leftImg->render(getMemDC(), _mark.leftPoint.x, _mark.leftPoint.y,
		0, 0,
		_mark.leftImg->getWidth() / 2, (_mark.leftImg->getHeight() / (MAXPAGE + 1)) * (_mark.pageIndex + 1));

	_mark.rightImg->render(getMemDC(),
		_mark.rightPoint.x,
		_mark.rightPoint.y + ((_mark.rightImg->getHeight() / (MAXPAGE + 1)) * (_mark.pageIndex + 1)),
		_mark.rightImg->getWidth() / 2,
		_mark.rightImg->getHeight() / (MAXPAGE + 1) * (_mark.pageIndex + 1),
		_mark.rightImg->getWidth() / 2,
		_mark.rightImg->getHeight() - ((_mark.rightImg->getHeight() / (MAXPAGE + 1)) * (_mark.pageIndex + 1)));
}

void mapToolBook::openBook(void)
{
	_icon.isView = false;
	_book.isView = true;
	_book.frameIndex = 0;
	_book.frameY = 0;
}

void mapToolBook::closeBook(void)
{
	_book.isCloseCheck = true;
	_book.isOpenCheck = false;
	_book.frameIndex = 0;
	_book.frameY = _book.img->getMaxFrameY();
}

void mapToolBook::changePage(bool isNext)
{
	_page.frameY = _page.img->getMaxFrameY();
	_page.isView = true;

	if (isNext)
	{
		_page.frameX = 0;
		_mark.pageIndex += 1;
	}
	else
	{
		_page.frameX = 1;
		_mark.pageIndex -= 1;
	}
}s