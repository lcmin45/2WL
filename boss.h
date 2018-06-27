#pragma once
#include "gameNode.h"
#include "skill.h"

class boss : public gameNode
{
public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual void release();
	virtual void render();
	virtual void update();
};