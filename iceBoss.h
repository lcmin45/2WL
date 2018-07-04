#pragma once
#include "boss.h"
class iceBoss :
	public boss
{

	bool _isCheck;
public:
	iceBoss();
	~iceBoss();

	virtual void render();
	virtual void update();
	virtual void iceMove();
	virtual void iceSkill();
};

