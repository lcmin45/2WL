#pragma once
#include "gameNode.h"
#include "current.h"

class miniMap : public gameNode
{
private:
	image*	_miniMap;				// 전체 맵을 축소하여 미니맵 이미지가 됨

public:
	miniMap();
	~miniMap();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setMiniMap(HDC hdc);		// 전체 맵 이미지를 받음
};

