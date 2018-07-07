#pragma once
#include "skill.h"

class �Ҳ�Ÿ�� : public skill
{
private:
	vector<PARTICLE>			vParticle;
	vector<PARTICLE>::iterator	viParticle;

	int _frameIndexY;

public:
	�Ҳ�Ÿ��();
	~�Ҳ�Ÿ��();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();
};

