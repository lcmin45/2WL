#pragma once
#include "skill.h"
#include "player.h"
#include "얼음던지기.h"
class 얼음던지기매니저 : public skill
{
private:
	

	player* _player;

	int count=0;
public:
	얼음던지기매니저();
	~얼음던지기매니저();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject);
	void getPlayerAddressLink(player* player) { _player = player; }

	
};

