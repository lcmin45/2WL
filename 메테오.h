#pragma once
#include "skill.h"



class ���׿� : public skill
{
private:
	
	float _playTime;
public:
	���׿�();
	~���׿�();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	void createMeteor();
	void moveMeteor();


	
};

