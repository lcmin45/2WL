#pragma once
#include "skill.h"
class �Ҳ�Ÿ�� : public skill
{
private:


public:
	�Ҳ�Ÿ��();
	~�Ҳ�Ÿ��();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void frameCount();
};

