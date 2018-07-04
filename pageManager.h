#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "page0.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"

class pageManager
{
private:
	page0 * _page0;
	page1*	_page1;
	page1*	_page2;
	page2*	_page3;
	page2*	_page4;
	page3*	_page5;
	page3*	_page6;
	page4*	_page7;
	page4*	_page8;

	int		_pageIndex;				// 현재 페이지

public:
	pageManager();
	~pageManager();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void pageInit(void);										// 페이지 초기화
	void pageUpdate(void);										// 현재 페이지 업데이트
	void setCenterPoint(POINT center);							// 현재 책의 중점 체크

	void setPageIndex(int index) { _pageIndex = index; }		// 현재 책의 페이지 설정

	void setMapTileClass(mapTile* mapTile) { _page0->setMapTileClass(mapTile); }
};

