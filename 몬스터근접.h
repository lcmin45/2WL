#pragma once
#include "skill.h"
class 몬스터근접 : public skill
{
private:
	int _count = 0;
public:
	몬스터근접();
	~몬스터근접();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
};

