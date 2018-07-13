#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page2 : public gameNode
{
private:
#define MAXBOX 18
#define	MAXBOXX 3
#define MAXBOXY 3

private:
	image * _titleImage[2];
	tagBox	_box[MAXBOX];

	POINT	_center;

public:
	page2();
	~page2();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);			// �ڽ� �ʱ�ȭ

	void titleRender(void);		// Ÿ��Ʋ ��Ʈ ����
	void tileRender(void);		// Ÿ�� �̹��� ����
	void boxRender(void);		// �ڽ� �̹��� ����

	void checkBox(void);		// �ڽ� üũ�� ���� ����

	void setIndex(int index);	// �ε��� ����
	void setCenterPoint(POINT point);

};
