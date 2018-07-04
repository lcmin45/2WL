#pragma once
#include "gameNode.h"
#include "player.h"
#include "�Ҳ�Ÿ��.h"
#include "�ٶ�����.h"
#include "���ָ�.h"
#include "ȭ����.h"
#include "��Ÿ�¿ð���.h"

class player;

class projectileManager:public gameNode
{
private:
	�Ҳ�Ÿ�� * firePunchAtt;
	�ٶ����� * windCutterAtt;
	���ָ� * earthPunchAtt;

	ȭ���� * fireBallAtt;


	��Ÿ�¿ð���* fireSword;

	player* _player;

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(const char * skillName);
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
};

