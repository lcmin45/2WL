#pragma once
#include "gameNode.h"

class tileObject : public gameNode
{
private:
	image * _img;				// 이미지
	animation*	_animation;			// 애니메이션
	POINT		_tileCenterPoint;	// 타일 중점 포인트
	POINT		_renderPoint;		// 랜드용 좌표

public:
	tileObject();
	~tileObject();

	virtual HRESULT init(int index);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setCenterPoint(POINT point) { _tileCenterPoint = point; }
	void setRenderPoint(POINT point) { _renderPoint = point; }
};

