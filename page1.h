#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page1 : public gameNode
{
private:
#define MAXBOX 72
#define	MAXBOXX 6
#define MAXBOXY 6

private:
	image * _titleImage[2];
	tagBox	_box[MAXBOX];

	POINT	_center;

public:
	page1();
	~page1();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);					// �ڽ� �ʱ�ȭ

	void checkBox(void);				// �ڽ� üũ�� ���� ����

	void titleRender(void);				// Ÿ��Ʋ ��Ʈ ����
	void tileRender(void);				// Ÿ�� �̹��� ����
	void boxRender(void);				// �ڽ� ���� ����

	void setIndex(int index);			// �ε��� ����
	void setCenterPoint(POINT point);

	void setBox(int index, int frameX, int frameY);	// �ڽ� �ʱ�ȭ�� ���� �ϱ� ���� ���� �Լ�
};


