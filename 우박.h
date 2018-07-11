#pragma once
#include "skill.h"

struct collision
{
	image* img;
	POINTFLOAT ptStart;
	POINTFLOAT pt;
	RECT rc;
	int frameIndex;
};

class 우박 : public skill
{
private:
	vector<collision*>				vHail;
	vector<collision*>::iterator	viHail;

	POINTFLOAT _pt2, _pt3, _pt4;
	RECT _rc2, _rc3,_rc4;

public:
	우박();
	~우박();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void fire(const char * skillName, int amount, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();

	void createHail();
	void moveHail();
	void collisionHail();
};

