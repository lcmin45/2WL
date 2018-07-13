#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page3 : public gameNode
{
private:
#define MAXBOX 36
#define	MAXBOXLX 3
#define MAXBOXLY 6
#define	MAXBOXRX 6
#define MAXBOXRY 3

private:
	image * _titleImage[2];
	tagBox _box[MAXBOX];

	POINT	_center;

public:
	page3();
	~page3();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);			// �ڽ� �ʱ�ȭ

	void checkBox(void);		// �ڽ� üũ�� ���� ����

	void titleRender(void);		// Ÿ��Ʋ ��Ʈ ����
	void tileRender(void);		// Ÿ�� �̹��� ����
	void boxRender(void);		// �ڽ� �̹��� ����

	void setIndex(int index);
	void setCenterPoint(POINT point);

	void setBox(int index, int startX, int startY, int endX, int endY, AUTOCHECK autoCheck, TERRAIN terrain);
};