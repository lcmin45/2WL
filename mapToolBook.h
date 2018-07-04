#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "pageManager.h"

class mapToolBook : public gameNode
{
private:
	struct tagBook
	{
		image*		bookImg;				// 책의 이미지
		animation*	ani;					// 책의 애니메이션
		POINT		center;					// 책의 중점 좌표
		int			pageIndex;				// 현재 페이지 번호
		int			moveSpeed;				// 책의 이동 속도
		bool		isView;					// 현재 책이 보이는 상태인지 체크
		bool		isOpen;					// 현재 책이 완전히 펼쳐진 상태인지 체크
		bool		isMove;					// 현재 책을 움직일 수 있는 상태인지 체크
	};

	struct tagBookIcon
	{
		image*		iconImg;				// 아이콘 책의 이미지
		animation*	ani;					// 아이콘 책의 애니메이션
		POINT		center;					// 아이콘 책의 중점 좌표
	};

	struct tagBookMark
	{
		image*	markImg;					// 좌우측에 보이는 마크 이미지
		POINT	leftPoint;					// 좌측에 보이는 마크 좌상단 좌표
		POINT	rightPoint;					// 우측에 보이는 마크 좌상단 좌표
	};

	struct tagBookPage
	{
		image*		pageChangeImg;			// 페이지 변경시 보이는 이미지
		animation*	ani;					// 페이지 변경 애니메이션
		bool		isView;					// 페이지 변경 중인지 여부
	};

private:
	tagBook			_mainBook;				// 메인 책
	tagBookIcon		_iconBook;				// 책을 접었을 때 우상단에 보이는 책 아이콘
	tagBookMark		_bookMark;				// 책을 열었을 때 보이는 좌우측 페이지 마크
	tagBookPage		_pageChange;			// 책의 페이지를 변경할 때 보이는 모션
	pageManager*	_pageManager;			// 각 페이지를 관리하는 클래스

	bool			_isMouseOnBook;			// 현재 마우스가 책위에 있느냐

public:
	mapToolBook();
	~mapToolBook();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void bookInit(void);					// 책관련 초기화
	void pageInit(void);					// 페이지 초기화
	void animationInit(void);				// 애니매이션 초기화

	void inputKey(void);					// 입력 키 처리
	void openBookKey(void);					// 책 열고접는 키 처리
	void moveBookKey(void);					// 책 움직임 키 처리
	void changePageKey(void);				// 페이지 변경 키 처리
	void checkPageIndexCenter(void);		// 현재 페이와 중점 좌표 설정
	void checkMouseOnBook(void);			// 마이수 포인트가 책 위에 있는지 체크

	void iconRender(void);					// 아이콘 책 랜더
	void bookRender(void);					// 메인 책 랜더
	void markRender(void);					// 메인 책 마크 랜더
	void pageManagerRender(void);			// 페이지 내용 렌더
	void pageChangeRender(void);			// 페이지 변경 이미지 랜더

	void openBook(void);					// 책 펼치기 동작 함수
	void closeBook(void);					// 책 접기 동작 함수
	void nextPage(void);					// 다음 페이지 동작 함수
	void beforePage(void);					// 이전 페이지 동작 함수

											// 콜백함수
	static void openBookC(void* obj);		// 책 열기 후
	static void closeBookC(void* obj);		// 책 닫기 후
	static void changePageC(void* obj);		// 페이지 변화 후

	bool getIsMoveBook(void) { return _mainBook.isMove; }		// 현재 마우스가 책 위에 있는지
	bool getIsMouseBook(void) { return _isMouseOnBook; }		// 현재 마우스가 책 위에 있는지

	void setMapTileMemoryAddressLink(mapTile* mapTile) { _pageManager->setMapTileClass(mapTile); }
};