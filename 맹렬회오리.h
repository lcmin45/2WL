#pragma once
#include "skill.h"
class �ͷ�ȸ���� :
	public skill
{
public:
	�ͷ�ȸ����();
	~�ͷ�ȸ����();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

