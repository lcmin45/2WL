#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "pageManager.h"

class mapToolBook : public gameNode
{
private:
	struct tagBook
	{
		image*		bookImg;				// å�� �̹���
		animation*	ani;					// å�� �ִϸ��̼�
		POINT		center;					// å�� ���� ��ǥ
		int			pageIndex;				// ���� ������ ��ȣ
		int			moveSpeed;				// å�� �̵� �ӵ�
		bool		isView;					// ���� å�� ���̴� �������� üũ
		bool		isOpen;					// ���� å�� ������ ������ �������� üũ
		bool		isMove;					// ���� å�� ������ �� �ִ� �������� üũ
	};

	struct tagBookIcon
	{
		image*		iconImg;				// ������ å�� �̹���
		animation*	ani;					// ������ å�� �ִϸ��̼�
		POINT		center;					// ������ å�� ���� ��ǥ
	};

	struct tagBookMark
	{
		image*	markImg;					// �¿����� ���̴� ��ũ �̹���
		POINT	leftPoint;					// ������ ���̴� ��ũ �»�� ��ǥ
		POINT	rightPoint;					// ������ ���̴� ��ũ �»�� ��ǥ
	};

	struct tagBookPage
	{
		image*		pageChangeImg;			// ������ ����� ���̴� �̹���
		animation*	ani;					// ������ ���� �ִϸ��̼�
		bool		isView;					// ������ ���� ������ ����
	};

private:
	tagBook			_mainBook;				// ���� å
	tagBookIcon		_iconBook;				// å�� ������ �� ���ܿ� ���̴� å ������
	tagBookMark		_bookMark;				// å�� ������ �� ���̴� �¿��� ������ ��ũ
	tagBookPage		_pageChange;			// å�� �������� ������ �� ���̴� ���
	pageManager*	_pageManager;			// �� �������� �����ϴ� Ŭ����

	bool			_isMouseOnBook;			// ���� ���콺�� å���� �ִ���

public:
	mapToolBook();
	~mapToolBook();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void bookInit(void);					// å���� �ʱ�ȭ
	void pageInit(void);					// ������ �ʱ�ȭ
	void animationInit(void);				// �ִϸ��̼� �ʱ�ȭ

	void inputKey(void);					// �Է� Ű ó��
	void openBookKey(void);					// å �������� Ű ó��
	void moveBookKey(void);					// å ������ Ű ó��
	void changePageKey(void);				// ������ ���� Ű ó��
	void checkPageIndexCenter(void);		// ���� ���̿� ���� ��ǥ ����
	void checkMouseOnBook(void);			// ���̼� ����Ʈ�� å ���� �ִ��� üũ

	void iconRender(void);					// ������ å ����
	void bookRender(void);					// ���� å ����
	void markRender(void);					// ���� å ��ũ ����
	void pageManagerRender(void);			// ������ ���� ����
	void pageChangeRender(void);			// ������ ���� �̹��� ����

	void openBook(void);					// å ��ġ�� ���� �Լ�
	void closeBook(void);					// å ���� ���� �Լ�
	void nextPage(void);					// ���� ������ ���� �Լ�
	void beforePage(void);					// ���� ������ ���� �Լ�

											// �ݹ��Լ�
	static void openBookC(void* obj);		// å ���� ��
	static void closeBookC(void* obj);		// å �ݱ� ��
	static void changePageC(void* obj);		// ������ ��ȭ ��

	bool getIsMoveBook(void) { return _mainBook.isMove; }		// ���� ���콺�� å ���� �ִ���
	bool getIsMouseBook(void) { return _isMouseOnBook; }		// ���� ���콺�� å ���� �ִ���

	void setMapTileMemoryAddressLink(mapTile* mapTile) { _pageManager->setMapTileClass(mapTile); }
};