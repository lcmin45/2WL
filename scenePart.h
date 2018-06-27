#pragma once
#include "gameNode.h"
#include "intro.h"
#include "loading.h"
#include "ending.h"

class scenePart : public gameNode
{
public:
	scenePart();
	~scenePart();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};