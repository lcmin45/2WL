#pragma once
#include "boss.h"
class woodBoss : public boss
{
private:

	bool _isCheck; //프레임을 0으로 만들기 위한 변수
public:
	woodBoss();
	~woodBoss();


	virtual void render();
	virtual void update();
	virtual void woodMove();
	virtual void woodSkill();
};

