#pragma once
#include "skill.h"

class 맹렬회오리 : public skill
{
private:
	image* _img2;
	image* _img3;
	image* _img4;


	int _frameIndex2;
	int _frameIndex3;
	int _frameIndex4;
public:
	맹렬회오리();
	~맹렬회오리();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);
	virtual void move();
	virtual void frameCount();
};

