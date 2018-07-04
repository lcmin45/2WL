#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class mapTile;

class page0 : public gameNode
{
private:
#define MAXBOX 6

private:
	tagBox	_box[MAXBOX];
	POINT	_center;

	mapTile* _mapTile;
public:
	page0();
	~page0();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);

	void checkBox(void);

	void boxRender(void);
	void fontRender(void);

	void setCenterPoint(POINT point);

	void setMapTileClass(mapTile* mapTile) { _mapTile = mapTile; }
};