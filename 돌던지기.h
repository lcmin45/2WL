#pragma once
#include "skill.h"
#include "player.h"
class �������� :
	public skill
{
private:
	image * _img2;
	player * _player;
	float _fireAngle;
public:
	��������();
	~��������();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();

	void getPlayerAddressLink(player* player) { _player = player; }
};

