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

	void imageInit(void);			// �̹��� �ʱ�ȭ
	void bookInit(void);			// å���� �ʱ�ȭ
	void animationInit(void);		// �ִϸ��̼� �ʱ�ȭ
									
	void inputKey(void);			// Ű �Է�
	void openBookKey(void);			// å �������� Ű
	void moveBookKey(void);			// å ������ Ű
	void changePageKey(void);		// ������ ���� Ű
	void checkPageIndexCenter(void);// ������ �ε��� ��ǥ ����
	void checkMousePoint(void);		// ���̼� ����Ʈ�� å ���� �ִ��� üũ
										
	void iconRender(void);			// ������ ����
	void bookRender(void);			// å ����
	void markRender(void);			// ��ũ ����
	void pageRender(void);			// ������ ����
	void pageChangeRender(void);	// ������ ���� ����
									
	void openBook(void);			// å ��ġ��
	void closeBook(void);			// å ����
	void nextPage(void);			// ���� ������
	void beforePage(void);			// ���� ������


	static void openBookC(void* obj);		// å ���� ��
	static void closeBookC(void* obj);		// å �ݱ� ��
	static void changePageC(void* obj);		// ������ ��ȭ ��

	bool getIsMoveBook(void)	{ return _book.isMove; }
	bool getIsMouseBook(void)	{ return _isMouseBook; }

	void setMapTileClass(mapTile* mapTile) { _page->setMapTileClass(mapTile); }
};

