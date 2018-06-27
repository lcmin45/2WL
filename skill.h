#pragma once
#include "gameNode.h"

class skill : public gameNode
{
public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};