#pragma once
#include "skill.h"
class �����Ѿ� : public skill
{
private:

	int _count;
public:
	�����Ѿ�();
	~�����Ѿ�();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();
};

