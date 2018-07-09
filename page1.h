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

	void boxInit(void);

	void checkBox(void);

	void titleRender(void);
	void tileRender(void);
	void boxRender(void);

	void setIndex(int index);
	void setCenterPoint(POINT point);

	void setBox(int index, int frameX, int frameY);
};


