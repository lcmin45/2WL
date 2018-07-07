#pragma once
#include "gameNode.h"
#include "inGame.h"
#include "mapTool.h"
#include "intro.h"
#include "ending.h"
#include "loading.h"

class playGround : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void settingAddImage(void);

	playGround();
	~playGround();
}; 