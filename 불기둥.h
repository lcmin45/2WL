#pragma once
#include "skill.h"
#include "player.h"

class �ұ�� : public skill
{
private:
	player * _player;
	int _fireCount;

public:
	�ұ��();
	~�ұ��();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();
	void getPlayerAddressLink(player* player) { _player = player; }
};

