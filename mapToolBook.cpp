#include "stdafx.h"
#include "mapToolBook.h"

mapToolBook::mapToolBook()
{
	_mapToolBookIndex += 1;
}

mapToolBook::~mapToolBook() {}

HRESULT mapToolBook::init(int index)
{
	_mapToolBookIndex = index;
	bookInit();
	pageInit();
	animationInit();
	_isMouseOnBook = false;

	return S_OK;
}

void mapToolBook::release(void)
{
	SAFE_RELEASE(_pageManager);
}

void mapToolBook::update(void)
{
	inputKey();
	checkPageIndexCenter();
	pageUpdate();
	checkMouseOnBook();
}

void mapToolBook::render(void)
{
	iconRender();
	bookRender();
	markRender();
	pageManagerRender();
	pageChangeRender();
}

void mapToolBook::bookInit(void)
{
	_mainBook.bookImg = IMAGEMANAGER->findImage("MAIN_BOOK");
	_mainBook.center = PointMake(WINSIZEX / 2, WINSIZEY / 2);
	_mainBook.isView = _mainBook.isMove = _mainBook.isOpen = false;
	_mainBook.pageIndex = 0;
	_mainBook.moveSpeed = 10;

	_iconBook.iconImg = IMAGEMANAGER->findImage("MINI_ICON_BOOK");
	_iconBook.center = PointMake(WINSIZEX - _iconBook.iconImg->getFrameWidth() / 2, _iconBook.iconImg->getFrameHeight() / 2);

	_bookMark.markImg = IMAGEMANAGER->findImage("MAIN_BOOK_MARK");
	_bookMark.leftPoint = PointMake(_mainBook.center.x - BOOKSIZEX / 2 - _bookMark.markImg->getWidth() / 2, _mainBook.center.y - BOOKSIZEY / 2 + 25);
	_bookMark.rightPoint = PointMake(_mainBook.center.x + BOOKSIZEX / 2, _mainBook.center.y - BOOKSIZEY / 2 + 25);

	_pageChange.pageChangeImg = IMAGEMANAGER->findImage("MAIN_BOOK_CHANGE");
	_pageChange.isView = false;
}

void mapToolBook::pageInit(void)
{
	_pageManager = new pageManager;
	_pageManager->init();
}

void mapToolBook::animationInit(void)
{
	// 책
	char str[128];
	sprintf_s(str, "MAIN_BOOK_OPEN_ANI_%d", _mapToolBookIndex);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "MAIN_BOOK", 0, 34, 15, false, false, openBookC, this);
	sprintf_s(str, "MAIN_BOOK_CLOSE_ANI_%d", _mapToolBookIndex);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "MAIN_BOOK", 34, 0, 15, false, false, closeBookC, this);

	// 아이콘
	KEYANIMANAGER->addCoordinateFrameAnimation("MINI_ICON_BOOK_ANI", "MINI_ICON_BOOK", 0, 14, 6, false, true);
	_iconBook.ani = KEYANIMANAGER->findAnimation("MINI_ICON_BOOK_ANI");
	_iconBook.ani->start();

	// 페이지 변경
	int nextPage[] = { 10, 8, 6, 4, 2, 0 };
	sprintf_s(str, "MAIN_BOOK_CHANGE_NEXT_ANI_%d", _mapToolBookIndex);
	KEYANIMANAGER->addArrayFrameAnimation(str, "MAIN_BOOK_CHANGE", nextPage, 6, 10, false, changePageC, this);

	int beforPage[] = { 11, 9, 7, 5, 3, 1 };
	sprintf_s(str, "MAIN_BOOK_CHANGE_BEFORE_ANI_%d", _mapToolBookIndex);
	KEYANIMANAGER->addArrayFrameAnimation(str, "MAIN_BOOK_CHANGE", beforPage, 6, 10, false, changePageC, this);
}

void mapToolBook::inputKey(void)
{
	openBookKey();
	moveBookKey();
	changePageKey();
}

void mapToolBook::openBookKey(void)
{
	// 책을 펼치거나 접는 중 일때는 동작하지 마라
	if (!_mainBook.isOpen && _mainBook.isView) return;

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_mainBook.isView)	closeBook();
		else					openBook();
	}
}

void mapToolBook::moveBookKey(void)
{
	// 쉬프트 키로 책만 움직임 설정
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))	_mainBook.isMove = true;
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))		_mainBook.isMove = false;

	if (!_mainBook.isMove) return;

	if (KEYMANAGER->isStayKeyDown('W')) _mainBook.center = PointMake(_mainBook.center.x, _mainBook.center.y - _mainBook.moveSpeed);
	if (KEYMANAGER->isStayKeyDown('A')) _mainBook.center = PointMake(_mainBook.center.x - _mainBook.moveSpeed, _mainBook.center.y);
	if (KEYMANAGER->isStayKeyDown('S')) _mainBook.center = PointMake(_mainBook.center.x, _mainBook.center.y + _mainBook.moveSpeed);
	if (KEYMANAGER->isStayKeyDown('D')) _mainBook.center = PointMake(_mainBook.center.x + _mainBook.moveSpeed, _mainBook.center.y);

	if (_mainBook.center.x < 0)			_mainBook.center.x = 0;
	if (_mainBook.center.x > WINSIZEX)	_mainBook.center.x = WINSIZEX;
	if (_mainBook.center.y < 0)			_mainBook.center.y = 0;
	if (_mainBook.center.y > WINSIZEY)	_mainBook.center.y = WINSIZEY;

	_bookMark.leftPoint = PointMake(_mainBook.center.x - BOOKSIZEX / 2 - _bookMark.markImg->getWidth() / 2, _mainBook.center.y - BOOKSIZEY / 2 + 25);
	_bookMark.rightPoint = PointMake(_mainBook.center.x + BOOKSIZEX / 2, _mainBook.center.y - BOOKSIZEY / 2 + 25);
}

void mapToolBook::changePageKey(void)
{
	if (!_mainBook.isOpen) return;

	if (KEYMANAGER->isOnceKeyDown('E') && _mainBook.pageIndex != MAXPAGE)	nextPage();
	if (KEYMANAGER->isOnceKeyDown('Q') && _mainBook.pageIndex != 0)			beforePage();
}

void mapToolBook::checkPageIndexCenter(void)
{
	if (!_mainBook.isOpen) return;

	_pageManager->setPageIndex(_mainBook.pageIndex);
	_pageManager->setCenterPoint(_mainBook.center);
}

void mapToolBook::pageUpdate()
{
	if (!_mainBook.isOpen) return;

	_pageManager->update();
}

void mapToolBook::checkMouseOnBook(void)
{
	if (!_mainBook.isView) return;

	if (getCameraPoint().x > _mainBook.center.x - BOOKSIZEX / 2 &&
		getCameraPoint().x < _mainBook.center.x + BOOKSIZEX / 2 &&
		getCameraPoint().y > _mainBook.center.y - BOOKSIZEY / 2 &&
		getCameraPoint().y < _mainBook.center.y + BOOKSIZEY / 2)
	{
		_isMouseOnBook = true;
	}
	else _isMouseOnBook = false;
}

void mapToolBook::iconRender(void)
{
	if (_mainBook.isView) return;

	_iconBook.iconImg->aniRender(CAMERAMANAGER->getCameraDC(), _iconBook.center.x - _iconBook.iconImg->getFrameWidth() / 2 - 20,
		_iconBook.center.y - _iconBook.iconImg->getFrameHeight() / 2 + 20, _iconBook.ani);
}

void mapToolBook::bookRender(void)
{
	if (!_mainBook.isView) return;

	if (_mainBook.isOpen)
	{
		_mainBook.bookImg->frameRender(CAMERAMANAGER->getCameraDC(), _mainBook.center.x - _mainBook.bookImg->getFrameWidth() / 2,
			_mainBook.center.y - _mainBook.bookImg->getFrameHeight() / 2, 0, _mainBook.bookImg->getMaxFrameY());
	}
	else
	{
		_mainBook.bookImg->aniRender(CAMERAMANAGER->getCameraDC(), _mainBook.center.x - _mainBook.bookImg->getFrameWidth() / 2,
			_mainBook.center.y - _mainBook.bookImg->getFrameHeight() / 2, _mainBook.ani);
	}
}

void mapToolBook::markRender(void)
{
	if (!_mainBook.isOpen) return;

	// 좌측에 보이는 마크
	_bookMark.markImg->render(CAMERAMANAGER->getCameraDC(), _bookMark.leftPoint.x, _bookMark.leftPoint.y,
		0, 0,
		_bookMark.markImg->getWidth() / 2, (_bookMark.markImg->getHeight() / (MAXPAGE + 1)) * (_mainBook.pageIndex + 1));

	// 우측에 보이는 마크
	_bookMark.markImg->render(CAMERAMANAGER->getCameraDC(),
		_bookMark.rightPoint.x,
		_bookMark.rightPoint.y + ((_bookMark.markImg->getHeight() / (MAXPAGE + 1)) * (_mainBook.pageIndex + 1)),
		_bookMark.markImg->getWidth() / 2,
		_bookMark.markImg->getHeight() / (MAXPAGE + 1) * (_mainBook.pageIndex + 1),
		_bookMark.markImg->getWidth() / 2,
		_bookMark.markImg->getHeight() - ((_bookMark.markImg->getHeight() / (MAXPAGE + 1)) * (_mainBook.pageIndex + 1)));
}

void mapToolBook::pageManagerRender(void)
{
	if (!_mainBook.isOpen) return;

	_pageManager->render();
}

void mapToolBook::pageChangeRender(void)
{
	if (!_pageChange.isView) return;

	_pageChange.pageChangeImg->aniRender(CAMERAMANAGER->getCameraDC(), _mainBook.center.x - _mainBook.bookImg->getFrameWidth() / 2,
		_mainBook.center.y - _mainBook.bookImg->getFrameHeight() / 2, _pageChange.ani);
}

void mapToolBook::openBook(void)
{
	char str[128];
	sprintf_s(str, "MAIN_BOOK_OPEN_ANI_%d", _mapToolBookIndex);
	_mainBook.isView = true;
	_mainBook.ani = KEYANIMANAGER->findAnimation(str);
	_mainBook.ani->start();
}

void mapToolBook::closeBook(void)
{
	char str[128];
	sprintf_s(str, "MAIN_BOOK_CLOSE_ANI_%d", _mapToolBookIndex);
	_mainBook.isOpen = false;
	_mainBook.ani = KEYANIMANAGER->findAnimation(str);
	_mainBook.ani->start();
}

void mapToolBook::nextPage(void)
{
	char str[128];
	sprintf_s(str, "MAIN_BOOK_CHANGE_NEXT_ANI_%d", _mapToolBookIndex);
	_pageChange.ani = KEYANIMANAGER->findAnimation(str);
	_mainBook.pageIndex += 1;
	_pageChange.isView = true;
	_pageChange.ani->start();
}

void mapToolBook::beforePage(void)
{
	char str[128];
	sprintf_s(str, "MAIN_BOOK_CHANGE_BEFORE_ANI_%d", _mapToolBookIndex);
	_pageChange.ani = KEYANIMANAGER->findAnimation(str);
	_mainBook.pageIndex -= 1;
	_pageChange.isView = true;
	_pageChange.ani->start();
}

void mapToolBook::openBookC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_mainBook.isOpen = true;
}

void mapToolBook::closeBookC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_mainBook.isView = false;
}

void mapToolBook::changePageC(void* obj)
{
	mapToolBook* m = (mapToolBook*)obj;

	m->_pageChange.isView = false;
}