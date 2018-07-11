#pragma once
#include "gameNode.h"
#include "player.h"
#include "�Ҳ�Ÿ��.h"
#include "�ٶ�����.h"
#include "���ָ�.h"
#include "ȭ����.h"
#include "��Ÿ�¿ð���.h"
#include "�ͷ�ȸ����.h"
#include "����Ŭ�кθ޶�.h"
#include "���ͱ���.h"
#include "�����Ѿ�.h"
#include "����������Ŵ���.h"
#include "���.h"


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
	void fire(const char * skillName, POINTFLOAT pt);
	void vectorCheck();
	void vectorDraw();
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }


	vector<skill*>				getVSkill() { return vSkill; };
	vector<skill*>::iterator	getViSkill() { return viSkill; };
	
};

