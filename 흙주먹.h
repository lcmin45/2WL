#pragma once
#include "skill.h"
class ���ָ� : public skill
{
private:
	int earthIndex;

public:
	���ָ�();
	~���ָ�();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
	virtual void fireAtt();
};

