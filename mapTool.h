#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "mapTile.h"
#include "mapToolBook.h"

class miniMap;

class mapTool : public gameNode
{
private:
	mapTile * _mapTile;			// 타일맵
	mapToolBook*	_book;				// 책
	miniMap*		_miniMap;			// 미니맵

	int				_moveSpeed;			// 화면 움직임 속도
	bool			_isMiniMapView;		// 미니맵을 보여주고 있는가

public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);		// 이미지 초기화

	void inputKey(void);		// 입력키 처리

	void miniMapRender(void);	// 미니맵 랜더
	void mapToolRender(void);	// 맵툴 렌더
};

