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

	int		_pageIndex;				// ���� ������

public:
	pageManager();
	~pageManager();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void pageInit(void);										// ������ �ʱ�ȭ
	void pageUpdate(void);										// ���� ������ ������Ʈ
	void setCenterPoint(POINT center);							// ���� å�� ���� üũ

	void setPageIndex(int index) { _pageIndex = index; }		// ���� å�� ������ ����

	void setMapTileClass(mapTile* mapTile) { _page0->setMapTileClass(mapTile); }
};

