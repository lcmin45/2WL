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

	void boxInit(void);

	void titleRender(void);

	void setIndex(int index);
	void setCenterPoint(POINT point);
};
