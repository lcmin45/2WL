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

	void imageInit(void);			// �̹��� �߰�
	void bookInit(void);			// å����

	void inputKey(void);			// Ű �Է�
	void moveBook(void);			// å ������ Ű
	void changePage(void);			// ������ ���� Ű

	void frame(void);				// ������ ��ȭ
	void iconFrame(void);			// ������ �̹���
	void bookFrame(void);			// å �̹���
	void pageFrame(void);			// ������ ���� �̹���

	void iconRender(void);			// ������ ����
	void bookRender(void);			// å ����
	void markRender(void);			// ��ũ ����
	void pageRender(void);			// ������ ���� ����

	void openBook(void);			// å ��ġ��
	void closeBook(void);			// å ����
	void changePage(bool isNext);	// ������ ����



									// ������ �׽�Ʈ
	mapToolPage* _mapPage[MAXPAGE + 1];
	void testRender(void);
};