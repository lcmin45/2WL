#pragma once
#include "skill.h"
#include "player.h"
#include "얼음던지기.h"
class 얼음던지기매니저 : public skill
{
private:
	vector<얼음던지기*>			vIceThrow;
	vector<얼음던지기*>::iterator viIceThrow;

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

	vector<얼음던지기*>	getVIceThrow() { return vIceThrow; }
};

