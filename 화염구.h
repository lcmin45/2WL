#pragma once
#include "skill.h"
class È­¿°±¸ : public skill
{
public:
	È­¿°±¸();
	~È­¿°±¸();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();

};

