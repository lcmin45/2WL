#pragma once
#include "boss.h"
class fireBoss :public boss
{
	bool _isCheck;
public:
	fireBoss();
	~fireBoss();

	virtual void render();
	virtual void update();
	virtual void fireMove();
	virtual void fireSkill();
};

