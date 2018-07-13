#pragma once
#include "boss.h"
class fireBoss :
	public boss
{
	bool _isCheck; //프레임을 0으로 만들기 위한 변수
public:
	fireBoss();
	~fireBoss();


	virtual void render();
	virtual void update();
	virtual void fireMove();
	virtual void fireSkill();
};

