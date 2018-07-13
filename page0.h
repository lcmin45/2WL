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

	void boxInit(void);					// 박스 초기화

	void checkBox(void);				// 박스 선택시 현재 상태 변경

	void boxRender(void);				// 박스 렌더
	void fontRender(void);				// 폰트 렌더

	void setCenterPoint(POINT point);	// 책의 중점 좌표를 받아와 박스의 위치를 재설정

	void setMapTileClass(mapTile* mapTile) { _mapTile = mapTile; }
};