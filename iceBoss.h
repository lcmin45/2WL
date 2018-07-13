#pragma once
#include "boss.h"
class iceBoss :
	public boss
{

	bool _isCheck; //프레임을 0으로 만들기 위한 변수
public:
	iceBoss();
	~iceBoss();

	virtual void render();
	virtual void update();
	virtual void iceMove();
	virtual void iceSkill();
};

