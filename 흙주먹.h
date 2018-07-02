#pragma once
#include "skill.h"
class 入林冈 : public skill
{
private:
	int earthIndex;

public:
	入林冈();
	~入林冈();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
	virtual void fireAtt();
};

