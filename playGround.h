#pragma once
#include "gameNode.h"
#include "inGame.h"
#include "mapTool.h"

class playGround : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
}; 