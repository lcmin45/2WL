#pragma once
#include "skill.h"
class ȭ���� : public skill
{
public:
	ȭ����();
	~ȭ����();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();

};

