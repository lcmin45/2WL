#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "tileObject.h"

class page4 : public gameNode
{
private:
#define MAXBOX 12
#define	MAXBOXX 2
#define MAXBOXY 3

private:
	POINT	_startPoint[MAXBOX];
	image*	_titleImage[2];
	tagBox	_box[MAXBOX];

	POINT	_center;
	 
public:
	page4();
	~page4();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);

	void checkBox(void);

	void titleRender(void);
	void tileRender(void);

	void setIndex(int index);

	void setCenterPoint(POINT point);
};
