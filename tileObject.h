#pragma once
#include "gameNode.h"

class tileObject : public gameNode
{
private:
	image*		img;
	animation*	animation;
	POINT		renderPoint;

public:
	tileObject();
	~tileObject();

	virtual HRESULT init(int index);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setPoint(POINT point) { renderPoint = point; }
};

