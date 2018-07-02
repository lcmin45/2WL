#pragma once
#include "skill.h"
class 바람베기 :	public skill
{
private:
	int _count=0;
public:
	바람베기();
	~바람베기();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
};

