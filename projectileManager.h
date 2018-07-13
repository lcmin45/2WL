#pragma once
#include "gameNode.h"
#include "player.h"
#include "mapToolNode.h"
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
#include "��������.h"
#include "�����ڱ�.h"
#include "���׿�.h"
#include "�ұ��.h"

struct tagCoolTime
{
	const char* name;
	float coolTime;
	float skillTime;
};

class projectileManager : public gameNode
{
private:
	player * _player;
	tagMapToolTile* _tile;

	vector<skill*>				vSkill;
	vector<skill*>::iterator	viSkill;

	tagCoolTime coolTime[7];

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool fire(string skillName);
	void fire(const char * skillName, POINTFLOAT pt);
	void vectorCheck();
	void vectorDraw();
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
	void setTileAddressLink(tagMapToolTile* getLink) { _tile = getLink; }


	vector<skill*>				getVSkill() { return vSkill; };
	vector<skill*>::iterator	getViSkill() { return viSkill; };
	float getCoolTime(const char* name);
};

