#pragma once
#include "skill.h"
class 사이클론부메랑 : public skill
{
private:
	image * _img2;
	image* _img3;
	image* _img4;


	int _frameIndex2;
	int _frameIndex3;
	int _frameIndex4;


	bool turn = false;

	int count;
public:
	사이클론부메랑();
	~사이클론부메랑();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);
	virtual void move();
	virtual void frameCount();
};

