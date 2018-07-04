#pragma once
#include "skill.h"
class 맹렬회오리 :
	public skill
{
public:
	맹렬회오리();
	~맹렬회오리();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

