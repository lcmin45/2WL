#pragma once
#include "skill.h"
class ���ͱ��� : public skill
{
private:
	int _count = 0;
public:
	���ͱ���();
	~���ͱ���();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
};

