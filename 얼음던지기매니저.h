#pragma once
#include "skill.h"
#include "player.h"
#include "����������.h"
class ����������Ŵ��� : public skill
{
private:
	vector<����������*>			vIceThrow;
	vector<����������*>::iterator viIceThrow;

	player* _player;

	int count=0;
public:
	����������Ŵ���();
	~����������Ŵ���();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject);
	void getPlayerAddressLink(player* player) { _player = player; }

	vector<����������*>	getVIceThrow() { return vIceThrow; }
};

