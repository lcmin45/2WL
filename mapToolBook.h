#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "pageManager.h"

class mapToolBook : public gameNode
{
private:
	struct tagBook
	{
		image*		img;
		animation*	ani;
		POINT		center;
		int			pageIndex;
		int			moveSpeed;
		bool		isView;
		bool		isOpen;
		bool		isMove;
	};

	struct tagBookIcon
	{
		image*		img;
		animation*	ani;
		POINT		center;
	};

	struct tagBookMark
	{
		image*	leftImg;
		image*	rightImg;
		POINT	leftPoint;
		POINT	rightPoint;
	};

	struct tagBookPage
	{
		image*		img;
		animation*	ani;
		bool		isView;
	};

private:
	tagBook			_book;
	tagBookIcon		_icon;
	tagBookMark		_mark;
	tagBookPage		_pageChange;
	pageManager*	_page;

	bool			_isMouseBook;

public:
	mapToolBook();
	~mapToolBook();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);			// 이미지 초기화
	void bookInit(void);			// 책관련 초기화
	void animationInit(void);		// 애니매이션 초기화
									
	void inputKey(void);			// 키 입력
	void openBookKey(void);			// 책 열고접는 키
	void moveBookKey(void);			// 책 움직임 키
	void changePageKey(void);		// 페이지 변경 키
	void checkPageIndexCenter(void);// 페이지 인덱스 좌표 설정
	void checkMousePoint(void);		// 마이수 포인트가 책 위에 있는지 체크
										
	void iconRender(void);			// 아이콘 랜더
	void bookRender(void);			// 책 랜더
	void markRender(void);			// 마크 랜더
	void pageRender(void);			// 페이지 렌더
	void pageChangeRender(void);	// 페이지 변경 랜더
									
	void openBook(void);			// 책 펼치기
	void closeBook(void);			// 책 접기
	void nextPage(void);			// 다음 페이지
	void beforePage(void);			// 이전 페이지


	static void openBookC(void* obj);		// 책 열기 후
	static void closeBookC(void* obj);		// 책 닫기 후
	static void changePageC(void* obj);		// 페이지 변화 후

	bool getIsMoveBook(void)	{ return _book.isMove; }
	bool getIsMouseBook(void)	{ return _isMouseBook; }

	void setMapTileClass(mapTile* mapTile) { _page->setMapTileClass(mapTile); }
};

