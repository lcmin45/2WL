#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "tileObject.h"
#include "current.h"

// 오토 타일 페이지

class page4 : public gameNode
{
private:
#define MAXBOX 12
#define	MAXBOXX 2
#define MAXBOXY 3
	
	struct tagAutoBox
	{
		string		imageName;
		string		boxName;
		RECT		rc;
		POINT		center;
		int			imageIndex;
		POINT		startPoint;
		POINT		endPoint;
		AUTOCHECK	autoCheck;
		image*		autoTileImg;
		TERRAIN		terrain;
	};

private:
	POINT		_startPoint[MAXBOX];
	image*		_titleImage[2];
	tagAutoBox	_box[MAXBOX];

	POINT		_center;

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
