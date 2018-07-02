#include "stdafx.h"
#include "mapToolBook.h"

mapToolBook::mapToolBook() {}

mapToolBook::~mapToolBook() {}

HRESULT mapToolBook::init(void)
{
	imageInit();
	bookInit();
	animationInit();
	
	return S_OK;
}

void mapToolBook::release(void) { }

void mapToolBook::update(void)
{
	inputKey();
	checkPageIndexCenter();
	_page->update();
	checkMousePoint();
}

void mapToolBook::render(void)
{
	iconRender();
	bookRender();
	markRender();	
	pageRender();
	pageChangeRender();
}

void mapToolBook::imageInit(void)
{
	IMAGEMANAGER->addFrameImage("BOOKICON", "image/mapTool/bookAnimation.bmp", 1200, 104, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OPENBOOK", "image/mapTool/bookOpen.bmp", 960, 18900, 1, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOOKMARK", "image/mapTool/number.bmp", 90, 324, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PAGEMOVE", "image/mapTool/page.bmp", 1920, 3240, 2, 6, true, RGB(255, 0, 255));
}

void mapToolBook::bookInit(void)
{
	_book.img = IMAGEMANAGER->findImage("OPENBOOK");
	_book.center = PointMake(WINSIZEX / 2, WINSIZEY / 2);
	_book.isView = _book.isMove = _book.isOpen = false;
	_book.pageIndex = 0;
	_book.moveSpeed = 10;

	_icon.img = IMAGEMANAGER->findImage("BOOKICON");
	_icon.center = PointMake(WINSIZEX - _icon.img->getFrameWidth() / 2, _icon.img->getFrameHeight() / 2);

	_mark.leftImg = IMAGEMANAGER->findImage("BOOKMARK");
	_mark.leftPoint = PointMake(_book.center.x - BOOKSIZEX / 2 - _mark.leftImg->getWidth() / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	_mark.rightImg = IMAGEMANAGER->findImage("BOOKMARK");
	_mark.rightPoint = PointMake(_book.center.x + BOOKSIZEX / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	
	_pageChange.img = IMAGEMANAGER->findImage("PAGEMOVE");
	_pageChange.isView = false;

	_page = new pageManager;
	_page->init();

	_isMouseBook = false;
}

void mapToolBook::animationInit(void)
{
	// 책
	int openBook[]	= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };
	KEYANIMANAGER->addArrayFrameAnimation("OPEN_BOOK", "OPENBOOK", openBook, 35, 15, false, openBookC, this);
	int closeBook[] = { 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("CLOSE_BOOK", "OPENBOOK", closeBook, 35, 15, false, closeBookC, this);

	// 아이콘
	int bookIcon[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("BOOK_ICON", "BOOKICON", bookIcon, 15, 6, true);
	_icon.ani = KEYANIMANAGER->findAnimation("BOOK_ICON");
	_icon.ani->start();

	// 페이지 변경
	int nextPage[] = { 10, 8, 6, 4, 2, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("NEXT_PAGE", "PAGEMOVE", nextPage, 6, 10, false, changePageC, this);

	int beforPage[] = { 11, 9, 7, 5, 3, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("BEFORE_PAGE", "PAGEMOVE", beforPage, 6, 10, false, changePageC, this);
}

void mapToolBook::inputKey(void)
{
	openBookKey();
	moveBookKey();
	changePageKey();
}

void mapToolBook::openBookKey(void)
{
	if (!_book.isOpen && _book.isView) return;

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_book.isView)	closeBook();
		else				openBook();
	}
}

void mapToolBook::moveBookKey(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))	_book.isMove = true;
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))		_book.isMove = false;

	if (!_book.isMove) return;

	if (KEYMANAGER->isStayKeyDown('W')) _book.center = PointMake(_book.center.x, _book.center.y - _book.moveSpeed);
	if (KEYMANAGER->isStayKeyDown('A')) _book.center = PointMake(_book.center.x - _book.moveSpeed, _book.center.y);
	if (KEYMANAGER->isStayKeyDown('S')) _book.center = PointMake(_book.center.x, _book.center.y + _book.moveSpeed);
	if (KEYMANAGER->isStayKeyDown('D')) _book.center = PointMake(_book.center.x + _book.moveSpeed, _book.center.y);

	if (_book.center.x < 0)			_book.center.x = 0;
	if (_book.center.x > WINSIZEX)	_book.center.x = WINSIZEX;
	if (_book.center.y < 0)			_book.center.y = 0;
	if (_book.center.y > WINSIZEY)	_book.center.y = WINSIZEY;

	_mark.leftPoint = PointMake(_book.center.x - BOOKSIZEX / 2 - _mark.leftImg->getWidth() / 2, _book.center.y - BOOKSIZEY / 2 + 50);
	_mark.rightPoint = PointMake(_book.center.x + BOOKSIZEX / 2, _book.center.y - BOOKSIZEY / 2 + 50);
}

void mapToolBook::changePageKey(void)
{
	if (!_book.isOpen) return;

	if (KEYMANAGER->isOnceKeyDown('E') && _book.pageIndex != MAXPAGE) nextPage();

	if (KEYMANAGER->isOnceKeyDown('Q') && _book.pageIndex != 0) beforePage();
}

void mapToolBook::checkPageIndexCenter(void)
{
	if (!_book.isOpen) return;

	_page->setPageIndex(_book.pageIndex);
	_page->setCenterPoint(_book.center);
}

void mapToolBook::checkMousePoint(void)
{
	if (!_book.isView) return;

	if (getCameraPoint().x > _book.center.x - BOOKSIZEX / 2 &&
		getCameraPoint().x < _book.center.x + BOOKSIZEX / 2 &&
		getCameraPoint().y > _book.center.y - BOOKSIZEY / 2 &&
		getCameraPoint().y < _book.center.y + BOOKSIZEY / 2)
	{
		_isMouseBook = true;
	}
	else _isMouseBook = false;
}

void mapToolBook::iconRender(void)
{
	if (_book.isView) return;

	_icon.img->aniRender(CAMERAMANAGER->getCameraDC(), _icon.center.x - _icon.img->getFrameWidth() / 2 - 20,
		_icon.center.y - _icon.img->getFrameHeight() / 2 + 20, _icon.ani);
}

void mapToolBook::bookRender(void)
{
	if (!_book.isView) return;
	
	if (_book.isOpen)
	{
		_book.img->frameRender(CAMERAMANAGER->getCameraDC(), _book.center.x - _book.img->getFrameWidth() / 2,
			_book.center.y - _book.img->getFrameHeight() / 2, 0, 34);
	}
	else
	{
		_book.img->aniRender(CAMERAMANAGER->getCameraDC(), _book.center.x - _book.img->getFrameWidth() / 2,
			_book.center.y - _book.img->getFrameHeight() / 2, _book.ani);
	}	
}

void mapToolBook::markRender(void)
{
	if (!_book.isOpen) return;

	_mark.leftImg->render(CAMERAMANAGER->getCameraDC(), _mark.leftPoint.x, _mark.leftPoint.y,
		0, 0, 
		_mark.leftImg->getWidth() / 2, (_mark.leftImg->getHeight() / (MAXPAGE + 1)) * (_book.pageIndex + 1));

	_mark.rightImg->render(CAMERAMANAGER->getCameraDC(),
		_mark.rightPoint.x, 
		_mark.rightPoint.y + ((_mark.rightImg->getHeight() / (MAXPAGE + 1)) * (_book.pageIndex + 1)),
		_mark.rightImg->getWidth() / 2, 
		_mark.rightImg->getHeight() / (MAXPAGE + 1) * (_book.pageIndex + 1),
		_mark.rightImg->getWidth() / 2, 
		_mark.rightImg->getHeight() - ((_mark.rightImg->getHeight() / (MAXPAGE + 1)) * (_book.pageIndex + 1)));
}

void mapToolBook::pageRender(void)
{
	if (!_book.isOpen) return;

	_page->render();
}

void mapToolBook::pageChangeRender(void)
{
	if (!_pageChange.isView) return;

	_pageChange.img->aniRender(CAMERAMANAGER->getCameraDC(), _book.center.x - _book.img->getFrameWidth() / 2,
		_book.center.y - _book.img->getFrameHeight() / 2, _pageChange.ani);
}


void mapToolBook::openBook(void)
{
	_book.isView = true;
	_book.ani = KEYANIMANAGER->findAnimation("OPEN_BOOK");
	_book.ani->start();
}

void mapToolBook::closeBook(void)
{
	_book.isOpen = false;
	_book.ani = KEYANIMANAGER->findAnimation("CLOSE_BOOK");
	_book.ani->start();
}

void mapToolBook::nextPage(void)
{
	_pageChange.ani = KEYANIMANAGER->findAnimation("NEXT_PAGE");
	_book.pageIndex += 1;
	_pageChange.isView = true;
	_pageChange.ani->start();
}

void mapToolBook::beforePage(void)
{
	_pageChange.ani = KEYANIMANAGER->findAnimation("BEFORE_PAGE");
	_book.pageIndex -= 1;
	_pageChange.isView = true;
	_pageChange.ani->start();
}

void mapToolBook::openBookC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_book.isOpen = true;
}

void mapToolBook::closeBookC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_book.isView = false;
}

void mapToolBook::changePageC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_pageChange.isView = false;
}