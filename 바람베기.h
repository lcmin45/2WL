#pragma once
#include "skill.h"
class �ٶ����� :	public skill
{
private:
	int _count=0;
public:
	�ٶ�����();
	~�ٶ�����();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
};

