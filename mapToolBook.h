#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "mapToolNode.h"
#include "mapToolPage.h"

class mapToolBook : public gameNode
{
private:
	struct tagBook
	{
		image*	img;
		POINT	center;
		int		frameIndex;
		int		frameX, frameY;
		bool	isView;
		bool	isOpenCheck;
		bool	isCloseCheck;
		bool	isMove;
	};

	struct tagBookIcon
	{
		image*	img;
		POINT	center;
		int		frameIndex;
		int		frameX, frameY;
		bool	isView;
	};

	struct tagBookMark
	{
		image*	leftImg;
		image*	rightImg;
		POINT	leftPoint;
		POINT	rightPoint;
		int		pageIndex;
	};

	struct tagBookPage
	{
		image*	img;
		int		frameIndex;
		int		frameX, frameY;
		int		checkIndex;
		bool	isView;
	};

private:
	tagBook		_book;
	tagBookIcon	_icon;
	tagBookMark	_mark;
	tagBookPage _page;



public:
	mapToolBook();
	~mapToolBook();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);			// 이미지 추가
	void bookInit(void);			// 책관련

	void inputKey(void);			// 키 입력
	void moveBook(void);			// 책 움직임 키
	void changePage(void);			// 페이지 변경 키

	void frame(void);				// 프레임 변화
	void iconFrame(void);			// 아이콘 이미지
	void bookFrame(void);			// 책 이미지
	void pageFrame(void);			// 페이지 변경 이미지

	void iconRender(void);			// 아이콘 랜더
	void bookRender(void);			// 책 랜더
	void markRender(void);			// 마크 랜더
	void pageRender(void);			// 페이지 변경 랜더

	void openBook(void);			// 책 펼치기
	void closeBook(void);			// 책 접기
	void changePage(bool isNext);	// 페이지 변경



									// 페이지 테스트
	mapToolPage* _mapPage[MAXPAGE + 1];
	void testRender(void);
};