#pragma once
#include "gameNode.h"
#include "player.h"
#include "�Ҳ�Ÿ��.h"
#include "�ٶ�����.h"
#include "���ָ�.h"
#include "ȭ����.h"
#include "��Ÿ�¿ð���.h"


class projectileManager : public gameNode
{
private:
	player * _player;

	vector<skill*>				vSkill;
	vector<skill*>::iterator	viSkill;

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(const char * skillName);
	void vectorCheck();
	void vectorDraw();
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
};

